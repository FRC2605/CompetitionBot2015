#ifndef SHS2605_ROBOT_H
#define SHS2605_ROBOT_H

#include <WPILib.h>

#include <Hardware/Motors/CANTalonConfiguration.h>
#include <Hardware/Drive/CANTalonPositionServo.h>
#include <Hardware/Drive/CANTalonQuadDriveBase.h>
#include <Hardware/Drive/CANTalonPSVelocityQuadBase.h>
#include <Hardware/Drive/LinearSlide.h>
#include <Hardware/Drive/MecanumDriveTrain.h>
#include <Hardware/Drive/Filters/MecanumVelocityProfile.h>
#include <Hardware/Drive/Filters/MecanumMagDirOrientationOffset.h>

#include <COM/WPICom.h>

#include <Sensing/DIO/DIOSwitchLimit.h>
#include <Sensing/Nav6/Nav6.h>
#include <Sensing/Nav6/Nav6YawAngularInput.h>

#include <Behaviors/BehaviorController.h>

#include <DriverStation/JoystickButtonInput.h>
#include <DriverStation/JoystickXYInput.h>
#include <DriverStation/JoystickOutputIndicator.h>

#include "RobotBehaviors/WinchControlBehavior.h"
#include "RobotBehaviors/JoystickMecanumDriveBehavior.h"
#include "RobotBehaviors/WinchHomingBehavior.h"
#include "RobotBehaviors/AutonomousBehavior.h"
#include "RobotBehaviors/Nav6CalibrationBehavior.h"

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
	CANTalonQuadDriveBase VelocityDriveBase;
	CANTalonPSVelocityQuadBase PositionDriveBase;
	
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
	
	JoystickButtonInput TurboButton;
	
	JoystickButtonInput WinchButton0;
	JoystickButtonInput WinchButton1;
	JoystickButtonInput WinchButton2;
	JoystickButtonInput WinchButton3;
	JoystickButtonInput WinchButton4;
	
	JoystickButtonInput BallastButton0;
	JoystickButtonInput BallastButton1;
	
	// Indication
	
	JoystickOutputIndicator WinchLight0;
	JoystickOutputIndicator WinchLight1;
	JoystickOutputIndicator WinchLight2;
	JoystickOutputIndicator WinchLight3;
	JoystickOutputIndicator WinchLight4;
	
	// Behaviors
	BehaviorController Behaviors;
	
	WinchControlBehavior :: PositionTargetButton WinchPosition0;
	WinchControlBehavior :: PositionTargetButton WinchPosition1;
	WinchControlBehavior :: PositionTargetButton WinchPosition2;
	WinchControlBehavior :: PositionTargetButton WinchPosition3;
	WinchControlBehavior :: PositionTargetButton WinchPosition4;
	
	WinchControlBehavior :: PositionTargetButton BallastPosition0;
	WinchControlBehavior :: PositionTargetButton BallastPosition1;
	
	JoystickMecanumDriveBehavior DriveBehavior;
	WinchHomingBehavior HomingBehavior;
	WinchControlBehavior WinchBehavior;
	AutonomousBehavior AutoBehavior;
	Nav6CalibrationBehavior YawCalibrationBehavior;
	
};

#define ROBOT_CLASS Robot

#endif
