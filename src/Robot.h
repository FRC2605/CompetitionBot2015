#ifndef SHS2605_ROBOT_H
#define SHS2605_ROBOT_H

#include <WPILib.h>

#include <Hardware/Motors/CANTalonConfiguration.h>
#include <Hardware/Drive/CANTalonPositionServo.h>
#include <Hardware/Drive/CANTalonQuadDriveBase.h>
#include <Hardware/Drive/LinearSlide.h>

#include <Hardware/Drive/MecanumDriveTrain.h>
#include <Hardware/Drive/Filters/MecanumVelocityProfile.h>

#include <Sensing/DIO/DIOSwitchLimit.h>

#include <DSInput/JoystickXYInput.h>
#include <DSInput/JoystickButtonInput.h>

#include <Behaviors/BehaviorController.h>

#include "RobotBehaviors/JoystickMecanumDriveBehavior.h"
#include "RobotBehaviors/WinchHomingBehavior.h"
#include "Robotbehaviors/WinchControllBehavior.h"

class Robot : public IterativeRobot
{
public:
	
	Robot ();
	~Robot ();
	
	void TeleopInit ();
	void TestInit ();
	void AutonomousInit ();
	void DisabledInit ();
	
	void TeleopPeriodic ();
	void TestPeriodic ();
	void AutonomousPeriodic ();
	void DisabledPeriodic ();
	
private:
	
	// Drive
	CANTalonConfiguration WheelConfig;
	CANTalonQuadDriveBase DriveBase;
	
	MecanumVelocityProfile VProfile;
	
	MecanumDriveTrain Drive;
	
	// Winch
	CANTalonPositionServo WinchServo;
	
	DigitalInput WinchLimitHigh;
	DigitalInput WinchLimitLow;
	DIOSwitchLimit WinchLimits;
	
	LinearSlide Winch;
	
	// Input
	Joystick StrafeStick;
	Joystick RotateStick;
	
	JoystickXYInput StrafeInput;
	JoystickXYInput RotateInput;
	
	JoystickButtonInput WinchUpButton;
	JoystickButtonInput WinchDownButton;
	
	// Behaviors
	BehaviorController Behaviors;
	
	JoystickMecanumDriveBehavior DriveBehavior;
	WinchHomingBehavior HomingBehavior;
	WinchControllBehavior WinchBehavior;
	
};

#define ROBOT_CLASS Robot

#endif
