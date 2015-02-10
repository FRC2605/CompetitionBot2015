#ifndef SHS2605_MECANUMDRIVEBEHAVIOR_H
#define SHS2605_MECANUMDRIVEBEHAVIOR_H

#include <Behaviors/IBehavior.h>

#include <Hardware/Drive/MecanumDriveTrain.h>
#include <Hardware/Drive/IQuadRectangularDriveBase.h>

#include <Sensing/IXYInput.h>

#define JOYSTICKMECANUMDRIVE_BID "joystick_mecanum_drive"

class JoystickMecanumDriveBehavior : public IBehavior
{
public:
	
	JoystickMecanumDriveBehavior ( MecanumDriveTrain * DriveTrain, IXYInput * StrafeInput, IXInput * RotationInput );
	~JoystickMecanumDriveBehavior ();
	
	void Init ();
	void Destroy ();
	
	void Start ();
	void Stop ();
	
	void Update ();
	
	static const char * GetDefaultBehaviorID ();
	
private:
	
	MecanumDriveTrain * Drive;
	
	IXYInput * Strafe;
	IXInput * Rotate;
	
};

#endif
