/**
*\file personnage.c
*\author Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas
*\date 13/05/2020
*\version 1.0

*\brief Gère toute la partie concernant le personnage
*/

#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/clavier.h"


//Ecrit par Aurélien Tudoret
/**
*\fn void charge_sprites_personnage(image_t sprites[], SDL_Renderer *rendu)

*\param sprites[] le tableau qui contiendra tous les sprites du personnage
*\param *rendu le rendu sur lequel on dessinera le personnage

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

	sprites[courant] = sprites[idle_droite];
}


//Ecrit par Aurélien Tudoret
/**
*\fn int test_collision(salle_t salle, perso_t *pers, int direction)

*\param salle la salle pour laquelle on test les collisions
*\param *pers le personnage pour lequel on test les collisions
*\param direction la direction dans laquelle se rend le personnage

*\brief permet de regarder si le personnage entre en collision avec un des murs de la salle

*\return 1 en cas de collision, 0 si aucune collision
*/
int test_collision(salle_t salle, perso_t *pers, int direction){

	int i = 0;
	SDL_Rect tmp = pers->sprites[courant].rectangle;

	if(direction == bas)
		tmp.y += 3;
	else if(direction == haut)
		tmp.y -= 3;
	else if(direction == droite)
		tmp.x += 3;
	else if(direction == gauche)
		tmp.x -= 3;

	for( ; i < salle.nb_murs; i++){

		if(SDL_HasIntersection(&salle.murs[i], &tmp)){
			return 1;
		}
	}
	return 0;
}


//Ecrit par Aurélien Tudoret
/**
*\fn void init_animations(animation_t *anim)

*\param *anim la structure qui gère les animations

*\brief Initialise la structure d'animations
*/
void init_animations(animation_t *anim){

	anim->actuel = courant;
	anim->last_use = SDL_GetTicks() - DELAIS_ANIMATIONS;
}


//Ecrit par Aurélien Tudoret
/**
*\fn void change_animation(animation_t *anim, image_t sprites[], int nouvelle_animation)
*\param *anim la structure qui gère les animations
*\param sprites[] le tableau de sprites du personnage
*\param nouvelle_animation l'indice du tableau ou se trouve la nouvelle animation a utiliser

*\brief permet de changer d'animation selon la nouvelle passée en paramètre
*/
void change_animation(animation_t *anim, image_t sprites[], int nouvelle_animation){

	sprites[courant] = sprites[nouvelle_animation];
	anim->actuel = nouvelle_animation;
	anim->last_use = SDL_GetTicks();
}


