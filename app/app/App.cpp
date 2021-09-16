#include "App.h"

App::App(std::string IP, const cv::Mat &calibrationImg) : roboConn(IP)
{
    this->IP = IP;
    this->setDefaultPosMovement();

    if (!this->roboConn.isConnected()) throw "Connection could not be established with ip: " + this->IP;

    if (!this->isImageProvided(calibrationImg)) {
        // Use imageProcessing to get image from camera
    }

    // use imageProcessing to calibrate camera

    // setup simulator

    this->moveHome();
}

void App::findAndGrabObject(const cv::Mat &objectImg)
{
    if (!this->isImageProvided(objectImg)) {
        // Use imageProcessing to get image from camera
    }

    // use imageProcessing to get coordinates to object in relation to the table from image

    // use jointPoseGetter to calculate and set jointposes, speed, acceleration for grabbing object

    // simulate move (handle err by calculating new joint poses)
    // calculate and simulate until a valid move is made (implement timeout and throw err)

    // TODO figure out best values for speed and acceleration.
    this->roboConn.moveL(this->jointPoses, this->speed, this->acceleration);

    this->waitForMoveRobot(this->jointPoses);

    // use gripperHandling to grab object (wait for confirmed grip)
}

void App::throwObject(const std::vector<double> &goalPos)
{
    this->moveHome();

    // use jointPoseGetter to get joint poses, speed and acceleration for throwing object

    // simulate move (handle err by calculating new joint poses)
    // calculate and simulate until a valid move is made (implement timeout and throw err)

    this->roboConn.moveL(this->jointPoses, this->speed, this->acceleration);

    // This wait may need to be more specific for the throw in order to time the release of object.
    this->waitForMoveRobot(this->jointPoses);

    // let go of object at right timing (may need threads)

    this->moveHome();
}

void App::moveHome()
{
    this->setDefaultPosMovement();
    // simulate move (handle err by calculating new joint poses)
    // calculate and simulate until a valid move is made (implement timeout and throw err)
    this->roboConn.moveL(this->homeJointPoses, this->speed, this->acceleration);
    this->waitForMoveRobot(this->homeJointPoses);
}

bool App::isImageProvided(const cv::Mat &image)
{
    return !(image.cols == 0 && image.rows == 0);
}

bool App::robotHasMovedToPos(const std::vector<double> &pos)
{
    // TODO: make sure they are able to be compared
    return this->roboConn.getActualJointPoses() == pos;
}

void App::waitForMoveRobot(const std::vector<double> &pos)
{
    while (!this->robotHasMovedToPos(pos)){
        // Implement a timeout feature. Throw error if timeout.
    }
}

void App::setDefaultPosMovement()
{
    this->homeJointPoses = this->roboConn.getHomeJointPos();
    this->speed = this->roboConn.getDefaultSpeed();
    this->acceleration = this->roboConn.getDefaultAcceleration();
}
