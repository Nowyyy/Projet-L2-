/**
* \file personnage.c
* \author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
* \date 04/02/2020
* \version 0.1

* \brief Gère toute la partie concernant le personnage

*/

#include "constantes.h"
#include "initialisation_sdl_fonctions.h"
#include "clavier.h"



/**

* \fn charge_sprites_personnage

* \param sprites[], tableau qui contiendra tous les sprites du personnage
* \param *rendu, le rendu sur lequel on dessinera le personnage

*\brief fonction qui charge tous les sprites du personnage
*/
void charge_sprites_personnage(image_t sprites[], SDL_Renderer *rendu){

	charge_image(SPRITE1_PATH, &sprites[idle_droite], rendu);
	charge_image(SPRITE2_PATH, &sprites[idle_gauche], rendu);
	charge_image(SPRITE3_PATH, &sprites[droite1], rendu);
	charge_image(SPRITE4_PATH, &sprites[droite2], rendu);
	charge_image(SPRITE5_PATH, &sprites[gauche2], rendu);
	charge_image(SPRITE6_PATH, &sprites[gauche1], rendu);
	charge_image(SPRITE7_PATH, &sprites[dead], rendu);
	charge_image(SPRITE8_PATH, &sprites[gauche3], rendu);
	charge_image(SPRITE9_PATH, &sprites[droite3], rendu);

	charge_image(SPRITE2_PATH, &sprites[courant], rendu);
}


/**
* \fn test_collision

* \param salle, la salle pour laquelle on test les collisions
* \param pers, le personnage pour lequel on test les collisions
* \param direction, la direction dans laquelle se rend le personnage

* \brief permet de regarder si le personnage entre en collision avec un des murs de la salle

* \return 1 en cas de collision, 0 si aucune collision
*/
int test_collision(salle_t salle, perso_t pers, int direction){

	int i = 0;

	for( ; i < salle.nb_murs; i++){

		if(direction == 0)//haut
			pers.sprites[courant].rectangle.y -= 1;
		else if(direction == 1) //droite
			pers.sprites[courant].rectangle.x += 1;
		else if(direction == 2) //bas
			pers.sprites[courant].rectangle.y += 1;
		else //gauche
			pers.sprites[courant].rectangle.x -= 1;

		if(SDL_HasIntersection(&salle.murs[i], &pers.sprites[0].rectangle)){
			return 1;
		}

		//printf("x perso %d, y perso %d, x mur +tailleimage %d, y mur, %d\n", pers.sprites[0].rectangle.x, pers.sprites[0].rectangle.y, salle.murs[i].x + TAILLE_IMAGE, salle.murs[i].y);
	}
	return 0;
}


/**

* \fn init_animations

* \param *anim, la structure qui gère les animations

* \brief Initialise la structure d'animations

*/
void init_animations(animation_t *anim){

	anim->actuel = courant;
	anim->last_use = SDL_GetTicks() - DELAIS_ANIMATIONS;
}



/**
* \fn animations_personnage

* \param sprites[], le tableau de sprites du personnage
* \param timer, le temps d'execution du jeu
* \param clavier, la structure de touches du clavier
* \param *anim, la structure qui gère les animations

* \brief permet de changer d'animation selon le déplacement du personnage

*/
void animations_personnage(image_t sprites[], unsigned int timer, touches_t clavier, animation_t *anim){

	int i;

	for(i = 0; i <= left && clavier.tab[i] != 1; i++);

	if(i <= left){
		if(anim->last_use + DELAIS_ANIMATIONS <= timer){

			if(i == right && sprites[courant].img == sprites[droite3].img){
				sprites[courant] = sprites[droite2];
				anim->actuel = droite2;
				anim->last_use = SDL_GetTicks();
			}
			else if (i == right && sprites[courant].img == sprites[droite2].img){
				sprites[courant] = sprites[droite1];
				anim->actuel = droite1;
				anim->last_use = SDL_GetTicks();
			}
			else if (i == right){
				sprites[courant] = sprites[droite3];
				anim->actuel = droite3;
				anim->last_use = SDL_GetTicks();
			}

			if(i == left && sprites[courant].img == sprites[gauche1].img){
				sprites[courant] = sprites[gauche2];
				anim->actuel = gauche2;
				anim->last_use = SDL_GetTicks();
			}
			else if (i== left && sprites[courant].img == sprites[gauche2].img){
				sprites[courant] = sprites[gauche3];
				anim->actuel = gauche1;
				anim->last_use = SDL_GetTicks();
			}
			else if (i == left ){
				sprites[courant] = sprites[gauche1];
				anim->actuel = gauche3;
				anim->last_use = SDL_GetTicks();
			}
		}
	}
	else{
		sprites[courant] = sprites[idle_droite];
		anim->actuel = idle_droite; 
		anim->last_use = SDL_GetTicks() - DELAIS_ANIMATIONS;
	}
}


