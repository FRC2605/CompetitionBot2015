#include "Nav6CalibrationBehavior.h"

Nav6CalibrationBehavior :: Nav6CalibrationBehavior ( MecanumMagDirOrientationOffset * Offset, double StartingOffset ):
	Offset ( Offset ),
	StartingOffset ( StartingOffset )
{	
};

Nav6CalibrationBehavior :: ~Nav6CalibrationBehavior ()
{
};

void Nav6CalibrationBehavior :: Init ( BehaviorController * Controller, const char * AppliedID )
{
};

void Nav6CalibrationBehavior :: Destroy ()
{
};

void Nav6CalibrationBehavior :: Start ()
{
};

void Nav6CalibrationBehavior :: Stop ()
{
	
	Offset -> CalibrateZero ( StartingOffset );
	
};

void Nav6CalibrationBehavior :: Update ()
{
};

const char * Nav6CalibrationBehavior :: GetDefaultBehaviorID ()
{
	
	return NAV6CALIB_BID;
	
};

