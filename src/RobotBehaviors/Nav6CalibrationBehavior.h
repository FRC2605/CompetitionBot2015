#ifndef SHS2605_NAV6CALIBRATIONBEHAVIOR_H
#define SHS2605_NAV6CALIBRATIONBEHAVIOR_H

#include <Behaviors/IBehavior.h>

#include <Hardware/Drive/Filters/MecanumMagDirOrientationOffset.h>

#define NAV6CALIB_BID "nav6_yaw_calibration"

class Nav6CalibrationBehavior : public IBehavior
{
public:
	
	Nav6CalibrationBehavior ( MecanumMagDirOrientationOffset * Offset, double StartingOffset );
	~Nav6CalibrationBehavior ();
	
	void Init ( BehaviorController * Controller, const char * AppliedID );
	void Destroy ();
	
	void Start ();
	void Stop ();
	
	void Update ();
	
	static const char * GetDefaultBehaviorID ();

private:
	
	MecanumMagDirOrientationOffset * Offset;
	
	double StartingOffset;
	
};



#endif
