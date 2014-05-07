#ifndef ACTIONSTOP_H
#define ACTIONSTOP_H

#include "Aria.h"

//  Your typical Action header use as a template 
//  for other action class headers

class ActionStop : public ArAction
{
public:

	ActionStop( double range );

	virtual ~ActionStop(void) {};

	virtual ArActionDesired *fire( ArActionDesired currentDesired);

	virtual void setRobot(ArRobot* robot);

protected:

	ArRangeDevice *mySonar;

	ArActionDesired myDesired;

	double range;

};
#endif;