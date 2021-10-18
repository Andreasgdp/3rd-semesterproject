#include "JointPoseGetter.h"
#include "cmath"

using namespace std;

JointPoseGetter::JointPoseGetter(/* args */)
{
}

JointPoseGetter::~JointPoseGetter()
{
}

vector<vector<double>> JointPoseGetter::jacobian(double q1, double q2, double q3, double q4, double q5, double q6)
{
    vector<vector<double>> jacobianData { {(273 * cos(q1)) / 2500 + (3223 * cos(q1) * cos(q5)) / 10000 + (17 * cos(q2) * sin(q1)) / 40 - (947 * cos(q4) * (cos(q2) * sin(q1) * sin(q3) + cos(q3) * sin(q1) * sin(q2))) / 10000 + (947 * sin(q4) * (sin(q1) * sin(q2) * sin(q3) - cos(q2) * cos(q3) * sin(q1))) / 10000 - (3223 * sin(q5) * (cos(q4) * (sin(q1) * sin(q2) * sin(q3) - cos(q2) * cos(q3) * sin(q1)) + sin(q4) * (cos(q2) * sin(q1) * sin(q3) + cos(q3) * sin(q1) * sin(q2)))) / 10000 - (49 * sin(q1) * sin(q2) * sin(q3)) / 125 + (49 * cos(q2) * cos(q3) * sin(q1)) / 125, (17 * cos(q1) * sin(q2)) / 40 + (947 * cos(q4) * (cos(q1) * cos(q2) * cos(q3) - cos(q1) * sin(q2) * sin(q3))) / 10000 - (947 * sin(q4) * (cos(q1) * cos(q2) * sin(q3) + cos(q1) * cos(q3) * sin(q2))) / 10000 + (3223 * sin(q5) * (cos(q4) * (cos(q1) * cos(q2) * sin(q3) + cos(q1) * cos(q3) * sin(q2)) + sin(q4) * (cos(q1) * cos(q2) * cos(q3) - cos(q1) * sin(q2) * sin(q3)))) / 10000 + (49 * cos(q1) * cos(q2) * sin(q3)) / 125 + (49 * cos(q1) * cos(q3) * sin(q2)) / 125, (947 * cos(q4) * (cos(q1) * cos(q2) * cos(q3) - cos(q1) * sin(q2) * sin(q3))) / 10000 - (947 * sin(q4) * (cos(q1) * cos(q2) * sin(q3) + cos(q1) * cos(q3) * sin(q2))) / 10000 + (3223 * sin(q5) * (cos(q4) * (cos(q1) * cos(q2) * sin(q3) + cos(q1) * cos(q3) * sin(q2)) + sin(q4) * (cos(q1) * cos(q2) * cos(q3) - cos(q1) * sin(q2) * sin(q3)))) / 10000 + (49 * cos(q1) * cos(q2) * sin(q3)) / 125 + (49 * cos(q1) * cos(q3) * sin(q2)) / 125, (947 * cos(q4) * (cos(q1) * cos(q2) * cos(q3) - cos(q1) * sin(q2) * sin(q3))) / 10000 - (947 * sin(q4) * (cos(q1) * cos(q2) * sin(q3) + cos(q1) * cos(q3) * sin(q2))) / 10000 + (3223 * sin(q5) * (cos(q4) * (cos(q1) * cos(q2) * sin(q3) + cos(q1) * cos(q3) * sin(q2)) + sin(q4) * (cos(q1) * cos(q2) * cos(q3) - cos(q1) * sin(q2) * sin(q3)))) / 10000, -(3223 * sin(q1) * sin(q5)) / 10000 - (3223 * cos(q5) * (cos(q4) * (cos(q1) * cos(q2) * cos(q3) - cos(q1) * sin(q2) * sin(q3)) - sin(q4) * (cos(q1) * cos(q2) * sin(q3) + cos(q1) * cos(q3) * sin(q2)))) / 10000, 0},
																{(273 * sin(q1)) / 2500 - (17 * cos(q1) * cos(q2)) / 40 + (3223 * cos(q5) * sin(q1)) / 10000 + (947 * cos(q4) * (cos(q1) * cos(q2) * sin(q3) + cos(q1) * cos(q3) * sin(q2))) / 10000 + (947 * sin(q4) * (cos(q1) * cos(q2) * cos(q3) - cos(q1) * sin(q2) * sin(q3))) / 10000 - (3223 * sin(q5) * (cos(q4) * (cos(q1) * cos(q2) * cos(q3) - cos(q1) * sin(q2) * sin(q3)) - sin(q4) * (cos(q1) * cos(q2) * sin(q3) + cos(q1) * cos(q3) * sin(q2)))) / 10000 - (49 * cos(q1) * cos(q2) * cos(q3)) / 125 + (49 * cos(q1) * sin(q2) * sin(q3)) / 125, (17 * sin(q1) * sin(q2)) / 40 - (947 * cos(q4) * (sin(q1) * sin(q2) * sin(q3) - cos(q2) * cos(q3) * sin(q1))) / 10000 - (947 * sin(q4) * (cos(q2) * sin(q1) * sin(q3) + cos(q3) * sin(q1) * sin(q2))) / 10000 + (3223 * sin(q5) * (cos(q4) * (cos(q2) * sin(q1) * sin(q3) + cos(q3) * sin(q1) * sin(q2)) - sin(q4) * (sin(q1) * sin(q2) * sin(q3) - cos(q2) * cos(q3) * sin(q1)))) / 10000 + (49 * cos(q2) * sin(q1) * sin(q3)) / 125 + (49 * cos(q3) * sin(q1) * sin(q2)) / 125, (3223 * sin(q5) * (cos(q4) * (cos(q2) * sin(q1) * sin(q3) + cos(q3) * sin(q1) * sin(q2)) - sin(q4) * (sin(q1) * sin(q2) * sin(q3) - cos(q2) * cos(q3) * sin(q1)))) / 10000 - (947 * sin(q4) * (cos(q2) * sin(q1) * sin(q3) + cos(q3) * sin(q1) * sin(q2))) / 10000 - (947 * cos(q4) * (sin(q1) * sin(q2) * sin(q3) - cos(q2) * cos(q3) * sin(q1))) / 10000 + (49 * cos(q2) * sin(q1) * sin(q3)) / 125 + (49 * cos(q3) * sin(q1) * sin(q2)) / 125, (3223 * sin(q5) * (cos(q4) * (cos(q2) * sin(q1) * sin(q3) + cos(q3) * sin(q1) * sin(q2)) - sin(q4) * (sin(q1) * sin(q2) * sin(q3) - cos(q2) * cos(q3) * sin(q1)))) / 10000 - (947 * sin(q4) * (cos(q2) * sin(q1) * sin(q3) + cos(q3) * sin(q1) * sin(q2))) / 10000 - (947 * cos(q4) * (sin(q1) * sin(q2) * sin(q3) - cos(q2) * cos(q3) * sin(q1))) / 10000, (3223 * cos(q1) * sin(q5)) / 10000 + (3223 * cos(q5) * (cos(q4) * (sin(q1) * sin(q2) * sin(q3) - cos(q2) * cos(q3) * sin(q1)) + sin(q4) * (cos(q2) * sin(q1) * sin(q3) + cos(q3) * sin(q1) * sin(q2)))) / 10000, 0},
																{0, (49 * sin(q2) * sin(q3)) / 125 - (49 * cos(q2) * cos(q3)) / 125 - (17 * cos(q2)) / 40 - (3223 * sin(q5) * (cos(q4) * (cos(q2) * cos(q3) - sin(q2) * sin(q3)) - sin(q4) * (cos(q2) * sin(q3) + cos(q3) * sin(q2)))) / 10000 + (947 * cos(q4) * (cos(q2) * sin(q3) + cos(q3) * sin(q2))) / 10000 + (947 * sin(q4) * (cos(q2) * cos(q3) - sin(q2) * sin(q3))) / 10000, (49 * sin(q2) * sin(q3)) / 125 - (49 * cos(q2) * cos(q3)) / 125 - (3223 * sin(q5) * (cos(q4) * (cos(q2) * cos(q3) - sin(q2) * sin(q3)) - sin(q4) * (cos(q2) * sin(q3) + cos(q3) * sin(q2)))) / 10000 + (947 * cos(q4) * (cos(q2) * sin(q3) + cos(q3) * sin(q2))) / 10000 + (947 * sin(q4) * (cos(q2) * cos(q3) - sin(q2) * sin(q3))) / 10000, (947 * cos(q4) * (cos(q2) * sin(q3) + cos(q3) * sin(q2))) / 10000 - (3223 * sin(q5) * (cos(q4) * (cos(q2) * cos(q3) - sin(q2) * sin(q3)) - sin(q4) * (cos(q2) * sin(q3) + cos(q3) * sin(q2)))) / 10000 + (947 * sin(q4) * (cos(q2) * cos(q3) - sin(q2) * sin(q3))) / 10000, -(3223 * cos(q5) * (cos(q4) * (cos(q2) * sin(q3) + cos(q3) * sin(q2)) + sin(q4) * (cos(q2) * cos(q3) - sin(q2) * sin(q3)))) / 10000, 0},
																{0, sin(q1), sin(q1), sin(q1), cos(q4) * (cos(q1) * cos(q2) * sin(q3) + cos(q1) * cos(q3) * sin(q2)) + sin(q4) * (cos(q1) * cos(q2) * cos(q3) - cos(q1) * sin(q2) * sin(q3)), cos(q5) * sin(q1) - sin(q5) * (cos(q4) * (cos(q1) * cos(q2) * cos(q3) - cos(q1) * sin(q2) * sin(q3)) - sin(q4) * (cos(q1) * cos(q2) * sin(q3) + cos(q1) * cos(q3) * sin(q2)))},
																{0, -cos(q1), -cos(q1), -cos(q1), cos(q4) * (cos(q2) * sin(q1) * sin(q3) + cos(q3) * sin(q1) * sin(q2)) - sin(q4) * (sin(q1) * sin(q2) * sin(q3) - cos(q2) * cos(q3) * sin(q1)), sin(q5) * (cos(q4) * (sin(q1) * sin(q2) * sin(q3) - cos(q2) * cos(q3) * sin(q1)) + sin(q4) * (cos(q2) * sin(q1) * sin(q3) + cos(q3) * sin(q1) * sin(q2))) - cos(q1) * cos(q5)},
																{1,
																 0,
																 0,
																 0,
																 sin(q4) * (cos(q2) * sin(q3) + cos(q3) * sin(q2)) - cos(q4) * (cos(q2) * cos(q3) - sin(q2) * sin(q3)),
																 -sin(q5) * (cos(q4) * (cos(q2) * sin(q3) + cos(q3) * sin(q2)) + sin(q4) * (cos(q2) * cos(q3) - sin(q2) * sin(q3)))},
    };

    this->j = jacobianData;

    return jacobianData;
}

void JointPoseGetter::showJacobian()
{
    for (int i = 0; i < this->j.size(); i++)
    {
        for (int j = 0; j < this->j[i].size(); j++)
        {
            cout << this->j[i][j] << ", ";
        }
        cout << endl;
    }
}