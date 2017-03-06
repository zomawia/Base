// Ass3 by Zomawia Sailo
// zomawia@gmail.com

#include "sfwdraw.h"
#include "constded.h"
#include "GameState.h"
#include "MenuState.h"
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
	
	APP_STATE states = ENTER_MENU;

	GameState gs;
	MenuState ms;

	bool quit = false;

	ms.init(); // called once
	gs.init();

	 // Should be called each time the state is transitioned into

	while (sfw::stepContext() && quit == false)
	{
		switch (states) {
		case ENTER_MENU:			
			ms.play();

		case MENU:
			ms.step();
			ms.draw();
			states = (APP_STATE)ms.next();
			break;

		case EXIT_MENU:
			ms.stop();
			ms.term();
			states = EXIT;
			break;

		case ENTER_GAME:
			ms.stop();
			ms.term();
			gs.play();

		case GAME:
			gs.step();
			gs.draw();
			states = (APP_STATE)gs.next();
			break;
		
		case EXIT: quit = true;


		}
	}

	//ms.stop(); // should be called each time the state is transitioned out of

	//ms.term(); // called once


	sfw::termContext();

}
