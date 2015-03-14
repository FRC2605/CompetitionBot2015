#ifndef SHS2605_MECANUMDRIVEBEHAVIOR_H
#define SHS2605_MECANUMDRIVEBEHAVIOR_H

#include <Hardware/Drive/MecanumDriveTrain.h>
#include <Hardware/Drive/IQuadRectangularDriveBase.h>

#include <Sensing/IXYInput.h>
#include <Sensing/IBooleanInput.h>

#include <Behaviors/IBehavior.h>

#define JOYSTICKMECANUMDRIVE_BID "joystick_mecanum_drive"

class JoystickMecanumDriveBehavior : public IBehavior
{
public:
	
	JoystickMecanumDriveBehavior ( MecanumDriveTrain * DriveTrain, IXYInput * StrafeInput, IXInput * RotationInput, IBooleanInput * TurboBotton, double LowMotorSpeed, double HighMotorSpeed, IQuadRectangularDriveBase * LowSpeedDrive, IQuadRectangularDriveBase * HighSpeedDrive = NULL );
	~JoystickMecanumDriveBehavior ();
	
	void Init ( BehaviorController * Controller, const char * AppliedID );
	void Destroy ();
	
	void Start ();
	void Stop ();
	
	void Update ();
	
	static const char * GetDefaultBehaviorID ();
	
private:
	
	MecanumDriveTrain * Drive;
	
	IQuadRectangularDriveBase * LowSpeedDrive;
	IQuadRectangularDriveBase * HighSpeedDrive;
	
	bool LowMotorSpeed;
	bool HighMotorSpeed;
	
	IXYInput * Strafe;
	IXInput * Rotate;
	
	IBooleanInput * TurboButton;
	
	bool LastTurboState;
	
};

#endif
