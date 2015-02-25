#ifndef SHS2605_WINCHPOSITIONACTION_H
#define SHS2605_WINCHPOSITIONACTION_H

#include <Hardware/Drive/LinearSlide.h>

#include <Actions/IAction.h>

class WinchPositionAction : public IAction
{
public:
	
	WinchPositionAction ( LinearSlide * Winch, double Position, double Tolerance );
	~WinchPositionAction ();
	
	void Reset ();
	
	void Start ();
	bool IsComplete ();
	void Stop ();
	
	void Update ();
	
private:
	
	LinearSlide * Winch;
	
	double Position;
	double Tolerance;
	
};

#endif
