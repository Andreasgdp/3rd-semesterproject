#include <iostream>
#include <eigen3/Eigen/Dense>
#include <vector>
#include "./robotConnection/RobotConnection.h"
#include "imageProcessing/ImageProcessing.h"
#include <math.h>
#include <chrono>
#include <thread>
#include "coordinateTranslator/CoordinateTranslator.h"
#include "gripperHandling/GripperController.h"
#include "simulation/Simulation.h"
#include "api/Api.h"
#include "app/App.h"

using namespace std;
using namespace Eigen;
using namespace ur_rtde;

int main(int argc, char *argv[])
{
//    RobotConnection r("192.168.100.49");
//    cout << r.getActualJointPoses() << endl << endl;
//    cout << r.getActualTCPPose() << endl << endl;


//    CoordinateTranslator c;
//    Api _api;
//    vector<CalibPoint> calibPoints = _api.getCalibPoint(1);
//    vector<Vector3d> P_robot;
//    vector<Vector3d> P_table;
//    for (int i = 0; i < calibPoints.size(); i++) {
//        P_robot.push_back(calibPoints[i].pointRobot);
//        P_table.push_back(calibPoints[i].pointTable);
//    }

//    c.setPointSets(P_robot, P_table);
//    c.calibrateRobotToTable();

//    RobotConnection _roboConn("127.0.0.1");
//    ThrowCalc _throwCalc;
//    _roboConn.moveThrowPos(1, 1);

//    Vector3d goalPos = Vector3d(0.4,0.4,0);

//    VectorXd dx = _throwCalc.velocityCalc(goalPos[0], goalPos[1], goalPos[2], _roboConn.getActualTCPPose());
//    cout << dx << endl << endl;
//    VectorXd q_end = _roboConn.getActualJointPoses();
//    VectorXd dq_end = _throwCalc.jacobianInverse(q_end[0], q_end[1], q_end[2], q_end[3], q_end[4], q_end[5]) * dx;
//    // Find acceleration vector
//    VectorXd accVector(6);
//    double t = 0.1;
//    accVector = dq_end / t;

//    // Starting pos for throw
//    VectorXd q_start = q_end - (0.5 * accVector * pow(t, 2));

//    // Move from home to start of throw
//    _roboConn.moveJ(q_start, 1, 1);

//    vector<VectorXd> jointVelocities = _throwCalc.getJointVelocities(t, q_end, q_start, dx, accVector);
//    for (int i = 0; i < jointVelocities.size(); i++)
//    {
//        _roboConn.speedJ(jointVelocities.at(i), 40, 0.008);
//        this_thread::sleep_for(chrono::milliseconds(8));
//    }
//    _roboConn.speedStop(40);

    App app("192.168.100.49", "192.168.100.11", false);
    app.findAndGrabObject();
    app.throwObject();

    /*
    Api api;
    CalibPoint calibPoint;

    int robotId = 1;½
    calibPoint.robotId = robotId;

    Vector3d P_robot1 = {-0.05907, -0.31838, 0.17};
    Vector3d P_robot2 = {0.06377, -0.48364, 0.17};
    Vector3d P_robot3 = {0.23051, -0.36235 ,0.17};

    Vector3d P_world1 = {0.65, 0.55, 0.205};
    Vector3d P_world2 = {0.45 , 0.5, 0.205};
    Vector3d P_world3 = {0.5, 0.3, 0.205};

    calibPoint.pointRobot = P_robot1;
    calibPoint.pointTable = P_world1;

    api.createCalibPoint(calibPoint);


    calibPoint.pointRobot = P_robot2;
    calibPoint.pointTable = P_world2;

    api.createCalibPoint(calibPoint);


    calibPoint.pointRobot = P_robot3;
    calibPoint.pointTable = P_world3;

    api.createCalibPoint(calibPoint);
    */

    /*
    VectorXd actualPos(6);
    actualPos << 0, 0, 0, 0, 0, 0;
    VectorXd withinPos(6);
    withinPos << 2, -2, 2, 2, 2, 2;

    Simulation sim("127.0.0.1");
    cout << "Within: " << sim.withinOffset(actualPos, withinPos, 4) << endl;
    */
//    Logger l1;
//    l1.getAndSetCurrTimeStamp();
//    this_thread::sleep_for(chrono::milliseconds(8));

//    this_thread::sleep_for(chrono::milliseconds(8));
//    Logger l3;
//    l1.endTime(l1.setThrowTime);
//    cout << l1.getThrowTime() << endl;


//    Logger l1;
//    this_thread::sleep_for(chrono::milliseconds(8));
//    l1.startTime();
//    this_thread::sleep_for(chrono::milliseconds(16));
//    Logger l3;
//    l1.endTime(l1.setThrowTime);
//    cout << l1.getThrowTime() << endl;

//    VectorXd actualPos(6);
//    actualPos << 0, 0, 0, 0, 0, 0;
//    VectorXd withinPos(6);
//    withinPos << 2, -2, 2, 2, 2, 2;

//    Simulation sim("127.0.0.1");
//    cout << "Within: " << sim.withinOffset(actualPos, withinPos, 4) << endl;

    /*
    VectorXd homePos(6);
    homePos << 0.143, -0.435, 0.20, -0.001, 3.12, 0.04;
    VectorXd grabPos(6);
    grabPos << 0.4, -0.435, 0.20, -0.001, 3.12, 0.04;

    vector<VectorXd> throwJointSpeeds;
    VectorXd jointSpeed1(6), jointSpeed2(6);
    jointSpeed1 << 1, 1, 1, 1, 1, 1;
    jointSpeed2 << 5, 5, 5, 5, 5, 5;
    throwJointSpeeds.push_back(jointSpeed1);
    throwJointSpeeds.push_back(jointSpeed2);

    Simulation sim("127.0.0.1");

    cout << "grab: " << sim.executeGrabSimulation(homePos, grabPos) << endl;
    cout << "throw: " << sim.executeThrowSimulation(grabPos, throwJointSpeeds) << endl;
    */


    /*
    RobotConnection robConn("127.0.0.1");
    cout << "Is connected: " << robConn.isConnected() << endl;

    VectorXd jointPoses(6);
    jointPoses << 0.143, -0.435, 0.20, -0.001, 3.12, 0.04;
    robConn.moveL(jointPoses, 0.5, 0.2);

    cout << "Pro stop: " << robConn.isProtectiveStopped() << endl;
    cout << "Actual TCP: " << robConn.getActualTCPPose() << endl;
    */

    /*
    // The constructor simply takes the IP address of the Robot
    RTDEControlInterface rtde_control("127.0.0.1");
    // First argument is the pose 6d vector followed by speed and acceleration
    rtde_control.moveL({-1.143, -0.435, 0.20, -0.001, 3.12, 0.04}, 0.5, 0.2);
    */

    /*
    // Calibration points in robot and world frame
    Vector3d P_robot1 = {-0.05907, -0.31838, 0.17};
    Vector3d P_robot2 = {0.06377, -0.48364, 0.17};
    Vector3d P_robot3 = {0.23051, -0.36235 ,0.17};
    vector<Vector3d> P_robot;
    P_robot.insert(P_robot.end(), {P_robot1, P_robot2, P_robot3});

    Vector3d P_world1 = {0.65, 0.55, 0.02};
    Vector3d P_world2 = {0.45 , 0.5, 0.02};
    Vector3d P_world3 = {0.5, 0.3, 0.02};
    vector<Vector3d> P_world;
    P_world.insert(P_world.end(), {P_world1, P_world2, P_world3});

    // Calibrate robot to table and compute entered point in world to robot frame
    CoordinateTranslator CoordinateTranslator;
    CoordinateTranslator.setPointSets(P_robot, P_world);

    CoordinateTranslator.calibrateRobotToTable();
    Vector3d pos = CoordinateTranslator.computeRobotPointCoords(0.5, 0.3, 0.02);
    cout << "Entered point from world frame in robot frame: " << endl << pos << endl;
    */

    /*
    Vector3d rot;
    rot << 1.7, 2.65, 0;

    VectorXd vec_joined(pos.size() + rot.size());
    vec_joined << pos, rot;
    cout << "vec_joined: " << endl << vec_joined << endl;

    RobotConnection robConn("192.168.100.49");
    cout << "Connected: " << robConn.isConnected() << endl;
    //GripperController gripCont("192.168.100.11");
    //gripCont.setForceLimit(40.0f);

    //gripCont.open();
    VectorXd customHome;
    customHome << 0.180, -0.193, 0.298, 1.6, 2.57, -0.14;
    //robConn.moveL(customHome);

    robConn.moveL(vec_joined);

    //gripCont.close();

    //robConn.moveL(customHome);

    //gripCont.disconnect();
    */

    /*
    RobotConnection r("127.0.0.1");
    // RobotConnection r("192.168.100.30");
    JointPoseGetter j;

    VectorXd dx(6);
    dx << 0.04, 0, 0, 0, 0, 0;

    VectorXd q_end(6);
    q_end << -0.136581,-0.217782,1.655361,-0.485521, 2.96964, -0.775282;
    r.moveJ(q_end, 1, 1);
    VectorXd x_end = r.getActualTCPPose();
    this_thread::sleep_for(chrono::milliseconds(1000));

    VectorXd dq_end = j.jacobianInverse(q_end[0], q_end[1], q_end[2], q_end[3], q_end[4], q_end[5]) * dx;
    cout << "expected joint poses:  \n" << q_end << endl;

    VectorXd q_start = q_end + (dq_end * -3);
    r.moveJ(q_start, 1, 1);

    this_thread::sleep_for(chrono::milliseconds(1000));

    vector<VectorXd> test = j.getJointVelocities(q_start, q_end, dx);

    for (int i = 0; i < test.size(); i++)
    {
        r.speedJ(test.at(i), 40);
        this_thread::sleep_for(chrono::milliseconds(8));
    }
    cout << "actual:  \n" << r.getActualJointPoses() << endl;
    r.speedStop(10);
    */

    return 0;
}
