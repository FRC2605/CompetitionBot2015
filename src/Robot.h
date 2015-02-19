#ifndef SHS2605_ROBOT_H
#define SHS2605_ROBOT_H

#include <WPILib.h>

#include <Hardware/Motors/CANTalonConfiguration.h>
#include <Hardware/Drive/CANTalonPositionServo.h>
#include <Hardware/Drive/CANTalonQuadDriveBase.h>
#include <Hardware/Drive/LinearSlide.h>
#include <Hardware/Drive/MecanumDriveTrain.h>
#include <Hardware/Drive/Filters/MecanumVelocityProfile.h>
#include <Hardware/Drive/Filters/MecanumMagDirOrientationOffset.h>

#include <COM/WPICom.h>

#include <Sensing/DIO/DIOSwitchLimit.h>
#include <Sensing/Nav6/Nav6.h>
#include <Sensing/Nav6/Nav6YawAngularInput.h>

#include <DSInput/JoystickXYInput.h>
#include <DSInput/JoystickButtonInput.h>

#include <Behaviors/BehaviorController.h>
#include <RobotBehaviors/WinchControlBehavior.h>

#include "RobotBehaviors/JoystickMecanumDriveBehavior.h"
#include "RobotBehaviors/WinchHomingBehavior.h"

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
	
	SerialPort Nav6Port;
	WPICom Nav6Com;
	Nav6 Nav;
	Nav6YawAngularInput Nav6YawInput;
	
	MecanumMagDirOrientationOffset OrientationOffset;
	MecanumVelocityProfile VProfile;
	
	MecanumDriveTrain Drive;
	
	// Winch
	CANTalonPositionServo WinchServo;
	LinearSlide Winch;
	
	// Ballast
	
	CANTalonPositionServo BallastServo;
	
	DigitalInput BallastLowLimit;
	DIOSwitchLimit BallastLimits;
	
	LinearSlide Ballast;
	
	// Input
	Joystick StrafeStick;
	Joystick RotateStick;
	Joystick DSButtons;
	
	JoystickXYInput StrafeInput;
	JoystickXYInput RotateInput;
	
	JoystickButtonInput WinchUpButton;
	JoystickButtonInput WinchDownButton;
	
	JoystickButtonInput FinePositioningButton;
	
	JoystickButtonInput WinchButton0;
	JoystickButtonInput WinchButton1;
	JoystickButtonInput WinchButton2;
	JoystickButtonInput WinchButton3;
	JoystickButtonInput WinchButton4;
	JoystickButtonInput WinchButton5;
	
	JoystickButtonInput BallastButton0;
	JoystickButtonInput BallastButton1;
	
	// Behaviors
	BehaviorController Behaviors;
	
	WinchControlBehavior :: PositionTargetButton WinchPosition0;
	WinchControlBehavior :: PositionTargetButton WinchPosition1;
	WinchControlBehavior :: PositionTargetButton WinchPosition2;
	WinchControlBehavior :: PositionTargetButton WinchPosition3;
	WinchControlBehavior :: PositionTargetButton WinchPosition4;
	WinchControlBehavior :: PositionTargetButton WinchPosition5;
	
	WinchControlBehavior :: PositionTargetButton BallastPosition0;
	WinchControlBehavior :: PositionTargetButton BallastPosition1;
	
	JoystickMecanumDriveBehavior DriveBehavior;
	WinchHomingBehavior HomingBehavior;
	WinchControlBehavior WinchBehavior;
	
};

#define ROBOT_CLASS Robot

#endif
