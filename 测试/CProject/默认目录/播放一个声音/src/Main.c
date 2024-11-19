#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

// Function for loading music to Mix_Music
static Mix_Music *loadMusic(const char *path)
{
    Mix_Music *usic = Mix_LoadMUS(path);
    if (usic == NULL)
    {
        fprintf(stderr, "Mix_LoadMUS Error: %s\n", Mix_GetError());
        return NULL;
    }
    return usic;
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Hello SDL2-mixer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    if (window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        fprintf(stderr, "Mix_OpenAudio Error: %s\n", Mix_GetError());
        return 1;
    }
    Mix_Music *music = loadMusic("music.ogg");
    if (music == NULL)
    {
        fprintf(stderr, "Couldn't load music\n");
        return 1;
    }
    if (Mix_PlayMusic(music, 1) == -1)
    {
        fprintf(stderr, "Couldn't play music\n");
        return 1;
    }
    while (Mix_PlayingMusic())
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                Mix_HaltMusic(); // Stop the music
                break;
            }
            // Process other events if necessary
        }
    }
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}