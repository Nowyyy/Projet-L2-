/**
*\file clavier.c
*\author Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas
*\date 13/05/2020
*\version 1.0

*\brief Gère tous les évènements au clavier
*/



#include "../include/constantes.h"


//Ecrit par Aurélien Tudoret

/**
*\fn void init_tab_clavier(int tab[])

*\param tab[] le tableau contenant les touches du clavier qui ont été appuyées

*\brief initialise le tableau d'evenement
*/
void init_tab_clavier(int tab[]){

	for(int i = 0; i < NB_TOUCHES_UTILISEES; i++)
		tab[i] = 0;
}


//Ecrit par Aurélien Tudoret. Ajout par Axel Jourry

/**
*\fn void event_clavier(touches_t *clavier, SDL_Event event)

*\param *clavier la structure contenant les touches du clavier

*\param event l'evenement lu au clavier

*\brief Range dans un tableau les evenements lus au clavier
*/
void event_clavier(touches_t *clavier, SDL_Event event){

	if(event.type == SDL_KEYDOWN){

		if(event.key.keysym.sym == SDLK_UP){
			clavier->tab[up] = TRUE;
		}
		else if(event.key.keysym.sym == SDLK_DOWN){
			clavier->tab[down] = TRUE;
		}
		else if(event.key.keysym.sym == SDLK_RETURN){
			clavier->tab[entree] = TRUE;
		}
		else if(event.key.keysym.sym == SDLK_LEFT){
			clavier->tab[left] = TRUE;
		}
		else if(event.key.keysym.sym == SDLK_RIGHT){
			clavier->tab[right] = TRUE;
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE){
			clavier->tab[escape] = TRUE;
		}
	}

	if(event.type == SDL_KEYUP){

		if(event.key.keysym.sym == SDLK_UP){
			clavier->tab[up] = FALSE;
		}
		else if(event.key.keysym.sym == SDLK_DOWN){
			clavier->tab[down] = FALSE;
		}
		else if(event.key.keysym.sym == SDLK_RETURN){
			clavier->tab[entree] = FALSE;
		}
		else if(event.key.keysym.sym == SDLK_LEFT){
			clavier->tab[left] = FALSE;
		}
		else if(event.key.keysym.sym == SDLK_RIGHT){
			clavier->tab[right] = FALSE;
		}
		else if(event.key.keysym.sym == SDLK_ESCAPE){
			clavier->tab[escape] = FALSE;
		}
	}
}
