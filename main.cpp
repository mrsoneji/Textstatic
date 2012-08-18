#include <iostream>
#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include </usr/include/SDL/SDL.h>
#include <SDL_mixer.h>

SDL_Surface* screen;
SDL_Event event;

/* guichan */
gcn::SDLInput* input;
gcn::SDLGraphics* graphics;
gcn::SDLImageLoader* imageLoader;

/* controles */
gcn::Gui* gui;
gcn::Container* container;
gcn::ImageFont* font;
gcn::TextBox* textbox;

/* audio */
int audio_rate = 22050;
Uint16 audio_format = AUDIO_S16SYS;
int audio_channels = 2;
int audio_buffers = 4096;

Mix_Chunk *sound = NULL;

int main(int argc, char *argv[]) 
{
	bool running = true;
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	screen = SDL_SetVideoMode(1680, 1050, 32, SDL_FULLSCREEN | SDL_HWSURFACE);
    SDL_EnableUNICODE(1);
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		running = false;
	}

	sound = Mix_LoadWAV("typewriter.wav");
	Mix_Volume(1,MIX_MAX_VOLUME/4);

    imageLoader = new gcn::SDLImageLoader();
    gcn::Image::setImageLoader(imageLoader);
    graphics = new gcn::SDLGraphics();
    graphics->setTarget(screen);
    input = new gcn::SDLInput();

    font = new gcn::ImageFont("fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    gcn::Widget::setGlobalFont(font); 

    gui = new gcn::Gui();
    gui->setGraphics(graphics);
    gui->setInput(input);

    container = new gcn::Container();
    container->setDimension(gcn::Rectangle(0, 0, 1680, 1050));
    gui->setTop(container);
    
    textbox = new gcn::TextBox("ahsdfkljahsfkljashdfkljh");
    textbox->setPosition(0, 0);
    textbox->setEditable(true);
    textbox->setSize(1680, 1050);
    container->add(textbox); 

	while (running)
	{
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {  
                    running = false;
                }

                Mix_PlayChannel(1, sound, 0);
            }
            else if(event.type == SDL_QUIT)
            {
                running = false;
            }
			
			textbox->setSize(1680, 1050);

			input->pushInput(event);
        }

       	gui->logic();
       	gui->draw();

		SDL_Flip(screen);
	}

	return 0;
}
