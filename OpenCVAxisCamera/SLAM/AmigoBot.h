/**
 *	FileName:		AmigoBot.h
 *	Author:			Ryan M. Bowen
 *	Date:			09/28/09
 *
 *	Description:	Header File for AmigoBot Class The
 *					Class is a facade for amigobot connections.
 */
#ifndef AMIGOBOT_H
#define AMIGOBOT_H

#include "Aria.h"
#include <iostream>

using namespace std;

#define REMOTE_HOST_FLAG	"-rh"		// Flags to Connect Remotely
#define SERIAL_PORT_FLAG	"-rp"		// Flags to Connect Local Serial
#define TCP_PORT_FLAG		"-rrtp"		// Flags to Connect Remore TCP/IP

class AmigoBot
{
	public:

		/**
		 *	Public Constructor
		 *
		 *	@param robotName		- Name for the robot.
		 *	@param connectionType	- Type of connection
		 *							  0	- Remote
		 *							  1 - Serial 
		 *							  2 - Simulator
		 *	@param arg				- command-line arguments
		 */
		AmigoBot(const char* robotName, const unsigned char connectionType, const char* arg);

		/**
		 *  Public Destructor
		 */
		~AmigoBot();

		/* Starts the robot connection. */
		void			start(void);

		/* Disconnects the robot. */
		void 			disconnect(void);

		/* Return the pointer the ArRobot object created on connection*/
		ArRobot* 		getRobot();

		/* Adds the sonar device */
		void 	addSonar();

		/* Returnt the pointer to the sonar device*/
		ArSonarDevice* 	getSonar();

		/* Remote Connection Flag */
		static const unsigned char REMOTE;

		/* Serial Connection Flag */
		static const unsigned char SERIAL;

		/* Simulator Connection Flag */
		static const unsigned char SIMULATOR;

		// Go to forward
		void goForward(int dist) {

			// when  the velocity is 250 the speed peer 0.25 m/s
			double travel_time = 1000*dist/0.25;

			cout << "Travel time :" <<(int)travel_time << endl;

			robot->lock();
			robot->setVel(250);
			robot->unlock();
			ArUtil::sleep((int)travel_time);
		}
	
	private:

		/* Robot Name */
		const char* robotName;

		/* The Robot Object */
		ArRobot* robot;

		/* Sonar Device Object*/
		ArSonarDevice*	sonar;
		
		/* Connection Object for robot */		 
		ArRobotConnector* robotConnector;
		
	

		/**
		 *  Connects to the robot
		 *	@params (same as constructor)
		 *	
		 */
		void	connect(const unsigned char connectionType , const char* arg);
};

#endif
