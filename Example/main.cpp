
#include "sfwdraw.h"
#include "GameState.h"
#include <time.h>


/*
	The main function should be used for application state management.
	Currently, only one state is implemented here, you'll need to add additional
	and get them to behave properly.
*/
void main()
{
	sfw::initContext(1600U, 900);

	srand(time(0));

	GameState gs;

	gs.init(); // called once

	gs.play(); // Should be called each time the state is transitioned into

	while (sfw::stepContext())
	{
		gs.step(); // called each update
		gs.draw(); // called each update

		//gs.next(); Determine the ID of the next state to transition to.
	}

	gs.stop(); // should be called each time the state is transitioned out of

	gs.term(); // called once


	sfw::termContext();

}