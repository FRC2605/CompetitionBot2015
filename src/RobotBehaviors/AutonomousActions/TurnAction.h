#ifndef SHS2605_TURNRIGHTACTION_H
#define SHS2605_TURNRIGHTACTION_H

#include <Sensing/IAngularInput.h>
#include <hardware/Drive/MecanumDriveTrain.h>
#include <Actions/IAction.h>

class TurnAction : public IAction
{
public:
	
	TurnAction ( MecanumDriveTrain * Drive, IAngularInput * Angle, double Target, double RotationSpeed, double Tolerance );
	~TurnAction ();
	
	void Reset ();
	
	void Start ();
	bool IsComplete ();
	void Stop ();
	
	void Update ();

private:
	
	MecanumDriveTrain * Drive;
	IAngularInput * Angle;
	
	double Offset;
	double Turned;
	double Target;
	
	double RotationSpeed;
	double Tolerance;
	
};

#endif
