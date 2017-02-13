
#include "../sfw/sfwdraw.h"
#include "GameState.h"


void main()
{
	sfw::initContext();


	GameState gs;

	gs.init();
	gs.play();

	while (sfw::stepContext())
	{
		gs.step();
		gs.draw();
	}

	gs.stop();
	gs.term();


	sfw::termContext();

}