/**
*\file initialisation_sdl_fonctions.c
*\author Jourry Axel, Tudoret Aurélien, Malabry Thomas, Marin Timothée
*\date 13/05/2020
*\version 1.0
*\brief fonctions de la sdl pour son initialisation, fichier .c
*/
#include "../include/constantes.h"


//Ecrit par Aurélien Tudoret
/**
*\fn int initialisation_sdl(SDL_Window **window, SDL_Renderer **rendu)

*\param **window contient la fenetre du jeu
*\param **rendu le rendu dans la fenetre sur lequel on dessinera par la suite

*\return 0 si tout c'est bien passé, 1 si une erreur est apparue

*\brief Initialise et créé fenetre et rendu par leur pointeur, si une initialisation échoue, on détruit tout et on retourne 1 pour signifier une erreur
*/
int initialisation_sdl(SDL_Window **window, SDL_Renderer **rendu){

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		return 1;

	*window = SDL_CreateWindow("Dungeon Of Cards", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);

	if(window == NULL)
		return 1;

	*rendu = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

	if(rendu == NULL){
		if(*window != NULL){
			SDL_DestroyWindow(*window);
			*window=NULL;
		}
		return 1;
	}

	return 0;
}


//Ecrit par Aurélien Tudoret
/**
*\fn void quit_sdl(SDL_Renderer **rendu, SDL_Window **window)

*\param **window contient la fenetre du jeu que l'on veut détruire
*\param **rendu le rendu dans la fenetre que l'on veut détruire

*\brief détruit les renderer et window passés en paramètre
*/
void quit_sdl(SDL_Renderer **rendu, SDL_Window **window){

	if(*rendu != NULL){
		SDL_DestroyRenderer(*rendu);
		*rendu=NULL;
	}
	if(*window != NULL){
		SDL_DestroyWindow(*window);
		*window=NULL;
	}

}


//Ecrit par Aurélien Tudoret
/**
*\fn int init_or_quit_ttf(int action)

*\param action permet de définir si l'on souhaite initialiser ttf ou le fermer

*\return 0 si tout c'est bien passé, 1 si une erreur est apparue

*\brief Initialise la librairie ttf
*/
int init_or_quit_ttf(int action){

	if(action){
		if(TTF_Init() != 0)
			return 1;
		else
			return 0;
	}
	else{
		TTF_Quit();
		return 0;
	}
}


//Ecrit par Axel Jourry
/**
*\fn extern void get_text_and_rect_color(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, SDL_Color textColor)

*\param renderer le rendu sur lequel on va dessiner le texte
*\param x la position x a laquelle sera le texte
*\param y la position y a laquelle sera le texte
*\param *text le texte que l'on souhaite dessiner à l'écran
*\param *font la police utilisée pour écrire
*\param **texture la texture qui contiendra le texte
*\param *rect le rectangle qui contiendra la texture
*\param textColor la couleur du texte

*\brief Modifie une texture et un rect afin d'afficher le texte aux coordonnées données sur le renderer avec la police
*/
extern void get_text_and_rect_color(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect, SDL_Color textColor){

    int text_width;
    int text_height;
    SDL_Surface *surface;

    surface = TTF_RenderText_Solid(font, text, textColor);

    *texture = SDL_CreateTextureFromSurface(renderer, surface);

    text_width = surface->w;
    text_height = surface->h;

		if(surface != NULL){
			SDL_FreeSurface(surface);
			surface=NULL;
		}


    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}


//Ecrit par Aurélien Tudoret
/**
*\fn extern void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect)

*\param *renderer le rendu sur lequel on va dessiner le texte
*\param x la position x a laquelle sera le texte
*\param y la position y a laquelle sera le texte
*\param *text le texte que l'on souhaite dessiner à l'écran
*\param *font la police utilisée pour écrire
*\param **texture la texture qui contiendra le texte
*\param *rect le rectangle qui contiendra la texture

*\brief Modifie une texture et un rect afin d'afficher le texte aux coordonnées données sur le renderer avec la police
*/
extern void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect){

    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);

    *texture = SDL_CreateTextureFromSurface(renderer, surface);

    text_width = surface->w;
    text_height = surface->h;

		if(surface != NULL){
			SDL_FreeSurface(surface);
			surface=NULL;
		}


    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}


