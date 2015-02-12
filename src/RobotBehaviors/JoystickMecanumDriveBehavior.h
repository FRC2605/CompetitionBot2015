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
	
	JoystickMecanumDriveBehavior ( MecanumDriveTrain * DriveTrain, IXYInput * StrafeInput, IXInput * RotationInput, IBooleanInput * FinePositioningButton );
	~JoystickMecanumDriveBehavior ();
	
	void Init ( BehaviorController * Controller, const char * AppliedID );
	void Destroy ();
	
	void Start ();
	void Stop ();
	
	void Update ();
	
	static const char * GetDefaultBehaviorID ();
	
private:
	
	MecanumDriveTrain * Drive;
	
	IXYInput * Strafe;
	IXInput * Rotate;
	
	IBooleanInput * FinePositioningButton;
	
};

#endif
