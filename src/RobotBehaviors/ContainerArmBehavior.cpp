#include "ContainerArmBehavior.h"

ContainerArmBehavior :: ContainerArmBehavior ( SpeedController * Motor, IBooleanInput * UpButton, IBooleanInput * DownButton, double SpeedUp, double SpeedDown ):
	Motor ( Motor ),
	UpButton ( UpButton ),
	DownButton ( DownButton ),
	SpeedUp ( SpeedUp ),
	SpeedDown ( SpeedDown )
{
};

ContainerArmBehavior :: ~ContainerArmBehavior ()
{
};

void ContainerArmBehavior :: Init ( BehaviorController * Controller, const char * AppliedID )
{
};

void ContainerArmBehavior :: Destroy ()
{
};

void ContainerArmBehavior :: Start ()
{

	Motor -> Set ( 0.0 );

};

void ContainerArmBehavior :: Stop ()
{

	Motor -> Set ( 0.0 );

};

void ContainerArmBehavior :: Update ()
{

	if ( UpButton -> GetBoolean () && ( ! DownButton -> GetBoolean () ) )
		Motor -> Set ( SpeedUp );
	else if ( ( ! UpButton -> GetBoolean () ) && DownButton -> GetBoolean () )
		Motor -> Set ( - SpeedDown );
	else
		Motor -> Set ( 0.0 );

};

const char * ContainerArmBehavior :: GetDefaultBehaviorID ()
{

	return AUTOBEHAVIOR_BID;

};