//Ecrit par Aurélien Tudoret
/**
*\fn int charge_image(char *path_img, image_t *struct_image, SDL_Renderer *rendu)

*\param *path_img contient le chemin et nom de l'image que l'on souhaite charger
*\param *struct_image une structure contenant les  champs nécessaires pour afficher l'image
*\param *rendu le rendu sur lequel on souhaite dessiner

*\brief charge une image dans une structure pouvant la contenir

*\return 1 si echec, 0 si réussite
*/
int charge_image(char *path_img, image_t *struct_image, SDL_Renderer *rendu){

	SDL_Surface *image = IMG_Load(path_img);

	struct_image->img = SDL_CreateTextureFromSurface(rendu, image);

	struct_image->rectangle.w = image->w;
	struct_image->rectangle.h = image->h;

	if(image != NULL){
		SDL_FreeSurface(image);
		image=NULL;
	}


	return 0;
}


//Créé par Axel Jourry
/**
*\fn void init_son(Mix_Chunk* sounds[NB_SON])

*\param *sounds[NB_SON] un tableau contenant les emplacements de chaque son

*\brief initialise un tableau avec tous les sons utilisés
*/
void init_son(Mix_Chunk* sounds[NB_SON]){

	sounds[move] = Mix_LoadWAV("../Sound/menu_move.wav");
	sounds[selection] = Mix_LoadWAV("../Sound/menu_select.wav");
	sounds[change_salle] = Mix_LoadWAV("../Sound/laby_change.wav");
	sounds[footsteps] = Mix_LoadWAV("../Sound/footstep.wav");
	sounds[gameOverFrame] = Mix_LoadWAV("../Sound/gameover_frame.wav");
	sounds[death] = Mix_LoadWAV("../Sound/ennemi_death.wav");
	sounds[collect] = Mix_LoadWAV("../Sound/collect.wav");
	sounds[chest] = Mix_LoadWAV("../Sound/chest.wav");
	sounds[enterFight] = Mix_LoadWAV("../Sound/enterFight.wav");
	sounds[animDeath] = Mix_LoadWAV("../Sound/death.wav");
	sounds[punch] = Mix_LoadWAV("../Sound/punch.wav");
	sounds[heal] = Mix_LoadWAV("../Sound/soin.wav");
	sounds[sword] = Mix_LoadWAV("../Sound/sword.wav");
	sounds[rock] = Mix_LoadWAV("../Sound/rock.wav");
	sounds[potion] = Mix_LoadWAV("../Sound/potion.wav");
	sounds[divine] = Mix_LoadWAV("../Sound/divine.wav");
	sounds[bouclier] = Mix_LoadWAV("../Sound/bouclier.wav");
	sounds[poison] = Mix_LoadWAV("../Sound/poison.wav");
	sounds[bdf] = Mix_LoadWAV("../Sound/bdf.wav");


	Mix_VolumeChunk(sounds[move], 32);
	Mix_VolumeChunk(sounds[selection], 32);
	Mix_VolumeChunk(sounds[change_salle], 32);
	Mix_VolumeChunk(sounds[footsteps], 16);
	Mix_VolumeChunk(sounds[gameOverFrame], 32);
	Mix_VolumeChunk(sounds[chest], 64);
	Mix_VolumeChunk(sounds[enterFight], 32);
	Mix_VolumeChunk(sounds[animDeath], 64);
	Mix_VolumeChunk(sounds[punch], 64);
	Mix_VolumeChunk(sounds[heal], 112);
	Mix_VolumeChunk(sounds[sword], 128);
	Mix_VolumeChunk(sounds[rock], 128);
	Mix_VolumeChunk(sounds[divine], 128);
	Mix_VolumeChunk(sounds[bouclier], 128);
	Mix_VolumeChunk(sounds[poison], 64);
	Mix_VolumeChunk(sounds[bdf], 64);
}


