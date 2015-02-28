#ifndef SHS2605_BALLASTPOSITIONACTION_H
#define SHS2605_BALLASTPOSITIONACTION_H

#include <Hardware/Drive/LinearSlide.h>

#include <Actions/IAction.h>

class BallastPositionAction : public IAction
{
public:
	
	BallastPositionAction ( LinearSlide * Ballast, double Position, double Tolerance );
	~BallastPositionAction ();
	
	void Reset ();
	
	void Start ();
	bool IsComplete ();
	void Stop ();
	
	void Update ();
	
private:
	
	LinearSlide * Ballast;
	
	double Position;
	double Tolerance;
	
};

#endif
