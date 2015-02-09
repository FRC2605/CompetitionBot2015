#ifndef SHS2605_ROBOT_H
#define SHS2605_ROBOT_H

#include <WPILib.h>

#include <Input/SmartJoystick.h>

#include "Hardware/Motors/CANTalonConfiguration.h"

#include "Hardware/Drive/CANTalonQuadDriveBase.h"
#include "Hardware/Drive/MecanumDriveTrain.h"

#include "Hardware/Drive/Filters/MecanumVelocityProfile.h"
#include "Hardware/Drive/Filters/MecanumMagDirOrientationOffset.h"

#include "Hardware/Drive/Filters/MecanumVelocityProfile.h"

class Robot : public IterativeRobot
{
public:
	
	Robot ();
	~Robot ();
	void TeleopInit ();
	void DisabledInit ();
	
	void TeleopPeriodic ();
	void DisabledPeriodic ();

private:
	CANTalonConfiguration WheelConfig;
	
	MecanumVelocityProfile VProfile;

	CANTalonQuadDriveBase DriveBase;
	MecanumDriveTrain DriveTrain;

	SmartJoystick StrafeStick;
	SmartJoystick RotateStick;

	Talon Lift;
	
};

#define ROBOT_CLASS Robot

#endif
