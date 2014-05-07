#include "ActionReadSonar.h"
#include "ArRobot.h"
#include <iostream>
#include <fstream>

enum SONAR_IDS
{
	LEFT    = 0,
	FRONT_1 = 1,
	FRONT_2 = 2,
	FRONT_3 = 3,
	FRONT_4 = 4,
	RIGHT   = 5,
	BACK_1  = 6,
	BACK_2  = 7,
};
using namespace std;
// Constructor
ActionReadSonar::ActionReadSonar(double range) : ArAction("ReadSonar")
{
	this->range = range;
	ofstream myfile;
	myfile.open("example.csv");
	myfile << "X" << ", " << "Y" << ", " << "Thetha" << "\n";
}

// Fire Action, this is called by ARIA, 
// does not need to be specifically called. 

ArActionDesired* ActionReadSonar::fire(ArActionDesired currentDesired)
{


	ArRobot *robot = this->getRobot();
	
	int total = robot->getNumSonar(); // get the total number of sonar on the robot
	ArSensorReading* value; // This class abstracts range and angle read from sonar

	//cout << " 0 : " << robot->getSonarReading(0)->getSensorTh() << " 1 : " << robot->getSonarReading(1)->getSensorTh() 
	//	 << " 2 : " << robot->getSonarReading(2)->getSensorTh() << " 3 : " << robot->getSonarReading(3)->getSensorTh()
	//	 << " 4 : " << robot->getSonarReading(4)->getSensorTh() << " 5 : " << robot->getSonarReading(5)->getSensorTh()
	//	 << " 6 : " << robot->getSonarReading(6)->getSensorTh() << " 7 : " << robot->getSonarReading(7)->getSensorTh()
		 
	//	 << "r :" << robot->getTh() << endl;


	double limit = 800;
	double distance;

	// reset the actionDesired (must be done), to clear
	// its previous values.
	myDesired.reset();

	// if the sonar is null we can't do anything, so deactivate
	if (mySonar == NULL)
	{
		deactivate();
		return NULL;
	}

	// gets value of object between -20 degrees and 20 degrees of foward
	double angle = 0;
	distance = mySonar->currentReadingPolar(-20, 20, &angle);
	//cout << "distance from nearest object =" << distance << endl;
	

	if (distance <= limit) {
		int heading = 15;

		//cout << "angle :" << angle << endl;
		if (angle > 10) {
			heading = -heading;
		}
		else if (angle < -10) {
			heading = heading;
		}
		
		//cout << "x" << robot->getX() << " ," << robot->getY() << endl;
		cout << "distance from nearest object =" << distance << endl;

		
		robot->lock();
		robot->setVel(0);
		robot->unlock();

		robot->lock();
		robot->setDeltaHeading(heading);
		robot->unlock();

		ArUtil::sleep(50);
	}

	return &myDesired;
}

// Called by ARIA when actions are added to a robot
// Do not call this method directly.

void ActionReadSonar::setRobot(ArRobot *robot)
{
	// Copies over pointer to the robot object
	ArAction::setRobot(robot);

	// Checks for a sonar device
	mySonar = robot->findRangeDevice("sonar");

	// No Sonar = Deactivate the robot
	if (mySonar == NULL)
	{
		ArLog::log(ArLog::Terse, "actionExample: ActionTurn: Warning: I found no sonar, deactivating.");
		deactivate();
	}
}