//Ecrit par Aurélien Tudoret. Ajouts par Axel Jourry
/**
*\fn void animations_personnage(image_t sprites[], unsigned int timer, touches_t clavier, animation_t *anim, Mix_Chunk *sounds[NB_SON])

*\param sprites[] le tableau de sprites du personnage
*\param timer le temps d'execution du jeu
*\param clavier la structure de touches du clavier
*\param *anim la structure qui gère les animations
*\param *sounds[NB_SON] le tableau contenant les sons

*\brief permet de changer d'animation selon le déplacement du personnage
*/
void animations_personnage(image_t sprites[], unsigned int timer, touches_t clavier, animation_t *anim, Mix_Chunk *sounds[NB_SON]){

	int i;

	for(i = 0; i <= left && clavier.tab[i] != 1; i++);//recherche d'une touche pressée

	if(i <= left){

		if(anim->last_use + DELAIS_ANIMATIONS <= timer){

			//animation du personnage vers la droite
			if(i == right && sprites[courant].img == sprites[droite3].img){
				change_animation(anim, sprites, droite2);

			}
			else if (i == right && sprites[courant].img == sprites[droite2].img){
				change_animation(anim, sprites, droite1);
				Mix_PlayChannel(0, sounds[footsteps], 0);

			}
			else if (i == right || (i == right && sprites[courant].img == sprites[droite1].img)){
				change_animation(anim, sprites, droite3);

			}

			//animation du personnage vers la gauche
			if(i == left && sprites[courant].img == sprites[gauche1].img){
				change_animation(anim, sprites, gauche2);
			}
			else if (i== left && sprites[courant].img == sprites[gauche2].img){
				change_animation(anim, sprites, gauche3);
			}
			else if (i == left || (i == left && sprites[courant].img == sprites[gauche3].img)){
				change_animation(anim, sprites, gauche1);
				Mix_PlayChannel(0, sounds[footsteps], 0);

			}

			//animation du personnage vers le haut
			if(i == up){
				//on garde le personnage orienté dans sa direction d'origine
				if(anim->actuel >= idle_droite && anim->actuel <= droite3){
					if(sprites[courant].img == sprites[droite3].img){
						change_animation(anim, sprites, droite2);
					}
					else if(sprites[courant].img == sprites[droite2].img){
						change_animation(anim, sprites, droite1);
						Mix_PlayChannel(0, sounds[footsteps], 0);

					}
					else{
						change_animation(anim, sprites, droite3);
					}
				}
				else{
					if(sprites[courant].img == sprites[gauche1].img){
						change_animation(anim, sprites, gauche2);
					}
					else if(sprites[courant].img == sprites[gauche2].img){
						change_animation(anim, sprites, gauche3);
					}
					else{
						change_animation(anim, sprites, gauche1);
						Mix_PlayChannel(0, sounds[footsteps], 0);

					}
				}
			}
			else //animation du personnage vers le bas
			if(i == down){
				//on garde le personnage orienté dans sa direction d'origine
				if(anim->actuel >= idle_droite && anim->actuel <= droite3){
					if(sprites[courant].img == sprites[droite3].img){
						change_animation(anim, sprites, droite2);
					}
					else if(sprites[courant].img == sprites[droite2].img){
						change_animation(anim, sprites, droite1);
						Mix_PlayChannel(0, sounds[footsteps], 0);

					}
					else{
						change_animation(anim, sprites, droite3);
					}
				}
				else{
					if(sprites[courant].img == sprites[gauche1].img){
						change_animation(anim, sprites, gauche2);
					}
					else if(sprites[courant].img == sprites[gauche2].img){
						change_animation(anim, sprites, gauche3);
					}
					else{
						change_animation(anim, sprites, gauche1);
						Mix_PlayChannel(0, sounds[footsteps], 0);

					}
				}
			}
		}
	}
	else{

		//aucune touche enfoncée, on revient a un état idle
		if(sprites[courant].img == sprites[gauche3].img || sprites[courant].img == sprites[gauche2].img || sprites[courant].img == sprites[gauche1].img){
			change_animation(anim, sprites, idle_gauche);
		}
		else{
			change_animation(anim, sprites, idle_droite);
		}

		anim->last_use -= DELAIS_ANIMATIONS;
	}
}


