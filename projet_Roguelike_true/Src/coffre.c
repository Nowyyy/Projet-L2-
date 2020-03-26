/**
*\file coffre.c
*\author Tudoret Aurélien
*\date 14/03/2020
*\version 0.1

*\brief permet de gérer animation et drop d'objets des coffres
*/


#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/fonctions.h"


/**
*\fn void animation_coffre(perso_t *pers)

*\param *pers, le personnage du jeu
*\param *salle, la salle dans laquelle se trouve le personnage
*\param *sounds[NB_SON], tableau contenant les sons

*\brief Permet d'effectuer l'animation du coffre s'il est en contact avec le joueur
*/
void animation_coffre(perso_t *pers, salle_t *salle, Mix_Chunk *sounds[NB_SON]){

	if(salle->coffre_salle.ouvert == 0 && (salle->coffre && (SDL_HasIntersection(&pers->sprites[courant].rectangle, &salle->coffre_salle.sprite.rectangle) || salle->coffre_salle.courant > 0))){
		//on est dans une salle avec un coffre et il n'a pas été ouvert

		if(salle->coffre_salle.courant < salle->coffre_salle.nb_sprites -1 && salle->coffre_salle.last + DELAIS_ANIMATIONS + 50 <= SDL_GetTicks()){

			salle->coffre_salle.sprite_courant.x += salle->coffre_salle.sprite_courant.w + salle->coffre_salle.gap;
			salle->coffre_salle.courant ++;
			salle->coffre_salle.last = SDL_GetTicks();

			if(salle->coffre_salle.son == 0){
				Mix_PlayChannel(2, sounds[chest], 0);
				salle->coffre_salle.son = 1;
			}


		}
		else if (salle->coffre_salle.courant == salle->coffre_salle.nb_sprites -1){
			salle->coffre_salle.ouvert = 1;
		}

	}

}



void creer_coffre(coffre_t *coffre, SDL_Renderer *rendu, int coffre_existe){

	if(coffre_existe){

		charge_image(COFFRE_PATH, &coffre->sprite, rendu);

		coffre->ouvert = 0;
		coffre->nb_sprites = 5;
		coffre->courant = 0;
		coffre->gap = 68;
		coffre->son = 0;

		coffre->last = SDL_GetTicks();

		coffre->sprite_courant.x = 0;
		coffre->sprite_courant.y = 0;
		coffre->sprite_courant.w = 39;
		coffre->sprite_courant.h = 50;

		coffre->sprite.rectangle.w = coffre->sprite_courant.w * 1.3;
		coffre->sprite.rectangle.h = coffre->sprite_courant.h * 1.3;
		coffre->sprite.rectangle.x = WIN_WIDTH / 2 - coffre->sprite.rectangle.w / 2;
		coffre->sprite.rectangle.y = WIN_HEIGHT / 2 - coffre->sprite.rectangle.h / 2;
	}
}



/**
*\fn void destruction_des_coffres(salle_t salles[], int taille)

*\param salles[], le tableau contenant toutes les salles du labyrinthe
*\param taille, la taille du tableau de salles

*\brief Libère tous les emplacements mémoires attribués aux coffres
*/
void destruction_des_coffres(salle_t salles[], int taille){

	int i;

	for(i = 0; i < taille * taille; i++){

		if(salles[i].coffre)
			libere_texture(&salles[i].coffre_salle.sprite.img);
	}
}


/**
*\fn


*/
void creer_texte_coffre(char *txt, image_t *image, int x, int y, SDL_Renderer *rendu){

	TTF_Font *font;

	font = TTF_OpenFont(FONT_PATH, 30);

	image->rectangle.x = x;
	image->rectangle.y = y;

	get_text_and_rect(rendu,image->rectangle.x, image->rectangle.y, txt, font, &image->img, &image->rectangle);

	TTF_CloseFont(font);
}



void loot_de_carte(loot_carte_t *loot, SDL_Renderer *rendu, coffre_t coffre, int etage){

	if(coffre.ouvert && loot->existe == 0){

		loot->existe = 1;

		loot->carte = generer_carte(etage);

		printf("%s\n", loot->carte->nom);

		ajout_carte_deck(loot->carte);
		ajout_carte_collec(loot->carte);

		loot->delai = DUREE_AFFICHAGE_CARTE_LOOT;

		loot->debut = SDL_GetTicks();

		creer_texte_coffre("Vous avez trouve :", &loot->texte, 0, 0, rendu);
	}
}
