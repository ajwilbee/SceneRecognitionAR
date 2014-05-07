#include <stdio.h>
#include "Aria.h"
#include "AmigoBot.h"
#include "ActionStop.h"
#include "ActionReadSonar.h"
#include "TimeWindow.h"


static TimeWindow timeWindow;

// Function Prototypes
void move(ArRobot* robot, double time_ms = 1000, int speed_mm = 250);
void square(ArRobot* robot);
void Wandering(ArRobot* robot);

void turn(ArRobot *robot, double angle);

void readSonars(ArRobot* robot);

int main2( int argc, char** argv )
{
	// Special ARIA initializations (NO TOUCH)
	Aria::init();

	// Create a New amigoBot Object
	// Param 1 - Some Name
	// Param 2 - Connection Type (AmigoBot::REMOTE, AmigoBot::SERIAL,AmigoBot::SIMULATOR)
	// Param 3 - Special Connection Param (IP, COM, PORT)

	AmigoBot* amigoBot = new AmigoBot("C",AmigoBot::REMOTE, "127.0.0.1");	
	//AmigoBot* amigoBot = new AmigoBot("A",AmigoBot::SERIAL,"COM");

	// This a default simulator robot object see above for other types
	// Note that the first parameter is some string name for now it matters not what it is
	//AmigoBot* amigoBot = new AmigoBot("E",AmigoBot::SIMULATOR,"8101");

	// Create the Actions
	ArActionStallRecover recover;		// Special Aria Action Recover if motors stall
	//ActionStop actionStop(10000);		// Fire Stop
	ActionReadSonar actionReadSonar(1000);

	// Create Devices
	ArSonarDevice sonar;

	ArRobot *robot = amigoBot->getRobot();

	// Attach Actions
	amigoBot->getRobot()->addRangeDevice(&sonar);
	//amigoBot->getRobot()->addAction(&recover,100);
	//amigoBot->getRobot()->addAction(&actionStop,50);
	amigoBot->getRobot()->addAction(&actionReadSonar, 50);

	// Start the robot
	amigoBot->getRobot()->enableMotors();
	amigoBot->getRobot()->runAsync(true);
	amigoBot->getRobot()->setConnectionTimeoutTime(0);

	ArUtil::sleep(100);

	ArTime start;
	start.setToNow();
	int i = 0;
	while (1)
	{

		move(robot);
		if (start.mSecSince() > 1000)
		{
			cout << i++ << endl;
			start.setToNow();

			readSonars(robot);

			if (i == 40) {
				//TimeWindow.showAll();
				break;
			}
		}
		ArUtil::sleep(50);
	}

	char c = getchar();

	if (c == 's') {
		timeWindow.savePos();
	}
	
	// Clean-Up Destroy the AmigoBot Object
	delete amigoBot;
	
	
	return 0;
}

void readSonars(ArRobot* robot )
{

	SonarData * datas[8];
	for (int i = 0; i < 8; i++)
	{
		SonarData * data = new SonarData();

		data->x = robot->getSonarReading(i)->getX();
		data->y = robot->getSonarReading(i)->getY();
		data->theta = robot->getSonarReading(i)->getSensorTh();
		data->range = robot->getSonarReading(i)->getRange();

		datas[i] = data;

		cout << "S_X :" << data->x << " S_Y:" << data->y << " Robot x :" << robot->getX() << " Robot y :" << robot->getY() << endl;
	}

	timeWindow.addNewData2TW(datas);
	double x = robot->getX();
	double y = robot->getY();
	


	timeWindow.addRobotPos(x, y);


	//cout << ":" << robot->getSonarReading(0)->getX() << "," << robot->getSonarReading(0)->getY() << " Angle :" << robot->getSonarReading(3)->getSensorTh() << ":" << robot->getSonarReading(0)->getRange() << endl;
}


void move(ArRobot* robot, double time_ms /*=1000*/, int speed_mm /*=250*/) 
{
	robot->lock();
	robot->setVel(speed_mm);
	robot->unlock();

	ArUtil::sleep(time_ms);

	robot->lock();
	robot->setVel(0);
	robot->unlock();
}

void square(ArRobot* robot)
{
	for (int i = 0; i < 1; i++) {
		//move(robot, 10000, 500);
		turn(robot, 30);
		turn(robot, -180);
	}
}

void turn( ArRobot *robot, double angle) 
{
	robot->lock();
	robot->setDeltaHeading(angle);
	robot->unlock();

	ArUtil::sleep(5000);
}

void Wandering(ArRobot* robot)
{
	while (1){
		robot->lock();
		robot->setVel(500);
		robot->unlock();
	}
}
