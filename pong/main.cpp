#include "cWindow.h"
#include "cGameManager.h"

#include <time.h>

int main(int argc, char** argv)
{
	srand((unsigned)time(NULL));

	auto gameWindow = cWindow(900, 800, "2D-Pong");
	auto gameManager = cGameManager(gameWindow);
	gameManager.Update();

	return 0;
}