//Ecrit par Aurélien Tudoret. Ajouts par Axel
/**
*\fn void deplacement_personnage(perso_t *pers, salle_t salle, int *continuer, animation_t *anim, Mix_Chunk *sounds[NB_SON], touches_t *clavier, int *etat)

*\param *pers la structure du pêrsonnage que l'on souhaite déplacer
*\param salle la salle dans laquelle le personnage se déplace
*\param *continuer le pointeur sur variable permettant de savoir si le joueur souhaite quitter le programme
*\param *anim la structure qui gère les animations
*\param *sounds[NB_SON] le tableau contenant les sons
*\param clavier la structure de touches du clavier
*\param *etat défini l'état dans lequel le jeu se trouve ->menu, labyrinthe, chargement

*\brief Gère les déplacement du personnage dans une salle
*/
void deplacement_personnage(perso_t *pers, salle_t salle, int *continuer, animation_t *anim, Mix_Chunk *sounds[NB_SON], touches_t *clavier, int *etat){

	SDL_Event event;

	unsigned int temps = SDL_GetTicks();

	while(SDL_PollEvent(&event)){ //On attend un évènement au clavier

		event_clavier(clavier, event);

		if(event.type == SDL_QUIT)//croix de la fenetre
			*continuer = FALSE;

		animations_personnage(pers->sprites, temps, *clavier, anim, sounds);
	//permet au personnage de revenir à l'état idle quand aucune touche n'est enfoncée
	}

	if(clavier->tab[down] == 1){ //touche du bas

		if(!test_collision(salle,pers, bas)){
			pers->y += VITESSE_PERSO;
			animations_personnage(pers->sprites, temps, *clavier, anim, sounds);
		}
		else
			pers->y -= 3;
	}
	else if(clavier->tab[right] == 1){ //touche droite

		if(!test_collision(salle,pers, droite)){
			pers->x += VITESSE_PERSO;
			animations_personnage(pers->sprites, temps, *clavier, anim, sounds);
		}
		else
			pers->x -= 3;
	}
	else if(clavier->tab[left] == 1){ //touche gauche

		if(!test_collision(salle,pers, gauche)){
			pers->x -= VITESSE_PERSO;
			animations_personnage(pers->sprites, temps, *clavier, anim, sounds);
		}
		else
			pers->x += 3;
	}
	else if(clavier->tab[up] == 1){ //touche haut

		if(!test_collision(salle,pers, haut)){
			pers->y -= VITESSE_PERSO;
			animations_personnage(pers->sprites, temps, *clavier, anim, sounds);
		}
		else
			pers->y += 3;
	}
	else if(clavier->tab[escape] == 1){ //Touche echap
		SDL_Delay(100);
		*etat = mainMenu;
		init_tab_clavier(clavier->tab);
	}

	pers->sprites[courant].rectangle.x = pers->x;
	pers->sprites[courant].rectangle.y = pers->y;
}


//Ecrit par Aurélien Tudoret. Ajouts par Axel

/**
*\fn int changement_de_salle(perso_t *pers, salle_t salle, int indice, Mix_Chunk *sounds[NB_SON])
*\param *pers la structure du personnage
*\param salle la salle dans laquelle on se trouve
*\param indice l'indice de la salle dans laquelle le joueur se situe
*\param *sounds[NB_SON] le tableau contenant les sons

*\brief permet de téléporter le personnage dans la salle dont il passe la porter

*\return la salle dans laquelle le joueur arrive
*/
int changement_de_salle(perso_t *pers, salle_t salle, int indice, Mix_Chunk *sounds[NB_SON]){

	for(int i = 0; i < salle.nb_portes; i++){

		if(SDL_HasIntersection(&salle.portes[i], &pers->sprites[0].rectangle)){

			if(salle.portes[i].y == EMPLACEMENT_DEPART_DESSIN_SALLE_Y){
			//porte en haut
				pers->x = WIN_WIDTH / 2 - TAILLE_IMAGE;
				pers->y = salle.murs[salle.nb_murs -1].y - TAILLE_IMAGE- 50;
				Mix_PlayChannel(1, sounds[change_salle], 0);

				return salle.s_h;
			}
			else if(salle.portes[i].y == 488){
			//porte en bas
				pers->x = WIN_WIDTH / 2 - TAILLE_IMAGE;

				pers->y = salle.murs[0].y + TAILLE_IMAGE + 50;
				Mix_PlayChannel(1, sounds[change_salle], 0);

				return salle.s_b;
			}
			else if(salle.portes[i].x == EMPLACEMENT_DEPART_DESSIN_SALLE_X){
			//porte à gauche
				pers->x = WIN_WIDTH / 2 + 50;
				pers->y = WIN_HEIGHT / 2 - TAILLE_IMAGE / 2;
				Mix_PlayChannel(1, sounds[change_salle], 0);

				return salle.s_g;
			}
			else{
			//porte à droite
				pers->x = salle.murs[0].x + TAILLE_IMAGE + 50;
				pers->y = WIN_HEIGHT / 2 - TAILLE_IMAGE / 2;
				Mix_PlayChannel(1, sounds[change_salle], 0);

				return salle.s_d;
			}
		}
	}

	pers->sprites[courant].rectangle.x = pers->x;
	pers->sprites[courant].rectangle.y = pers->y;

	return indice;
}


