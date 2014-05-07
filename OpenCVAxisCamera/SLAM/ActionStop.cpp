#include "ActionStop.h"
#include <iostream>

using namespace std;

// Constructor
ActionStop::ActionStop(double range) : ArAction("Stop")
{
	this->range = range;	
}

// Fire Action, this is called by ARIA, 
// does not need to be specifically called. 

ArActionDesired* ActionStop::fire(ArActionDesired currentDesired)
{
	ArRobot *robot = this->getRobot();
	double limit = 20*29*2;
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
	double angle;
	distance = mySonar->currentReadingPolar(-40, 40, &angle);

	//cout << "Distance :" << distance / 29 / 2 << " Angle :" << (double)(angle) << endl;

	if (distance <= limit) {

		cout << "distance from nearest object =" << distance/29/2 << endl;

	    robot->lock();
		robot->stop();
		robot->unlock();

		robot->lock();
		robot->setDeltaHeading(10);
		robot->unlock();

		ArUtil::sleep(50);
	}

	return &myDesired;
}

// Called by ARIA when actions are added to a robot
// Do not call this method directly.

void ActionStop::setRobot(ArRobot *robot)
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