#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

SDL_Surface *load_image(std::string filename)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());

	if( loadedImage != NULL )
	{
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
	// Temporary rectangle section to hold the offsets
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, destination, &offset);

}

int main( int argc, char* args[] )
{
	SDL_Surface *screen = NULL;
    SDL_Surface *message = NULL;
    SDL_Surface *background = NULL;

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int SCREEN_BPP = 32;

    //Start SDL
    if(SDL_Init( SDL_INIT_EVERYTHING )  != -1)
    {
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

		SDL_WM_SetCaption("Hello World - Michael Aquilina", NULL);

		background = load_image("portal.jpg");
		message = load_image("hello.bmp");

		apply_surface(0, 0, background, screen);
		apply_surface(360, 0, background, screen);
		apply_surface(0, 280, background, screen);
		apply_surface(360, 280, background, screen);

		//SDL_BlitSurface(hello, NULL, screen, NULL);
		SDL_Flip(screen);

		SDL_Delay(2000);

		SDL_FreeSurface(message);
		SDL_FreeSurface(background);

		//Quit SDL
		SDL_Quit();

		return 0;
    }
    else
    	return -1;
}
