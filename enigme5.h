#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_gfxPrimitives.h>

// structure qui contient l ensemble des paramets pour preparer une imager a etre bliter
typedef struct Image
{
    SDL_Rect posfromimg;  // to save the x,y,w,h cordinates of an image //position of display in the screen
    SDL_Rect posinscreen; // position of the photo taken
    SDL_Surface *img;     // contain the img
} Image;

 
 typedef struct Enigme_image
{
    char solution; // enhi reponse s7i7e i wela j wela u ,i 
    int solved;//esqt cec que howa jebe wela le
   // int diplayscore;//est ce que n affiche score wela lé
    char enigmeimg[256];//nsager fiha ween mawjood l enigme
    Image backgroundenigme, question;//image lele background enigme w lele question w reponse
    Image won, lost, timeout;//image le ma7totine
 } Enigme_image;
 



 void geneerEnigme(Enigme_image *p, char *nomfichier);//generation aleatoire du question
 void affiche_image(Image c,SDL_Surface *screen);//affichage de l enigme
  
//les initialisation des images 
  void initilisationimagebackground(Enigme_image *c);
 void initilisation_won(Enigme_image *c);
 void initilisation_lost(Enigme_image *c);
 void initilisation_question_image(Enigme_image *c);