/**
*\file confirmer_nouveau.c
*\author Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas
*\date 13/05/2020
*\version 1.0

*\brief Gère l'écrasement de la sauvegarde en cas de nouvelle partie
*/

#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/personnage.h"
#include "../include/sauvegardefonc.h"
#include "../include/fonctions.h"


//Ecrit par Axel Jourry
/**
*\fn void afficher_confirmation(SDL_Renderer *rendu, SDL_Rect rect_sel, SDL_Texture *confirmer_texture, SDL_Rect confirmer_rect, SDL_Texture *retour_texture, SDL_Rect retour_rect, SDL_Texture *message_texture, SDL_Rect message_rect)

*\param *rendu le renderer sur lequel on dessine
*\param rect_sel le rectangle de sélection du menu
*\param *confirmer_texture la texture pour le texte "Charger partie"
*\param confirmer_rect le rectangle pour confirmer l'écrasement de la partie
*\param *retour_texture la texture pour le texte "Quitter"
*\param retour_rect le rectangle pour le texte "retour"
*\param *message_texture la texture pour le texte du message
*\param message_rect le rectangke pour le texte du message

*\brief Affiche sur le rendu les différentes textures et rectangles passés en paramètre
*/
void afficher_confirmation(SDL_Renderer *rendu, SDL_Rect rect_sel, SDL_Texture *confirmer_texture, SDL_Rect confirmer_rect, SDL_Texture *retour_texture, SDL_Rect retour_rect, SDL_Texture *message_texture, SDL_Rect message_rect){


	SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

	SDL_RenderClear(rendu);//nettoie l'écran pour supprimer tout ce qui est dessus

	SDL_SetRenderDrawColor(rendu, 255,255,255,255); //couleur blanche pour dessiner le rectangle_selection

	SDL_RenderDrawRect(rendu, &rect_sel);

	SDL_RenderCopy(rendu, confirmer_texture, NULL, &confirmer_rect);
	SDL_RenderCopy(rendu, retour_texture, NULL, &retour_rect);
  	SDL_RenderCopy(rendu, message_texture, NULL, &message_rect);

	SDL_RenderPresent(rendu);//applique les modifs précédentes
}


