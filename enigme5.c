#include "enigme5.h"

void geneerEnigme(Enigme_image *p, char *nomfichier)
{
    p->solved = 0; // par defaut not solved

    initilisation_won(p); // initlisation des images win and lost
    initilisation_lost(p);
    // initilisation_time_out(&p->timeout);
    //  Open the file for reading
    FILE *file = fopen(nomfichier, "r"); // ouvrire le fichier en mode lecture
    if (file == NULL)
    {
        fprintf(stderr, "Unable to open file: %s\n", nomfichier);
        exit(1);
    }

    // ne7seb 9adech 3andi men ligne fel fichier
    int num_lines = 0;
    char c;
    while ((c = fgetc(file)) != EOF)//3lech ne7seb f les lignes
    {
        if (c == '\n')
        {
            num_lines++;
        }
    }
    //****************************
    srand(time(NULL));                 // t assurer que random number yetbadel kol menlanci jeux
    int line_num = rand() % num_lines; // ne5ro random number me 0 7ata l 9adech 3andi men ligne

    fseek(file, 0, SEEK_SET); // nepointi 3la awel ligne mel fichier
    for (int i = 0; i < line_num; i++)
    {
        while ((c = fgetc(file)) != EOF && c != '\n')
            ;
    }
    // Once the loop has finished, the file pointer will be pointing to the beginning of the desired line.
    // At this point, the program can read the line using functions like fgets or fscanf.

    char line[256];
    fgets(line, sizeof(line), file);

    sscanf(line, "%255[^;];%c", p->enigmeimg, &p->solution); // ligne eli t7asalet 3lihe ne5ro les champ eli 7achti bihom w n7othom fi variaible

    // Close the file
    fclose(file);
}

 void affiche_image(Image c, SDL_Surface *screen)
{

    SDL_BlitSurface(c.img, &c.posfromimg, screen, &c.posinscreen);
}
//part mta3 initialisation mta3 l image
void initilisationimagebackground(Enigme_image *c)
{
    c->backgroundenigme.img = IMG_Load("src_enigme_image/background_enigme_imagee.png");
    if (c->backgroundenigme.img == NULL)
    {
        fprintf(stderr, "error loding background img enigme%s\n", TTF_GetError());
        return;
    }
    c->backgroundenigme.posfromimg.h = c->backgroundenigme.img->h;
    c->backgroundenigme.posfromimg.w = c->backgroundenigme.img->w;
    c->backgroundenigme.posfromimg.x = 0;
    c->backgroundenigme.posfromimg.y = 0;
    c->backgroundenigme.posinscreen.h = c->backgroundenigme.img->h;
    c->backgroundenigme.posinscreen.w = c->backgroundenigme.img->w;
    c->backgroundenigme.posinscreen.x = 400;
    c->backgroundenigme.posinscreen.y = 10;
}
void initilisation_won(Enigme_image *c)
{
    c->won.img = IMG_Load("src_enigme_image/winenigme.png");
    if (c->won.img == NULL)
    {
        fprintf(stderr, "error loding won img %s\n", TTF_GetError());
        return;
    }

    c->won.posfromimg.h = c->won.img->h;
    c->won.posfromimg.w = c->won.img->w;
    c->won.posfromimg.x = 0;
    c->won.posfromimg.y = 0;

    c->won.posinscreen.h = c->won.img->h;
    c->won.posinscreen.w = c->won.img->w;
    c->won.posinscreen.x = 400;
    c->won.posinscreen.y = 10;
};
void initilisation_lost(Enigme_image *c)
{
    c->lost.img = IMG_Load("src_enigme_image/lost.png");
    if (c->lost.img == NULL)
    {
        fprintf(stderr, "error loding lost img %s\n", TTF_GetError());
        return;
    }

    c->lost.posfromimg.h = c->lost.img->h;
    c->lost.posfromimg.w = c->lost.img->w;
    c->lost.posfromimg.x = 0;
    c->lost.posfromimg.y = 0;

    c->lost.posinscreen.h = c->lost.img->h;
    c->lost.posinscreen.w = c->lost.img->w;
    c->lost.posinscreen.x = 400;
    c->lost.posinscreen.y = 10;
}
 void initilisation_question_image(Enigme_image *c)
{

    char file_path[] = "src_enigme_image/";
    char full_path[256];

    strcpy(full_path, file_path);    // Copy the file path into the full path buffer
    strcat(full_path, c->enigmeimg); // Append the image file name to the full path buffer

    c->question.img = IMG_Load(full_path);

    if (c->question.img == NULL)
    {
        fprintf(stderr, "error loding background img enigme%s\n", TTF_GetError());
        return;
    }
    c->question.posfromimg.h = c->question.img->h;
    c->question.posfromimg.w = c->question.img->w;
    c->question.posfromimg.x = 0;
    c->question.posfromimg.y = 0;
    c->question.posinscreen.h = c->question.img->h;
    c->question.posinscreen.w = c->question.img->w;
    c->question.posinscreen.x = 400;
    c->question.posinscreen.y = 10;
}