//Créé par Axel Jourry
/**
*\fn void init_music(Mix_Music* musics[NB_MUSIC])

*\param *musics[NB_MUSIC] un tableau contenant les emplacements de chaque musiques

*\brief initialise un tableau avec toutes les musiques utilisées
*/
void init_music(Mix_Music* musics[NB_MUSIC]){

musics[menu] = Mix_LoadMUS("../Sound/menu_song.mp3");
musics[level1] = Mix_LoadMUS("../Sound/level1.mp3");
musics[gameOverMusic] = Mix_LoadMUS("../Sound/gameover.mp3");
musics[fight] = Mix_LoadMUS("../Sound/music_fight.mp3");
musics[boss] = Mix_LoadMUS("../Sound/music_boss.mp3");
musics[level2] = Mix_LoadMUS("../Sound/level2.mp3");
musics[level3] = Mix_LoadMUS("../Sound/level3.mp3");
musics[level4] = Mix_LoadMUS("../Sound/level4.mp3");
musics[level5] = Mix_LoadMUS("../Sound/level5.mp3");
musics[victory] = Mix_LoadMUS("../Sound/victory.mp3");

}


//Créé par Axel Jourry
/**
*\fn free_mixer(Mix_Music* musics[NB_MUSIC], Mix_Chunk* sounds[NB_SON])

*\param *musics[NB_MUSIC] un tableau contenant les emplacements de chaque musiques
*\param *sounds[NB_SON] un tableau contenant les emplacements de chaque son

*\brief libère tous les sons et toutes les musiques utilisées
*/
void free_mixer(Mix_Music* musics[NB_MUSIC], Mix_Chunk* sounds[NB_SON]){
	for(int i=move; i<NB_SON-1; i++){
		if(sounds[i]!= NULL){
			Mix_FreeChunk(sounds[i]);
			sounds[i]=NULL;
		}
	}

	for(int i=menu; i<NB_MUSIC-1; i++){
		if(musics[i]!=NULL){
			Mix_FreeMusic(musics[i]);
			musics[i]=NULL;
		}
	}

	Mix_CloseAudio();
}


//Créé par Axel Jourry
/**
*\fn choix_musique(Mix_Music* musics[NB_MUSIC], perso_t *pers)

*\param *musics[NB_MUSIC] un tableau contenant les emplacements de chaque musiques
*\param *pers la structure du personnage

*\brief Choisi la musique en fonction de l'étage
*/
void choix_musique(Mix_Music* musics[NB_MUSIC], perso_t *pers){
	if(pers->etage == 1){
		Mix_VolumeMusic(6);
		Mix_PlayMusic(musics[level1], -1);
	}
	else if(pers->etage == 2){
		Mix_VolumeMusic(16);
		Mix_PlayMusic(musics[level2], -1);
	}
	else if(pers->etage == 3){
		Mix_VolumeMusic(12);

		Mix_PlayMusic(musics[level3], -1);
	}
	else if(pers->etage == 4){
		Mix_VolumeMusic(18);

		Mix_PlayMusic(musics[level4], -1);
	}
	else if(pers->etage == 5){
		Mix_VolumeMusic(12);

		Mix_PlayMusic(musics[level5], -1);
	}
}

//Ecrit par Aurélien Tudoret
/**
*\fn void libere_texture(SDL_Texture **texture)

*\param **texture la texture a libérer

*\brief Libère les SDL_Textures si elle ne le sont pas déjà
*/
void libere_texture(SDL_Texture **texture){

	if(*texture != NULL){
		SDL_DestroyTexture(*texture);
		*texture = NULL;
	}
}