//Ecrit par Axel Jourry
/**
*\fn int deplacement_rectangle_selection_confirmer(int *etat, SDL_Rect confirmer_rect, SDL_Rect retour_rect, SDL_Rect **rect_sel, Mix_Chunk *sounds[NB_SON], perso_t *pers)

*\param *etat permet de changer l'affichage selon l'écran dans lequel se trouve le jeu
*\param confirmer_rect le rectangle contenant le texte de confirmation d'ecrasement de partie
*\param retour_rect le rectangle contenant le texte "retour", pour retourner au menu principal
*\param **rect_sel le rectangle de sélection permettant de sélectionner une option
*\param *sounds[NB_SON] le tableau contenant les sons
*\param *pers la structure du personnage

*\brief Permet de déplacer d'option en option le rectangle de sélection

*\return retourne False pour fermer la fenetre, True pour la garder  ouverte
*/
int deplacement_rectangle_selection_confirmer(int *etat, SDL_Rect confirmer_rect, SDL_Rect retour_rect, SDL_Rect **rect_sel, Mix_Chunk *sounds[NB_SON], perso_t *pers){

	SDL_Event event;

	while(SDL_PollEvent(&event)){ //On attend un évènement au clavier

		if(event.type == SDL_KEYDOWN){	//touche enfoncée
			if(event.key.keysym.sym == SDLK_DOWN){
				if((*rect_sel)->y != retour_rect.y){//on n'est pas sur la dernière option, on peut descendre
					if((*rect_sel)->y == confirmer_rect.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = retour_rect.y - RECT_SELECT_Y_DIFF;
						(*rect_sel)->x = retour_rect.x - RECT_SELECT_X_DIFF;
						(*rect_sel)->w = retour_rect.w + 100;
						(*rect_sel)->h = retour_rect.h + 50;
						Mix_PlayChannel(0, sounds[move], 0);
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_UP){
				if((*rect_sel)->y != confirmer_rect.y){//on n'est pas sur la premiere option, on peut monter
					if((*rect_sel)->y == retour_rect.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = confirmer_rect.y - RECT_SELECT_Y_DIFF;
						(*rect_sel)->x = confirmer_rect.x - RECT_SELECT_X_DIFF;
						(*rect_sel)->w = confirmer_rect.w + 100;
						(*rect_sel)->h = confirmer_rect.h + 50;
						Mix_PlayChannel(0, sounds[move], 0);
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_RETURN){//touche entrée
				if((*rect_sel)->y == confirmer_rect.y - RECT_SELECT_Y_DIFF){
					*etat = labyrinthe;

					//on détruit les listes à nouveau, afin de ne pas les retrouvées remplies dans une nouvelle partie
					detruire_liste(COLLEC);
					detruire_liste(DECK);
					init_liste();

					Mix_PlayChannel(1, sounds[selection], 0);
				}
				else if((*rect_sel)->y == retour_rect.y - RECT_SELECT_Y_DIFF){
					*etat = mainMenu;
					Mix_PlayChannel(1, sounds[selection], 0);
				}
			}
		}

		if(event.type == SDL_QUIT)//croix de la fenetre
			return FALSE;
	}

	return TRUE;
}


//Ecrit par Axel Jourry
/**
*\fn void menu_confirmation(int *continuer, int *etat, SDL_Renderer *rendu, TTF_Font *police, Mix_Chunk *sounds[NB_SON], perso_t *pers)

*\param *continuer le pointeur sur un int permettant de savoir si le joueur veut quitter le jeu
*\param *etat le pointeur sur un int permettant de connaitre le prochain écran auquel le joueur veut accèder
*\param *rendu le renderer sur lequel on dessine
*\param *police la police d'écriture pour TTF
*\param *sounds[NB_SON] le tableau contenant les sons
*\param *pers la structure du personnage

*\brief Permet d'afficher un menu confirmant l'écrasement de la sauvegarde et de l'écraser ou non en fonction du choix du joueur
*/
void menu_confirmation(int *continuer, int *etat, SDL_Renderer *rendu, TTF_Font *police, Mix_Chunk *sounds[NB_SON], perso_t *pers){

	SDL_Rect retour_rect, confirmer_rect, message_rect;
	SDL_Rect *rectangle_selection = malloc(sizeof(SDL_Rect));

	SDL_Texture *retour_texture, *confirmer_texture, *message_texture;

	char retour_text[] = "Retourner au menu principal", confirmer_text[] = "Ecraser la partie", message_text[] = "Sauvegarde existante. Ecraser partie ?" ;

	int x_retour, x_confirmer, y_retour, y_confirmer, x_message, y_message;

	x_retour = WIN_WIDTH * 0.28;
	y_retour = WIN_HEIGHT * 0.75;

	x_confirmer = WIN_WIDTH * 0.37-10;
	y_confirmer = WIN_HEIGHT * 0.50;

  x_message = WIN_WIDTH * 0.20;
  y_message = WIN_HEIGHT * 0.15;

	SDL_Color color_text={134, 134, 134};



	//On créé les textures qui contiendront les textes
	get_text_and_rect(rendu, x_confirmer, y_confirmer, confirmer_text, police, &confirmer_texture, &confirmer_rect);
	get_text_and_rect(rendu, x_retour, y_retour, retour_text, police, &retour_texture, &retour_rect);
  get_text_and_rect_color(rendu, x_message, y_message, message_text, police, &message_texture, &message_rect, color_text);

	rectangle_selection->x = x_retour - RECT_SELECT_X_DIFF;
	rectangle_selection->y = y_retour - RECT_SELECT_Y_DIFF;
	rectangle_selection->w = retour_rect.w + 100;
	rectangle_selection->h = retour_rect.h + 50;

	while(*continuer && *etat == confirmer_nouveau){

		afficher_confirmation(rendu, *rectangle_selection, confirmer_texture, confirmer_rect, retour_texture, retour_rect, message_texture, message_rect);

		*continuer = deplacement_rectangle_selection_confirmer(etat, confirmer_rect, retour_rect, &rectangle_selection, sounds, pers);
	}

	if(rectangle_selection != NULL){
		free(rectangle_selection);
		rectangle_selection=NULL;
	}

	libere_texture(&message_texture);
	libere_texture(&confirmer_texture);
	libere_texture(&retour_texture);
}
