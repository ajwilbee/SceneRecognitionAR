#ifndef ACTIONREADSONAR_H
#define ACTIONREADSONAR_H

#include "Aria.h"


//  Your typical Action header use as a template 
//  for other action class headers

class ActionReadSonar : public ArAction
{
public:

	ActionReadSonar(double range);

	virtual ~ActionReadSonar(void) {
	};

	virtual ArActionDesired *fire(ArActionDesired currentDesired);

	virtual void setRobot(ArRobot* robot);



protected:

	ArRangeDevice *mySonar;
	

	ArActionDesired myDesired;

	double range;

};
#endif;