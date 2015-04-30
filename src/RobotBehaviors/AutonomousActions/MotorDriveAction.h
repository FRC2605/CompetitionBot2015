#ifndef SHS_2605_MOTORDRIVEACTION_H
#define SHS_2605_MOTORDRIVEACTION_H

#include <WPILib.h>

#include <Actions/IAction.h>

#include <Timing/IntervalTimer.h>

class MotorDriveAction : public IAction
{
public:

	MotorDriveAction ( SpeedController * Motor, double Time, double Power, double OffPower = 0.0 );
	~MotorDriveAction ();

	virtual void Reset ();

	virtual void Start ();
	virtual bool IsComplete ();
	virtual void Stop ();

	virtual void Update ();

private:

	SpeedController * Motor;
	IntervalTimer Timer;

	double Time;



	double Power;
	double OffPower;

};

#endif
