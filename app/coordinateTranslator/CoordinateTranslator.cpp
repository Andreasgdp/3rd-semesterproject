#include "CoordinateTranslator.h"
#include <iostream>

using namespace std;
using namespace Eigen;

CoordinateTranslator::CoordinateTranslator() {
}

CoordinateTranslator::CoordinateTranslator(const vector<Vector3d> &robotPointSet, const vector<Vector3d> &worldPointSet) {
    _robotPointSet = robotPointSet;
    _worldPointSet = worldPointSet;
    setNumberOfPoints();
}

void CoordinateTranslator::setNumberOfPoints() {
    if (_robotPointSet.size() != _worldPointSet.size()) {
            throw invalid_argument("Robot and world point sets must be of same size!");
    } else {
        _numberOfPoints = _robotPointSet.size();
    }
}

Vector3d CoordinateTranslator::computeCentroid(const vector<Vector3d> &pointSet) {
    Vector3d sum = {0, 0, 0};
    for (int i = 0; i < _numberOfPoints; i++) {
        sum += pointSet[i];
    }
    return 1 / (double)_numberOfPoints * sum;
}

vector<Vector3d> CoordinateTranslator::computeZeroCentroidPointSet(const vector<Vector3d> &pointSet, const Vector3d &centroid) {
    vector<Vector3d> q;
    for (int i = 0; i < _numberOfPoints; i++) {
        q.push_back(pointSet[i] - centroid);
    }
    return q;
}

JacobiSVD<Matrix3d> CoordinateTranslator::computeSVD(const vector<Vector3d> &robotPointSet, const vector<Vector3d> &worldPointSet, const unsigned int &computationOptions) {
    Matrix3d sum;
    sum << 0, 0, 0, 0, 0, 0, 0, 0, 0;
    for (int i = 0; i < _numberOfPoints; i++) {
        sum += robotPointSet[i] * worldPointSet[i].transpose();
    }
    Eigen::JacobiSVD<Eigen::Matrix3d> svd(sum, computationOptions);
    return svd;
}

Matrix3d CoordinateTranslator::computeRotationMatrix(const JacobiSVD<Matrix3d> &svd) {
    return svd.matrixV() * svd.matrixU().transpose();
}

Vector3d CoordinateTranslator::computeTranslationMatrix(const Matrix3d &rotationMatrix, const Vector3d &robotPointSetCentroid, const Vector3d &worldPointSetCentroid) {
    return worldPointSetCentroid - rotationMatrix * robotPointSetCentroid;
}

Matrix4d CoordinateTranslator::constructTransformationMatrix(const Matrix3d &rotationMatrix, const Vector3d &translationVector, const RowVector3d &shear, const double &scale) {
    Matrix4d H;
    H << rotationMatrix.coeff(0, 0), rotationMatrix.coeff(0, 1), rotationMatrix.coeff(0, 2), translationVector(0),
         rotationMatrix.coeff(1, 0), rotationMatrix.coeff(1, 1), rotationMatrix.coeff(1, 2), translationVector(1),
         rotationMatrix.coeff(2, 0), rotationMatrix.coeff(2, 1), rotationMatrix.coeff(2, 2), translationVector(2),
         shear(0)                  , shear(1)                  , shear(2)                  , scale;
    return H;
}

void CoordinateTranslator::computeInverseTransformationMatrix() {
    _inverseTransformationMatrix = _transformationMatrix.inverse();
}

void CoordinateTranslator::calibrateRobotToTable() {
    Vector3d robotCentroid = computeCentroid(_robotPointSet);
    Vector3d worldCentroid = computeCentroid(_worldPointSet);

    Matrix3d rotationMatrix = computeRotationMatrix(computeSVD(computeZeroCentroidPointSet(_robotPointSet, robotCentroid), computeZeroCentroidPointSet(_worldPointSet, worldCentroid)));
    Vector3d translationMatrix = computeTranslationMatrix(rotationMatrix, robotCentroid, worldCentroid);

    Matrix4d H = constructTransformationMatrix(rotationMatrix, translationMatrix);
    _transformationMatrix = H;
    computeInverseTransformationMatrix();
}

Vector3d CoordinateTranslator::computeRobotPointCoords(const double &x, const double &y, const double &z) {
    Vector4d inputPoint = {x, y, z, 1};
    Vector4d robotPoint4d = _inverseTransformationMatrix * inputPoint;
    Vector3d robotPoint3d = {robotPoint4d(0), robotPoint4d(1), robotPoint4d(2)};
    return robotPoint3d;
}






