/**

* \fn deplacement_personnage

* \param pers, la structure du pêrsonnage que l'on souhaite déplacer
* \param salle, la salle dans laquelle le personnage se déplace
* \param *continuer, pointeur sur variable permettant de savoir si le joueur souhaite quitter le programme

* \brief Gère les déplacement du personnage dans une salle
*/
void deplacement_personnage(perso_t *pers, salle_t salle, int *continuer, animation_t *anim){

	SDL_Event event;

	unsigned int temps = SDL_GetTicks();

	touches_t clavier;

	init_tab_clavier(clavier.tab);

	while(SDL_PollEvent(&event)){ //On attend un évènement au clavier

		event_clavier(&clavier, event);

		if(clavier.tab[down] == 1){ //touche du bas

			if(!test_collision(salle,*pers, 2)){
				pers->y += VITESSE_PERSO;
				animations_personnage(pers->sprites, temps, clavier, anim);
			}
		}
		else if(clavier.tab[right] == 1){ //touche droite
	
			if(!test_collision(salle,*pers, 1)){
				pers->x += VITESSE_PERSO;
				animations_personnage(pers->sprites, temps, clavier, anim);
			}
		}
		else if(clavier.tab[left] == 1){ //touche gauche

			if(!test_collision(salle,*pers, 3)){
				pers->x -= VITESSE_PERSO;
				animations_personnage(pers->sprites, temps, clavier, anim);
			}
		}
		else if(clavier.tab[up] == 1){ //touche haut
			
			if(!test_collision(salle,*pers, 0)){
				pers->y -= VITESSE_PERSO;
				animations_personnage(pers->sprites, temps, clavier, anim);
			}
		}
	
	if(event.type == SDL_QUIT)//croix de la fenetre
		*continuer = FALSE;
	}
		
	pers->sprites[courant].rectangle.x = pers->x;
	pers->sprites[courant].rectangle.y = pers->y;
}



/**
* \fn changement_de_salle

* \param *pers, la structure du personnage
* \param *salle, la salle dans laquelle on se trouve
* \param *continuer la variable permettant de quitter le jeu

* \brief permet de téléporter le personnage dans la salle dont il passe la porter

* \return la salle dans laquelle le joueur arrive
*/
int changement_de_salle(perso_t *pers, salle_t salle, int indice, Mix_Chunk *change_salle){

	for(int i = 0; i < salle.nb_portes; i++){

		if(SDL_HasIntersection(&salle.portes[i], &pers->sprites[0].rectangle)){

			if(salle.portes[i].y == EMPLACEMENT_DEPART_DESSIN_SALLE_Y){
			//porte en haut
				pers->x = WIN_WIDTH / 2 - TAILLE_IMAGE;
				pers->y = salle.murs[salle.nb_murs -1].y - TAILLE_IMAGE;
				Mix_PlayChannel(0, change_salle, 1);

				return salle.s_h;
			}
			else if(salle.portes[i].y == 488){
			//porte en bas
				pers->x = WIN_WIDTH / 2 - TAILLE_IMAGE;

				pers->y = salle.murs[0].y + TAILLE_IMAGE;
				Mix_PlayChannel(0, change_salle, 1);

				return salle.s_b;
			}
			else if(salle.portes[i].x == EMPLACEMENT_DEPART_DESSIN_SALLE_X){
			//porte à gauche
				pers->x = WIN_WIDTH / 2 + 100;
				pers->y = WIN_HEIGHT / 2 - TAILLE_IMAGE / 2;
				Mix_PlayChannel(0, change_salle, 1);

				return salle.s_g;
			}
			else{
			//porte à droite
				pers->x = salle.murs[0].x + TAILLE_IMAGE;
				pers->y = WIN_HEIGHT / 2 - TAILLE_IMAGE / 2;
				Mix_PlayChannel(0, change_salle, 1);

				return salle.s_d;
			}
		}
	}

	pers->sprites[courant].rectangle.x = pers->x;
	pers->sprites[courant].rectangle.y = pers->y;

	return indice;
}