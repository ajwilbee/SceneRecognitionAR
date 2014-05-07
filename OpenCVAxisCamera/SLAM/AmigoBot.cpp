#include "Aria.h"
#include "AmigoBot.h"

// Connection constants 

const unsigned char AmigoBot::REMOTE 	= 0;	// Connect remotely
const unsigned char AmigoBot::SERIAL	= 1;	// Connect through serial port
const unsigned char AmigoBot::SIMULATOR	= 2;	// Connect to the simulator


// SEE HEADER FILE FOR FUNCTION COMMENTS

AmigoBot::AmigoBot( const char* robotName, const unsigned char connectionType, const char* arg )
{
	this->robotName	= robotName;
	this->robot = NULL;
	this->sonar	= NULL;

	// Connection to robot on object creation
	connect( connectionType, arg );
}

AmigoBot::~AmigoBot()
{
	disconnect();

	//delete sonar;
	//delete robot;
}

void AmigoBot::connect(const unsigned char connectionType , const char* arg)
{

	// Setup the Command Line Arguments Manually
	// FIX LATER : APPEND TO EXISTING ARGS
	int argc = 3;

	const char* p1 = " ";
	const char* p2 = " ";

	switch( connectionType )
	{
		case AmigoBot::REMOTE:

			p2 = REMOTE_HOST_FLAG;

			break;

		case AmigoBot::SERIAL:

			p2 = SERIAL_PORT_FLAG;

			break;

		case AmigoBot::SIMULATOR:

			p2 = TCP_PORT_FLAG;

			break;

	}

	// Set arguments
	char** argv = (char**) malloc( sizeof(p1) + sizeof(p2) + sizeof(arg) );
	argv[0] = (char*)p1;
	argv[1] = (char*)p2;
	argv[2] = (char*)arg;

	// Log arguments used
	ArLog::log(ArLog::Normal, "AmigoBotControl: Using Parameters: %s %s %s\r\n",p1,p2,arg);

	// Parse the command-line arguments
	ArArgumentParser parser(&argc, argv);
  	parser.loadDefaultArguments();

	// Check the command-line arguments for errors	
	if (!Aria::parseArgs())
  	{
		ArLog::log(ArLog::Normal, "AmigoBotControl: Bad Arguments");

		// Show argument options
    		Aria::logOptions();
    		Aria::shutdown();
  	}

	robot = new ArRobot();

	// Create a new aria connection object for the robot
	// base on the command-line arguments
  	robotConnector = new ArRobotConnector(&parser, robot);

  	ArLog::log(ArLog::Terse, "AmigoBotControl: Started!");


	// Attempt to connect to the robot
	if(!robotConnector->connectRobot())
  	{
		// Connection issues display some options (from aria
    		ArLog::log(ArLog::Terse, "AmigoBotControl: Could not connect to the robot.");													
    		if(parser.checkHelpAndWarnUnparsed())
    		{
       	 		Aria::logOptions();
        		Aria::exit(1);
    		}

		robot = NULL;
  	}

	
}

void AmigoBot::addSonar()
{
	sonar = new ArSonarDevice();
	robot->addRangeDevice(sonar);
}


void AmigoBot::start()
{
	robot->runAsync(true);
	

	// Wait 5 Seconds for sonar start-up
	ArUtil::sleep(5000);
}

void AmigoBot::disconnect()
{
	ArLog::log(ArLog::Normal, "AmigoBotControl: Ending robot thread...");
  	robot->stopRunning();

  	// wait for the thread to stop
  	robot->waitForRunExit();

}

ArRobot* AmigoBot::getRobot()
{
	return robot;
}

ArSonarDevice* AmigoBot::getSonar()
{
	return sonar;
}
