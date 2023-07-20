#include <iostream>
#include "print.h"
#include "pong.h"
#include "game.h"

using namespace std;



int main(int argc, char* argv[])
{
    cout << "Hello World!" << endl;

	print("Number:", 3, 0.5);

	Pong pong = Pong("Pong", 800, 600);

	while (pong.running())
	{
		pong.frameStart();
		pong.handleEvents();
		pong.update();
		pong.render();
		pong.frameEnd();
	}
    return 0;
}