//Ecrit par Aurélien Tudoret
/**
*\fn void initialise_personnage(perso_t *pers)

*\param *pers la structure du personnage

*\brief initialise les valeurs de base pour le personnage
*/
void initialise_personnage(perso_t *pers){

	pers->pv = PV_DEPART_PERSONNAGE;
	pers->pv_max = PV_DEPART_PERSONNAGE;
	pers->pv_old = PV_DEPART_PERSONNAGE;

	pers->x = WIN_WIDTH / 2;
	pers->y = WIN_HEIGHT / 2;

	pers->fuite = 0;

	pers->etage = 1;
	pers->etage_old = 1;

	pers->cmpMort = 0;
}


//Ecrit par Aurélien Tudoret
/**
*\fn int collision_perso_ennemi(perso_t pers, ennemi_t ennemi)

*\param pers la structure du personnage
*\param ennemi l'ennemi présent dans la salle

*\return TRUE si une collision a lieu, FALSE sinon

*\brief Vérifie la collision ou non entre un ennemi spécifique et le joueur
*/
int collision_perso_ennemi(perso_t pers, ennemi_t ennemi){

	return SDL_HasIntersection(&pers.sprites[courant].rectangle, &ennemi.sprites.rectangle);
}


//Ecrit par Aurélien Tudoret
/**
*\fn int combat_declenche(salle_t salle, perso_t pers)

*\param salle la salle du labyrinthe dans laquelle on se situe
*\param pers la structure du personnage

*\return TRUE si une collision est detéctée avec un ennemi, FALSE sinon

*\brief Regarde si le personnage entre en combat avec un ennemi dans la salle
*/
int combat_declenche(salle_t salle, perso_t pers){

	if(salle.ennemi_present || salle.boss){
		if(collision_perso_ennemi(pers, *salle.ennemi))
			return TRUE;

		if(salle.nb_ennemi == 2)
			if(collision_perso_ennemi(pers, *salle.ennemi2))
				return TRUE + 1;

		return FALSE;
	}

	return FALSE;
}


//Ecrit par Aurélien Tudoret. Ajouts par Thomas Malabry
/**
*\fn void creer_texture_depuis_char(image_t *texte_pv, image_t *texte_etage, perso_t perso, SDL_Renderer *rendu, image_t *texte_counter, int *compte_ennemi, int *ennemi_max)

*\param *texte_pv une structure qui contiendra l'image du texte a afficher
*\param *texte_etage une structure qui contiendra l'image du texte a afficher
*\param pers le personnage à partir duquel on va récupérer des informations
*\param *rendu le renderer sur lequel on dessine
*\param *texte_counter une structure qui contiendra l'image du texte a afficher
*\param *compte_ennemi un compteur des ennemis morts
*\param *ennemi_max le nombre d'ennemi max.

*\brief Crée des images à partir de texte issu des données du personnage, range ces images dans les structures correspondantes
*/
void creer_texture_depuis_char(image_t *texte_pv, image_t *texte_etage, perso_t perso, SDL_Renderer *rendu, image_t *texte_counter, int *compte_ennemi, int *ennemi_max){

	char pv[15], etage[15],counter[15];

	TTF_Font *police = NULL;

	int x_pv = WIN_WIDTH *0.08, x_etage = WIN_WIDTH *0.08, y_pv = WIN_HEIGHT * 0.10, y_etage = WIN_HEIGHT * 0.02;
  int x_counter=WIN_WIDTH *0.08,y_counter=WIN_HEIGHT * 0.19;
	int max=*(ennemi_max)*0.7;

	police = TTF_OpenFont(FONT_PATH, 30);

	sprintf(pv, "%d / %d", perso.pv, perso.pv_max);
	sprintf(etage, "Etage %d", perso.etage);
	sprintf(counter,"%d / %d",*(compte_ennemi),max);

	get_text_and_rect(rendu, x_etage, y_etage, etage, police, &texte_etage->img, &texte_etage->rectangle);
	get_text_and_rect(rendu, x_pv, y_pv, pv, police, &texte_pv->img, &texte_pv->rectangle);
	get_text_and_rect(rendu, x_counter, y_counter, counter, police, &texte_counter->img, &texte_counter->rectangle);

	TTF_CloseFont(police); //on libère la police
}
