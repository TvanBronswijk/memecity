#include <SDL.h>
#include <iostream>

bool is_running = true;
SDL_Event event;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	const auto window = SDL_CreateWindow("SDL TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
		SDL_WINDOW_SHOWN);

	while (is_running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_q:
					is_running = false;

				case SDLK_DOWN:
					std::cout << "Down";
					break;

				case SDLK_UP:
					std::cout << "Up";
					break;

				default:
					std::cout << event.key.keysym.sym;
					break;
				}
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}