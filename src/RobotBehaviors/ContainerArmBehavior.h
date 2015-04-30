#ifndef SHS2605_CONTAINERARMBEHAVIOR_H
#define SHS2605_CONTAINERARMBEHAVIOR_H

#include <WPILib.h>

#include <Behaviors/IBehavior.h>
#include <Actions/ActionController.h>

#include <Sensing/IBooleanInput.h>

#define AUTOBEHAVIOR_BID "containerarm"

class ContainerArmBehavior : public IBehavior
{
public:

	ContainerArmBehavior ( SpeedController * Motor, IBooleanInput * UpButton, IBooleanInput * DownButton, double SpeedUp, double SpeedDown );
	~ContainerArmBehavior ();

	void Init ( BehaviorController * Controller, const char * AppliedID );
	void Destroy ();

	void Start ();
	void Stop ();

	void Update ();

	static const char * GetDefaultBehaviorID ();

private:

	IBooleanInput * UpButton;
	IBooleanInput * DownButton;

	double SpeedUp;
	double SpeedDown;

	SpeedController * Motor;

};

#endif
