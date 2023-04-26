#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
#include "enigme5.h"

int main(int argc, char *argv[])
{
    int whichscreen = 1; // keni 0 bech t affichli enigme sinon keni 1 bech t affichili menu input
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    TTF_Init();

    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1)
    {
        printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1000) == -1)
    {
        printf("Error opening audio: %s\n", Mix_GetError());
        return 1;
    }
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(1250, 666, 32, SDL_HWSURFACE | SDL_RESIZABLE);
    if (!screen)
    {
        printf("unable to set 1250x666 video: %s\n", SDL_GetError());
        return 1;
    }
    Mix_Music *music = Mix_LoadMUS("src_enigme_image/music/trimed.mp3");
    Mix_Music *music_win = Mix_LoadMUS("src_enigme_image/music/success-fanfare-trumpets-6185.mp3");
    if (!music)
    {
        printf("Error loading sound: %s\n", Mix_GetError());
        return 1;
    }
    Mix_PlayMusic(music, 1); // -1 to loop indefinitely

    // Set the window caption
    SDL_WM_SetCaption("SDL Game", NULL);

    // Set up the event loop
    SDL_Event event;
    int done = 0;
    Mix_VolumeMusic(60);
    //**********************************************************
    Uint32 t_prev2, t_prev1, t_prev3;
    Enigme_image enigme_img;
    initilisationimagebackground(&enigme_img);                   //<--------
    geneerEnigme(&enigme_img, "src_enigme_image/questions.txt"); //<--------
    initilisation_question_image(&enigme_img);                   //<--------
    // Set the font for the primitives drawing routines
    gfxPrimitivesSetFont(NULL, 0, 0);
    // Zoom the image by a factor of 2
    SDL_Surface *zoomed = NULL;
    //**********************input
      while (!done)
    {
         
        

            // Process events
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    done = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_RETURN:

                        break;
                    case SDLK_ESCAPE:
                        done = 1;
                        break;
                    case SDLK_UP:

                        break;
                    case SDLK_DOWN:

                        break;
                    case SDLK_u:
                        if (enigme_img.solved == 0) // tant que howa
                        {
                            Mix_HaltMusic();
                            if ('u' == enigme_img.solution) // kena nzelu w howa reponse s7i7a alors solved =2 sinon =3
                            {
                                enigme_img.solved = 2;
                            }
                            else
                                enigme_img.solved = 3;
                        }
                        break;
                    case SDLK_i:
                        if (enigme_img.solved == 0)
                        {
                            Mix_HaltMusic();

                            if ('i' == enigme_img.solution)
                            {
                                enigme_img.solved = 2;
                            }
                            else
                                enigme_img.solved = 3;
                        }

                        break;
                     case SDLK_k:
                        if (enigme_img.solved == 0)
                        {
                            Mix_HaltMusic();

                            if ('k' == enigme_img.solution)
                            {
                                enigme_img.solved = 2;
                            }
                            else
                                enigme_img.solved = 3;
                        }

                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
            
                    break;
                }
            }

            if (SDL_GetTicks() - t_prev1 > 2000 && enigme_img.solved == 0) // nod5el lel fonction kol 2s w tan que howa mezel mejebch ma3neha solved mezelt 0
            {

                SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255)); // affichage background bidha
                affiche_image(enigme_img.backgroundenigme, screen);                    // affichage de l enigme background
                affiche_image(enigme_img.question, screen);                            // affichage mta3 l question foo9 l background

                t_prev1 = SDL_GetTicks();
            }
            else if (enigme_img.solved == 2) // keno jeweb s 7i7e
            {
                static float zoom_factor = 1.0;                                                   // nzoomi melowel b 1.0
                zoom_factor += 0.01;                                                              // zoome yemchi w yekber 0 0.01
                SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));            // n aficher background bidhe
                zoomed = zoomSurface(enigme_img.won.img, zoom_factor, zoom_factor, SMOOTHING_ON); // nesna3 surface jdida eli b zoom jdidee
                int x = (screen->w / 2) - (zoomed->w / 2);                                        // ne7seb l x eli fel woset
                int y = (screen->h / 2) - (zoomed->h / 2);                                        // ne7seb l y eli fel wose
                SDL_Rect dest = {x, y, zoomed->w, zoomed->h};                                     // nrake7 destination ween bech naffiche fi screen
                SDL_BlitSurface(zoomed, NULL, screen, &dest);                                     
           
            if(4<zoom_factor){done=1;}
            }
            else if (enigme_img.solved == 3) // keno jeweb bel 8alet
            {
                SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255)); // n aficher background bidhe
                static double angle = 0.0;
                angle += 0.1;                                                                               // nzeed fel angle de routage
                SDL_Surface *rotated_img = rotozoomSurface(enigme_img.lost.img, angle, 1.0, 0);             // nrotate l image
                SDL_Rect rect = {(screen->w - rotated_img->w) / 2, (screen->h - rotated_img->h) / 2, 0, 0}; // destination cordinate
                SDL_BlitSurface(rotated_img, NULL, screen, &rect);                                          // naffiche l image jdida b rotate
                SDL_FreeSurface(rotated_img);
                 printf("%f\n",angle);
                   if(360<angle){done=1;}
            }
        
        SDL_Flip(screen); // mettre à jour la surface de l'écran
    }
    // Clean up SDL
    SDL_Quit();

    return 0;
}
