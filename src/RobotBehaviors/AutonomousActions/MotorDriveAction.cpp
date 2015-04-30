#include "MotorDriveAction.h"

MotorDriveAction :: MotorDriveAction ( SpeedController * Motor, double Time, double Power, double OffPower ):
	Motor ( Motor ),
	Time ( Time ),
	Timer (),
	Power ( Power ),
	OffPower ( OffPower )
{
};

MotorDriveAction :: ~MotorDriveAction ()
{
};

void MotorDriveAction :: Reset ()
{

	Timer.Reset ();

}

void MotorDriveAction :: Start ()
{

	Timer.Start ();

	Motor -> Set ( Power );

};

bool MotorDriveAction :: IsComplete ()
{

	return Timer.GetTimeS () >= Time;

};

void MotorDriveAction :: Stop ()
{

	Timer.Stop ();

	Motor -> Set ( OffPower );

};

void MotorDriveAction :: Update ()
{};

