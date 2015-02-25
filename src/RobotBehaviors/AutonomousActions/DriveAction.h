#ifndef SHS2605_DRIVEACTION_H
#define SHS2605_DRIVEACTION_H

#include <hardware/Drive/MecanumDriveTrain.h>
#include <Timing/IntervalTimer.h>
#include <Actions/IAction.h>

class DriveAction : public IAction
{
public:
	
	DriveAction ( MecanumDriveTrain * Drive, double XSpeed, double YSpeed, double Time );
	~DriveAction ();
	
	void Reset ();
	
	void Start ();
	bool IsComplete ();
	void Stop ();
	
	void Update ();
	
private:
	
	MecanumDriveTrain * Drive;
	
	double XSpeed;
	double YSpeed;
	double Time;
	
	IntervalTimer Timer;
	
};

#endif
