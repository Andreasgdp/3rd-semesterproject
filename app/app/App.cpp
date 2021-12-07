#include "App.h"
#include <thread>
#include "../api/Logger.h"

using namespace std;
using namespace Eigen;

GripperController _gripper("192.168.100.11");
Logger _log;

App::App(std::string robotIP,
         std::string gripperIP,
         bool localEnv) : _roboConn(robotIP),
                          _simulator("127.0.0.1"),
                          _coordTrans(),
                          _api()
{
    _localEnv = localEnv;
    // Sets the ip of the "robot" to the ip provided or to 127.0.0.1 if in local environment
    _IP = (!_localEnv) ? robotIP : "127.0.0.1";

    if (!_roboConn.isConnected())
        throw std::invalid_argument("Connection could not be established with ip: " + _IP);

    vector<CalibPoint> calibPoints = _api.getCalibPoint(1);
    vector<Vector3d> P_robot;
    vector<Vector3d> P_table;
    for (int i = 0; i < calibPoints.size(); i++) {
        P_robot.push_back(calibPoints[i].pointRobot);
        P_table.push_back(calibPoints[i].pointTable);
    }

    _coordTrans.setPointSets(P_robot, P_table);
    _coordTrans.calibrateRobotToTable();

    moveHome();

    _gripper.open();
}

void App::findAndGrabObject()
{
    moveHome();
    _doneThrow = false;
    bool simSuccess = false;
    _gripper.open();

    // use imageProcessing to get coordinates to object in relation to the table from image
//    vector<double> imgBallCoords = _imgProcessor.getBallCoords();
    vector<vector<double>> positions = _imgProcessor.liveHoughCircles();
    _imgBallCoords = positions.at(0);
    _imgTargetCoords = positions.at(1);

    // translate the coordinates to the object in relation to table to robot base coordinates
    Vector3d robotObjectPoint = _coordTrans.computeRobotPointCoords(_imgBallCoords[1], _imgBallCoords[0], 0.194); // TODO: Check for hardcoded z

    VectorXd homePos = _roboConn.getHomePosCoords();

    Vector3d robotObjectPointRotation;
    robotObjectPointRotation << homePos[3], homePos[4], homePos[5];

    // move above object
    VectorXd endPosAboveObject(6);
    endPosAboveObject << robotObjectPoint[0], robotObjectPoint[1], 0.280329, robotObjectPointRotation;
    simSuccess = _simulator.executeMoveLSimulation(_roboConn.getActualJointPoses(), endPosAboveObject);
    if (!simSuccess) return;
    _roboConn.moveL(endPosAboveObject, _roboConn.getDefaultSpeed(), _roboConn.getDefaultAcceleration());

    // move to object
    VectorXd robotObjectPointAndRotation(6);
    robotObjectPointAndRotation << robotObjectPoint, robotObjectPointRotation;
    simSuccess = _simulator.executeMoveLSimulation(_roboConn.getActualJointPoses(), robotObjectPointAndRotation);
    if (!simSuccess) return;
    _roboConn.moveL(robotObjectPointAndRotation, _roboConn.getDefaultSpeed(), _roboConn.getDefaultAcceleration());

    // grab object
    _gripper.close();

    // move above object
    simSuccess = _simulator.executeMoveLSimulation(_roboConn.getActualJointPoses(), endPosAboveObject);
    if (!simSuccess) return;
    _roboConn.moveL(endPosAboveObject, _roboConn.getDefaultSpeed(), _roboConn.getDefaultAcceleration());
}

void App::throwObject()
{
    bool simSuccess = false;
    simSuccess = _simulator.executeMoveJSimulation(_roboConn.getActualJointPoses(), _roboConn.getThrowPosJoints());
    if (!simSuccess) return;
    _roboConn.moveThrowPos(_roboConn.getDefaultSpeed(), _roboConn.getDefaultAcceleration());

    // move to throw angle
    VectorXd actualTCP(6);
    actualTCP = _roboConn.getActualTCPPose();
//    actualTCP = _simulator.getActualTCPPose();
    Vector3d tcpInTable = _coordTrans.computeTablePointCoords(actualTCP[0], actualTCP[1], actualTCP[2]);

    double v = _throwCalc.TCPAngleCalc(_imgTargetCoords[0], _imgTargetCoords[1], tcpInTable);

    VectorXd newPos(6);
    newPos << _roboConn.getActualJointPoses();
//    newPos << _simulator.getActualJointPoses();
    newPos[4] += v;

    simSuccess = _simulator.executeMoveJSimulation(_roboConn.getActualJointPoses(), newPos);
    if (!simSuccess) return;
    _roboConn.moveJ(newPos, _roboConn.getDefaultSpeed(), _roboConn.getDefaultAcceleration());


    // something something
    VectorXd dx = _throwCalc.velocityCalc(_imgTargetCoords[0], _imgTargetCoords[1], 0.15, _simulator.getActualTCPPose());
//    VectorXd dx = _throwCalc.velocityCalc(_imgTargetCoords[0], _imgTargetCoords[1], _imgTargetCoords[2], _roboConn.getActualTCPPose()) * 0.5;

    VectorXd q_end = _simulator.getActualJointPoses();
    VectorXd dq_end = _throwCalc.jacobianInverse(q_end[0], q_end[1], q_end[2], q_end[3], q_end[4], q_end[5]) * dx;
    // Find acceleration vector
    VectorXd accVector(6);
    double t = 0.2;
    accVector = dq_end / t;

    // Starting pos for throw
    VectorXd q_start = q_end - (0.5 * accVector * pow(t, 2));


    // Move from home to start of throw
    simSuccess = _simulator.executeMoveJSimulation(_roboConn.getActualJointPoses(), q_start);
    if (!simSuccess) return;
    _roboConn.moveJ(q_start, _roboConn.getDefaultSpeed(), _roboConn.getDefaultAcceleration());

    vector<VectorXd> jointVelocities = _throwCalc.getJointVelocities(t, q_end, q_start, dx, accVector);

    simSuccess = _simulator.executeThrowSimulation(_roboConn.getActualJointPoses(), q_end, jointVelocities);
    if (!simSuccess) return;

    thread throwThread([](double time) {
        time -= 0.025;
        int timeMilli = time * 1000;
        this_thread::sleep_for(chrono::milliseconds(timeMilli));
//        _log.startTime();
        _gripper.open();
//        _log.endTime(_log.setGrabTime);
    }, t);

    for (int i = 0; i < jointVelocities.size(); i++)
    {
        _roboConn.speedJ(jointVelocities.at(i), 40, 0.008);
        this_thread::sleep_for(chrono::milliseconds(8));
    }
    _roboConn.speedStop(40);

    throwThread.join();

    this->moveHome();
    _doneThrow = true;
}

void App::moveHome()
{
    bool simSuccess = false;
    simSuccess = _simulator.executeMoveJSimulation(_roboConn.getActualJointPoses(), _roboConn.getHomePosJoints());
    if (!simSuccess) return;
    _roboConn.moveJ(_roboConn.getHomePosJoints(), _roboConn.getDefaultSpeed(), _roboConn.getDefaultAcceleration());
}

bool App::doneThrow() const
{
    return _doneThrow;
}

void App::setDoneThrow(bool newDoneThrow)
{
    _doneThrow = newDoneThrow;
}
