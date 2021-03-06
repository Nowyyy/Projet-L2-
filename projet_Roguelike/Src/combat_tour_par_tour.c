/**

*\file combat_tour_par_tour.c

*\author Tudoret Aurélien, Jourry Axel, Marin Timothée, Malabry Thomas

*\date 13/05/2020

*\version 1.0

*\brief contient et fait appel a toutes fonctions nécessaires pour le combat
*/

#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/fonctions.h"
#include "../include/clavier.h"
#include "../include/animation.h"


//Ecrit par Thomas Malabry et Aurélien Tudoret. Ajouts par Axel Jourry.
/**
*\fn int deplacement_rectangle_selection_combat(SDL_Rect defausse, SDL_Rect fuir, image_t images[NB_TEXTURES_LABY], SDL_Rect **rect_sel, Mix_Chunk *sounds[NB_SON], Mix_Music *musics[NB_MUSIC])

*\param defausse Correspond aux coordonnées du texte défausse
*\param fuir Correspond aux coordonnées du texte fuir
*\param images[NB_TEXTURES_LABY] Un tableau contenant les cartes
*\param **rect_sel Les coordonnées et taille du rectangle de selection
*\param *sounds[NB_SON] Contient les sons du jeu
*\param *music[NB_MUSIC] Contient les musiques du jeu

*\brief Permet de déplacer le rectangle de selection

*/
int deplacement_rectangle_selection_combat(SDL_Rect defausse, SDL_Rect fuir, image_t images[NB_TEXTURES_LABY], SDL_Rect **rect_sel, Mix_Chunk *sounds[NB_SON], Mix_Music *musics[NB_MUSIC]){

	SDL_Event event;
 	int choix= NB_CARTES_COMBAT +1;

	while(SDL_PollEvent(&event) && choix== NB_CARTES_COMBAT +1){ //On attend un évènement au clavier

		if(event.type == SDL_KEYDOWN){	//touche enfoncée

			if(event.key.keysym.sym == SDLK_RIGHT){
				if((*rect_sel)->x < defausse.x){//on n'est pas sur la dernière option, on peut descendre

					if((*rect_sel)->x == images[carte4].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->y = defausse.y - RECT_SELECT_Y_DIFF;
						(*rect_sel)->x = defausse.x - RECT_SELECT_X_DIFF;
						(*rect_sel)->w = defausse.w + RECT_SELECT_X_DIFF * 2;
						(*rect_sel)->h = defausse.h + RECT_SELECT_Y_DIFF * 2;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == images[carte3].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte4].rectangle.x - RECT_SELECT_X_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == images[carte2].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte3].rectangle.x - RECT_SELECT_X_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == images[carte1].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte2].rectangle.x - RECT_SELECT_X_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_LEFT){

				if((*rect_sel)->x > images[carte1].rectangle.x){//on n'est pas sur la premiere option, on peut aller a gauche

					if((*rect_sel)->y == defausse.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->x = images[carte4].rectangle.x - RECT_SELECT_X_DIFF;
						(*rect_sel)->y = images[carte4].rectangle.y - RECT_SELECT_Y_DIFF;
						(*rect_sel)->h = images[carte4].rectangle.h + RECT_SELECT_Y_DIFF * 2;
						(*rect_sel)->w = images[carte4].rectangle.w + RECT_SELECT_X_DIFF * 2;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == fuir.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte4].rectangle.x - RECT_SELECT_X_DIFF;
						(*rect_sel)->y = images[carte4].rectangle.y - RECT_SELECT_Y_DIFF;
						(*rect_sel)->h = images[carte4].rectangle.h + RECT_SELECT_Y_DIFF * 2;
						(*rect_sel)->w = images[carte4].rectangle.w + RECT_SELECT_X_DIFF * 2;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == images[carte4].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte3].rectangle.x - RECT_SELECT_X_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == images[carte3].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte2].rectangle.x - RECT_SELECT_X_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == images[carte2].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte1].rectangle.x - RECT_SELECT_X_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_UP){//touche haut
				if((*rect_sel)->y == fuir.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = defausse.y - RECT_SELECT_Y_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
				}
			}
			else if(event.key.keysym.sym == SDLK_DOWN){//touche bas
				if((*rect_sel)->y == defausse.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = fuir.y - RECT_SELECT_Y_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
				}
			}
			else if(event.key.keysym.sym == SDLK_RETURN){//touche entrée
				if((*rect_sel)->y == defausse.y - RECT_SELECT_Y_DIFF){
					Mix_PlayChannel(0, sounds[selection], 0);
					return -2;
				}
				else if((*rect_sel)->y == fuir.y - RECT_SELECT_Y_DIFF){
					Mix_PlayChannel(0, sounds[selection], 0);
					return -1;
				}
				else if((*rect_sel)->x == images[carte1].rectangle.x - RECT_SELECT_X_DIFF){
					Mix_PlayChannel(0, sounds[selection], 0);
					return 0;
				}
				else if((*rect_sel)->x == images[carte2].rectangle.x - RECT_SELECT_X_DIFF){
					Mix_PlayChannel(0, sounds[selection], 0);
					return 1;
				}
				else if((*rect_sel)->x == images[carte3].rectangle.x - RECT_SELECT_X_DIFF){
					Mix_PlayChannel(0, sounds[selection], 0);
					return 2;
				}
				else if((*rect_sel)->x == images[carte4].rectangle.x - RECT_SELECT_X_DIFF){
					Mix_PlayChannel(0, sounds[selection], 0);
					return 3;
				}
			}
		}
	}
	return NB_CARTES;
}


//Ecrit par Thomas Malabry et Aurélien Tudoret
/**
*\fn void affichage_combat_personnage(SDL_Renderer *rendu, perso_t *pers, ennemi_t *ennemi, image_t def, image_t fuir, SDL_Rect *rect_sel, image_t images[NB_TEXTURES_COMBAT], hud_combat_t ennemi_hud, hud_combat_t pers_hud, hud_combat_t action)

*\param *rendu le renderer sur lequel on dessine
*\param *pers la structure contenant le personnage
*\param *ennemi la structure contenant tous les ennemis
*\param def Les textures du texte defausse
*\param fuir Les textures du texte fuir
*\param *rect_sel Les coordonnées et taille du rectangle de selection
*\param images[NB_TEXTURES] le tableau contenant les cartes
*\param ennemi_hud la barre de vie de l'ennemi
*\param pers_hud la barre de vie du joueur
*\param action l'action jouée par le joueur ou l'ennemi

*\brief Permet d'afficher toutes la partie combat
*/
void affichage_combat_personnage(SDL_Renderer *rendu, perso_t *pers, ennemi_t *ennemi, image_t def, image_t fuir, SDL_Rect *rect_sel, image_t images[NB_TEXTURES_COMBAT],
hud_combat_t ennemi_hud, hud_combat_t pers_hud, hud_combat_t action){

	int w5 = images[gui_bar].rectangle.w, h5 = images[gui_bar].rectangle.h;

	images[gui_bar].rectangle = action.texte.rectangle;

	images[gui_bar].rectangle.x -= 40;
	images[gui_bar].rectangle.y -= 10;
	images[gui_bar].rectangle.w += 80;
	images[gui_bar].rectangle.h += 20;

	SDL_Rect carte_selec;

  //écran noir puis nettoie l'écran
  SDL_SetRenderDrawColor(rendu,0,0,0,255);
  SDL_RenderClear(rendu);
  /*Mise en place des fonds*/
  SDL_RenderCopy(rendu, images[fond2].img, NULL, &images[fond2].rectangle);

  SDL_RenderCopy(rendu, images[fond].img, NULL, &images[fond].rectangle);

  images[coeur].rectangle.x = WIN_WIDTH * 0.10;
  images[coeur].rectangle.y = WIN_HEIGHT * 0.02;

  SDL_RenderCopy(rendu, pers_hud.pv.img, NULL, &pers_hud.pv.rectangle);
  SDL_RenderCopy(rendu, pers_hud.nom.img, NULL, &pers_hud.nom.rectangle);
  SDL_RenderCopy(rendu, images[coeur].img, NULL, &images[coeur].rectangle);

  images[coeur].rectangle.x = WIN_WIDTH * 0.81;
  images[coeur].rectangle.y = WIN_HEIGHT * 0.02;

  SDL_RenderCopy(rendu, ennemi_hud.pv.img, NULL, &ennemi_hud.pv.rectangle);
  SDL_RenderCopy(rendu, ennemi_hud.nom.img, NULL, &ennemi_hud.nom.rectangle);
  SDL_RenderCopy(rendu, images[coeur].img, NULL, &images[coeur].rectangle);

  if(action.existe){
  	SDL_RenderCopy(rendu, images[gui_bar].img, NULL, &images[gui_bar].rectangle);
 	SDL_RenderCopy(rendu, action.texte.img, NULL, &action.texte.rectangle);
  }

  if(action.defausse){
  	//on est dans l'écran de défausse, on affiche les cartes sélectionnées par le joueur s'il y en a

  	SDL_SetRenderDrawColor(rendu,240,220,130,255);//jaune

  	if(action.cartes[0]){
  		carte_selec = images[carte1].rectangle;
  		SDL_RenderDrawRect(rendu, &carte_selec);
  	}

  	if(action.cartes[1]){
  		carte_selec = images[carte2].rectangle;
  		SDL_RenderDrawRect(rendu, &carte_selec);
  	}

  	if(action.cartes[2]){
  		carte_selec = images[carte3].rectangle;
  		SDL_RenderDrawRect(rendu, &carte_selec);
  	}

  	if(action.cartes[3]){
  		carte_selec = images[carte4].rectangle;
  		SDL_RenderDrawRect(rendu, &carte_selec);
  	}

  	SDL_SetRenderDrawColor(rendu,0,0,0,255);
  }

  /*Mise en place des cartes */
  SDL_RenderCopy(rendu, images[carte1].img, NULL, &images[carte1].rectangle);

  SDL_RenderCopy(rendu, images[carte2].img, NULL, &images[carte2].rectangle);

  SDL_RenderCopy(rendu, images[carte3].img, NULL, &images[carte3].rectangle);

  SDL_RenderCopy(rendu, images[carte4].img, NULL, &images[carte4].rectangle);
  /*afficher le rectangle*/
  SDL_SetRenderDrawColor(rendu, 255,255,255,255);
  SDL_RenderDrawRect(rendu, rect_sel);
  /*Texte Défausse et fuir*/
  SDL_RenderCopy(rendu, def.img, NULL, &def.rectangle);
  SDL_RenderCopy(rendu, fuir.img, NULL, &fuir.rectangle);

  /*Mise en place du personnage*/
	int hauteur=405;
  int w=pers->sprites[idle_droite].rectangle.w;
  int h=pers->sprites[idle_droite].rectangle.h;
  int x=pers->sprites[idle_droite].rectangle.x;
  int y=pers->sprites[idle_droite].rectangle.y;
  pers->sprites[idle_droite].rectangle.w *= 1.2;
  pers->sprites[idle_droite].rectangle.h *= 1.2;
  pers->sprites[idle_droite].rectangle.x = 215;
  pers->sprites[idle_droite].rectangle.y = hauteur-(pers->sprites[idle_droite].rectangle.h);
  pers->sprites[courant] = pers->sprites[idle_droite];
  SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);

  /*Afficher l'ennemi*/
  int xe=ennemi->sprites.rectangle.x;
  int ye=ennemi->sprites.rectangle.y;
  int he=ennemi->sprites.rectangle.h;
  int we=ennemi->sprites.rectangle.w;
  ennemi->sprite_courant.x = 0;
  ennemi->sprite_courant.y = ennemi->sprite_courant.h;
  ennemi->sprites.rectangle.x = 830;
  ennemi->sprites.rectangle.w *= 1.2;
  ennemi->sprites.rectangle.h *= 1.2;
	ennemi->sprites.rectangle.y = hauteur-(ennemi->sprites.rectangle.h);
  ennemi->sprites = ennemi->sprites;
  SDL_RenderCopy(rendu, ennemi->sprites.img, &ennemi->sprite_courant, &ennemi->sprites.rectangle);

  SDL_RenderPresent(rendu);
	/*Reinitialise les coordonnées du perso et des ennemis*/
  pers->sprites[idle_droite].rectangle.w = w;
  pers->sprites[idle_droite].rectangle.h = h;
  pers->sprites[idle_droite].rectangle.x = pers->x;
  pers->sprites[idle_droite].rectangle.y = pers->y;
  ennemi->sprites.rectangle.w = we;
  ennemi->sprites.rectangle.h = he;
  ennemi->sprites.rectangle.x = xe;
  ennemi->sprites.rectangle.y = ye;

  images[gui_bar].rectangle.w = w5;
  images[gui_bar].rectangle.h = h5;
}


//Ecrit par Aurélien Tudoret
/**
*\fn void charge_textures_combat(image_t images[], SDL_Renderer *rendu, carte_t *cartes[])

*\param images[] le tableau contenant les images
*\param *rendu le renderer sur lequel on dessine
*\param *cartes[] le tableau de pointeur sur des cartes, contient les cartes utilisées pendant le combat

*\brief Charge dans le tableau images les visuels pour les fonds et les cartes afin de pouvoir les afficher
*/
void charge_textures_combat(image_t images[], SDL_Renderer *rendu, carte_t *cartes[]){

	charge_image(FOND_COMBAT_PATH,&images[fond2], rendu);
	charge_image(COMBAT_PATH,&images[fond], rendu);
	charge_image(GUI_COMBAT_PATH,&images[gui_bar], rendu);
	charge_image(cartes[0]->path,&images[carte1], rendu);
	charge_image(cartes[1]->path,&images[carte2], rendu);
	charge_image(cartes[2]->path,&images[carte3], rendu);
	charge_image(cartes[3]->path,&images[carte4], rendu);
	charge_image(HEART_PATH,&images[coeur], rendu);
	charge_image(GAMEOVER_PATH, &images[gameover], rendu);
	charge_image(DEATHLIGHT_PATH, &images[deathlight], rendu);
}


//Ecrit par Aurélien Tudoret
/**
*\fn void donne_valeur_rect_images(image_t images[], perso_t *perso)

*\param images[] le tableau contenant les images
*\param *perso Contient la structure du personnage

*\brief Donne les coordonnées et ajuste les tailles des images des cartes et des fonds pour l'écran de combat
*/
void donne_valeur_rect_images(image_t images[], perso_t *perso){

	images[fond2].rectangle.x= 0;
	images[fond2].rectangle.y= 70;
	images[fond2].rectangle.w *= 1;
	images[fond2].rectangle.h *= 1;

 	images[fond].rectangle.x=0;
	images[fond].rectangle.y= 450;
  	images[fond].rectangle.w *= 1;
  	images[fond].rectangle.w *= 1;
  	images[fond].rectangle.w *= 4;

  	images[carte1].rectangle.x=50;
  	images[carte1].rectangle.y= 450;

	images[carte2].rectangle.x=250;
  	images[carte2].rectangle.y= 450;

 	images[carte3].rectangle.x=450;
  	images[carte3].rectangle.y= 450;

  	images[carte4].rectangle.x=650;
  	images[carte4].rectangle.y= 450;

	images[gameover].rectangle.x = 135;
	images[gameover].rectangle.y = -100;

	images[deathlight].rectangle.x = WIN_WIDTH/2-100;
	images[deathlight].rectangle.y = WIN_HEIGHT/2-65;
}


//Ecrit par Aurélien Tudoret
/**
*\fn void free_image(image_t images[])

*\param images[] le tableau contenant les images

*\brief Supprime les images des cartes et des fonds utilisées pour le combat
*/
void free_image(image_t images[]){

	for(int i = 0; i< NB_TEXTURES_COMBAT; i++)
		libere_texture(&images[i].img);
}


//Ecrit par Aurélien Tudoret et Thomas Malabry. Ajouts par Axel Jourry
/**
*\fn void tour_joueur(perso_t *pers, ennemi_t *ennemi, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON])

*\param *pers la structure du personnage
*\param *ennemi l'ennemi que le joueur affronte
*\param *carte la carte que le joueur joue
*\param *rendu le renderer sur lequel on dessine
*\param *sounds[NB_SON] Contient les sons du jeu

*\brief permet d'effectuer l'action sélectionnée par le joueur
*/
void tour_joueur(perso_t *pers, ennemi_t *ennemi, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON]){

	anim_combat_perso(pers, carte, rendu, sounds, ennemi);

	if(carte->type == ATTAQUE){
		if(carte->consommable > 0){
			carte->consommable -= 1;
		}
		ennemi->pv -= carte->valeur;
		if(ennemi->pv < 0){
			ennemi->pv = 0;
		}
	}
	else{

		if(carte->consommable > 0){
			carte->consommable -= 1;
		}

		if(pers->pv + carte->valeur <= pers->pv_max)
			pers->pv += carte->valeur;
		else
			pers->pv = pers->pv_max;
	}
}


//Ecrit par Aurélien Tudoret et Thomas Malabry. Ajouts par Axel Jourry
/**
*\fn void tour_ennemi(perso_t *pers, ennemi_t *ennemi, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON])

*\param *pers la structure du personnage
*\param *ennemi l'ennemi que le joueur affronte
*\param *rendu le renderer sur lequel on dessine
*\param *sounds[NB_SON] le tableau des sons


*\brief permet de faire jouer l'ennemi, actions effectuées selon la situation
*/
void tour_ennemi(perso_t *pers, ennemi_t *ennemi, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON]){

	if(ennemi->pv < ennemi->pv_max * 0.10 && ennemi->heal_use == 0){
		//l'ennemi se soigne une seule fois par combat si il a moins d'un certain pourcentage de pdv restant
		ennemi->heal_use = 1;
		ennemi->pv = ennemi->pv_max * 0.50;
	}
	else{
		anim_combat_ennemi_attaque(ennemi, rendu, sounds, pers);
		pers->pv -= ennemi->attaque;

		if(pers->pv < 0)
			pers->pv = 0;
	}
}


//Ecrit par Aurélien Tudoret
/**
*\fn void creer_texte_combat(char *txt, image_t *image, int x, int y, SDL_Renderer *rendu, TTF_Font *font)

*\param *txt le texte que l'on souhaite afficher à l'écran,
*\param *image la structure qui contiendra le texte
*\param x la position en x où sera placée l'image
*\param y la position en y où sera placée l'image
*\param *rendu le renderer sur lequel on dessine
*\param *font la police utilisée pour écrire le texte

*\brief Permet de donner à une structure image, un texte et les positions où l'afficher à l'écran
*/
void creer_texte_combat(char *txt, image_t *image, int x, int y, SDL_Renderer *rendu, TTF_Font *font){

	image->rectangle.x = x;
	image->rectangle.y = y;

	get_text_and_rect(rendu,image->rectangle.x, image->rectangle.y, txt, font, &image->img, &image->rectangle);
}


//Ecrit par Aurélien Tudoret
/**
*\fn void create_hud(hud_combat_t *hud_pers, hud_combat_t *hud_ennemi, ennemi_t ennemi, perso_t pers, SDL_Renderer *rendu, TTF_Font *font)

*\param *hud_pers le HUD du personnage
*\param *hud_ennemi le HUD de l'ennemi
*\param *ennemi l'ennemi que le joueur affronte
*\param *pers la structure du personnage
*\param *rendu le renderer sur lequel on dessine
*\param *font la police utilisée pour écrire le texte

*\brief Créer un HUD pour le perso et l'ennemi s'il n'existe pas, sinon détruit les textures précédentes pour mettre à jour
*/
void create_hud(hud_combat_t *hud_pers, hud_combat_t *hud_ennemi, ennemi_t ennemi, perso_t pers, SDL_Renderer *rendu, TTF_Font *font){

	char pv_pers[20], pv_ennemi[20], nom_pers[] = "Joueur";

	sprintf(pv_pers, "PV  %d / %d", pers.pv, pers.pv_max);
	sprintf(pv_ennemi, "PV  %d / %d", ennemi.pv, ennemi.pv_max);

	if(hud_ennemi->existe == 0 || hud_pers->existe == 0){

		hud_ennemi->existe = 1;

		hud_pers->existe = 1;
	}
	else{
		libere_texture(&hud_pers->pv.img);
		libere_texture(&hud_pers->nom.img);
		libere_texture(&hud_ennemi->nom.img);
		libere_texture(&hud_ennemi->pv.img);
	}

	creer_texte_combat(nom_pers, &hud_pers->nom, WIN_WIDTH * 0.02, WIN_HEIGHT *0.02, rendu, font);
	creer_texte_combat(pv_pers, &hud_pers->pv, hud_pers->nom.rectangle.x + hud_pers->nom.rectangle.w + 50, WIN_HEIGHT *0.02, rendu, font);

	creer_texte_combat(ennemi.nom, &hud_ennemi->nom, WIN_WIDTH * 0.65, WIN_HEIGHT *0.02, rendu, font);
	creer_texte_combat(pv_ennemi, &hud_ennemi->pv, WIN_WIDTH * 0.85, WIN_HEIGHT *0.02, rendu, font);
}


//Ecrit par Aurélien Tudoret
/**
*\fn void init_hud_action(hud_combat_t *action)

*\param *action le hud qui affichera l'action effectuée par le joueur ou l'ennemi

*\brief initialise certaines valeurs du hud action
*/
void init_hud_action(hud_combat_t *action){

	action->existe = 0;
	action->defausse = 0;
	action->cartes[0] = 0;
	action->cartes[1] = 0;
	action->cartes[2] = 0;
	action->cartes[3] = 0;
}


//Ecrit par Aurélien Tudoret
/**
*\fn void actualisation_apres_tour(perso_t *pers, ennemi_t *ennemi, carte_t carte, hud_combat_t *action, hud_combat_t *hud_pers, hud_combat_t *hud_ennemi, SDL_Renderer *rendu, TTF_Font *font, int tour)

*\param *pers la structure du personnage
*\param *ennemi la structure de l'ennemi
*\param carte la carte utilisée par le joueur lors de ce tour
*\param *action le hud qui affichera l'action effectuée par le joueur ou l'ennemi
*\param *hud_pers le hud du personnage
*\param *hud_ennemi le hud de l'ennemi
*\param *rendu le renderer sur lequel on dessine
*\param *font la police utilisée pour écrire le texte
*\param tour indique si c'est le joueur ou l'ennemi qui joue

*\brief Actualise les huds des perso et ennemi, prépare le texte a affichant indiquant l'action effectuée
*/
void actualisation_apres_tour(perso_t *pers, ennemi_t *ennemi, carte_t carte, hud_combat_t *action, hud_combat_t *hud_pers, hud_combat_t *hud_ennemi, SDL_Renderer *rendu, TTF_Font *font, int tour){

	char joueur[80];
	int x, y;

	if(action->existe)
		libere_texture(&action->texte.img);

	if(tour){

		create_hud(hud_pers, hud_ennemi, *ennemi, *pers, rendu, font); //actualisation des pdv dans le hud

		if(carte.type == ATTAQUE)
			sprintf(joueur, "Vous utilisez %s, %s perd %d points de vie", carte.nom, ennemi->nom, carte.valeur);
		else
			sprintf(joueur, "Vous utilisez %s, Vous recuperez %d points de vie", carte.nom, carte.valeur);
	}
	else{

		create_hud(hud_pers, hud_ennemi, *ennemi, *pers, rendu, font); //actualisation des pdv dans le hud

		if(ennemi->pv != ennemi->pv_old)
			sprintf(joueur, "%s se soigne de %d points de vie", ennemi->nom, ennemi->pv - ennemi->pv_old);
		else
			sprintf(joueur, "%s attaque ! Vous perdez %d points de vie", ennemi->nom, ennemi->attaque);
	}

	action->existe = 1;

	creer_texte_combat(joueur, &action->texte, 0, 0, rendu, font);

	x = WIN_WIDTH / 2 - action->texte.rectangle.w /2;
	y = WIN_HEIGHT * 0.15;
	action->texte.rectangle.x = x + 20;
	action->texte.rectangle.y = y + 20;

	ennemi->pv_old = ennemi->pv;
}


//Ecrit par Aurélien Tudoret
/**
*\fn void detruire_action_temp(hud_combat_t *action)

*\param *action la zone de texte détaillant les coups échangés entre le joueur et l'ennemi

*\brief permet de détruire l'image présente dans le champs texte de action
*/
void detruire_action_temp(hud_combat_t *action){

	if(action->existe){
		action->existe = 0;
		libere_texture(&action->texte.img);
		action->defausse = 0;
		action->cartes[0] = 0;
		action->cartes[1] = 0;
		action->cartes[2] = 0;
		action->cartes[3] = 0;
	}
}


//Ecrit par Aurélien Tudoret
/**
*\fn void range_carte_deck(carte_t *cartes[])

\param *cartes[] le tableau de pointeurs sur cartes, contient les cartes utilisées pendant le combat

*\brief Range les cartes encore valide dans le deck, détruit les cartes barrées
*/
void range_carte_deck(carte_t *cartes[]){

	choix_liste(DECK);

	en_queue();

	for(int i = 0; i < NB_CARTES_COMBAT; i++){

		if(cartes[i]->type != NO_CARTE){

			ajout_droit(cartes[i]);
		}
		else{ // fake carte (carte barrée)
			detruire_carte(&cartes[i]);
		}
	}
}


//Ecrit par Aurélien Tudoret
/**
*\fn void consommable_epuise(carte_t *cartes[], int indice, image_t images[], SDL_Renderer *rendu)

*\param *cartes[] le tableau de pointeurs sur cartes, contient les cartes utilisées pendant le combat
*\param indice l'indice de la carte regardée par la fonction
*\param images[] le tableau contenant les images
*\param *rendu le renderer sur lequel on dessine

*\brief vérifie si la carte est de type consommable et si elle est épuisée
*/
void consommable_epuise(carte_t *cartes[], int indice, image_t images[], SDL_Renderer *rendu){

	int x = images[carte1 + indice].rectangle.x, y = images[carte1 + indice].rectangle.y;

	if(cartes[indice]->type != NO_CARTE){

		if(cartes[indice]->consommable == 0){

			detruire_carte(&cartes[indice]);

			tire_carte_deck(cartes, indice);

			charge_image(cartes[indice]->path,&images[carte1 + indice], rendu);

			images[carte1 + indice].rectangle.y = y;
			images[carte1 + indice].rectangle.x = x;
		}
	}
}


//Ecrit par Aurélien Tudoret
/**
*\fn void range_carte_tire_nouvelles(carte_t *cartes[NB_CARTES_COMBAT], int cartes_selectionnees[], image_t images[], SDL_Renderer *rendu)

*\param *cartes[NB_CARTES_COMBAT] la tableau des cartes du joueur
*\param cartes_selectionnees[] le tableau permettant de connaître les cartes que le joueur veut défausser
*\param images[] contient toutes les images nécessaires à l'affichage de l'écran de combat
*\param *rendu le renderer sur lequel on dessine

*\brief effectue la défausse, les cartes que le joueur ne veut pas sont renvoyées dans le deck, de nouvelles sont tirées à la place
*/
void range_carte_tire_nouvelles(carte_t *cartes[NB_CARTES_COMBAT], int cartes_selectionnees[], image_t images[], SDL_Renderer *rendu){


	choix_liste(DECK);

	en_queue();

	for(int i = 0; i < NB_CARTES_COMBAT; i++){

		if(cartes[i]->type != NO_CARTE && cartes_selectionnees[i]){

			ajout_carte_deck(cartes[i]);
			detruire_carte(&cartes[i]);

			tire_carte_deck(cartes, i);
			charge_image(cartes[i]->path,&images[carte1 + i], rendu);
		}
	}
}


//Ecrit par Aurélien Tudoret
/**
*\fn void defausse(SDL_Renderer *rendu, perso_t *perso, ennemi_t *ennemi, SDL_Rect *rectangle_selection, image_t images[], hud_combat_t hud_ennemi, hud_combat_t hud_pers, hud_combat_t action, TTF_Font *police, Mix_Chunk *sounds[NB_SON], Mix_Music *musics[NB_MUSIC], carte_t *cartes[NB_CARTES_COMBAT])

*\param *rendu le renderer sur lequel on dessine
*\param *perso la structure contenant le personnage
*\param *ennemi la structure de l'ennemi que le joueur affronte actuellement
*\param *rectangle_selection le rectangle de sélection que le joueur contrôle pour sélectionner des actions
*\param images[] contient toutes les images nécessaires à l'affichage de l'écran de combat
*\param hud_ennemi l'ATH de l'ennemi, comprenant l'affichage de son nom et de ses hp
*\param hud_pers l'ATH du joueur, comprenant l'affichage de son nom et de ses hp
*\param action l'ATH permettant d'afficher du texte indicatif au joueur -> fourre tout
*\param *police la police utilisée pour écrire du texte sur l'écran de jeu
*\param *sounds[] le tableau des sons brefs pour les interactions
*\param *musics[] le tableau des muisques d'ambience
*\param *cartes[] le tableau des cartes du joueur

*\brief permet d'effectuer toutes actions liées à la défausse de carte avec un affichage spécifique
*/
void defausse(SDL_Renderer *rendu, perso_t *perso, ennemi_t *ennemi, SDL_Rect *rectangle_selection, image_t images[], hud_combat_t hud_ennemi,
hud_combat_t hud_pers, hud_combat_t action, TTF_Font *police, Mix_Chunk *sounds[NB_SON], Mix_Music *musics[NB_MUSIC], carte_t *cartes[NB_CARTES_COMBAT]){


	image_t confirmer, annuler;

	detruire_action_temp(&action);

	int cartes_selectionnees[NB_CARTES_COMBAT] = {0, 0, 0, 0}, conf = 0, annul = 0, choix;

	get_text_and_rect(rendu, EMPLACEMENT_DEFAUSSE_X, EMPLACEMENT_DEFAUSSE_Y, "Confirmer", police, &confirmer.img, &confirmer.rectangle);
	get_text_and_rect(rendu, EMPLACEMENT_DEFAUSSE_X, EMPLACEMENT_FUITE_Y, "annuler", police, &annuler.img, &annuler.rectangle);

	action.existe = 1;
	action.defausse = 1;
	get_text_and_rect(rendu, EMPLACEMENT_DEFAUSSE_X, EMPLACEMENT_FUITE_Y, "Selectionner les cartes a defausser", police, &action.texte.img, &action.texte.rectangle);

	action.texte.rectangle.x = WIN_WIDTH / 2 - action.texte.rectangle.w /2 + 20;
	action.texte.rectangle.y = WIN_HEIGHT * 0.15 + 20;

	while(!conf && !annul){

		affichage_combat_personnage(rendu, perso, ennemi, confirmer, annuler, rectangle_selection, images, hud_ennemi, hud_pers, action);

  		choix = deplacement_rectangle_selection_combat(confirmer.rectangle, annuler.rectangle, images, &rectangle_selection, sounds, musics);

  		if(choix == -1){
  			annul = 1;
  		}
  		else if(choix == -2){
  			conf = 1;
  		}
  		else if (choix < NB_CARTES_COMBAT){

  			if(cartes_selectionnees[choix] == 0){
  				action.cartes[choix] = 1;
  				cartes_selectionnees[choix] = 1;
  			}
  			else{
  				action.cartes[choix] = 0;
  				cartes_selectionnees[choix] = 0;
  			}

  		}
	}

	if(conf && (cartes_selectionnees[0] == 1 || cartes_selectionnees[1] == 1 || cartes_selectionnees[3] == 1 || cartes_selectionnees[2] == 1)){
		//le joueur a confirmer vouloir changer des cartes et au moins une est sélectionnée
		range_carte_tire_nouvelles(cartes, cartes_selectionnees, images, rendu);
	}

	libere_texture(&annuler.img);
	libere_texture(&confirmer.img);
	detruire_action_temp(&action);
}


//Ecrit par Thomas Malabry Aurélien Tudoret. Ajouts par Axel Jourry
/**
*\fn void combat_t_p_t(perso_t * perso, ennemi_t * ennemi, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON], Mix_Music *musics[NB_MUSIC], int *etat)

*\param *perso la structure contenant le personnage
*\param *ennemi la structure de l'ennemi que le joueur affronte actuellement
*\param *rendu le renderer sur lequel on dessine
*\param *sounds[NB_SON] Contient les sons du jeu
*\param *music[NB_MUSIC] Contient les musiques du jeu
*\param *etat permet de changer l'affichage selon l'écran dans lequel se trouve le jeu

*\brief Fonction qui permet de gérer les choix de l'utilisateur via la SDL sur le combat
*/
void combat_t_p_t(perso_t * perso, ennemi_t * ennemi, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON], Mix_Music *musics[NB_MUSIC], int *etat)
{
////////////////Déclaration variables

	carte_t *cartes[NB_CARTES_COMBAT];

	image_t images[NB_TEXTURES_COMBAT];

	SDL_Event event;

	SDL_Rect *rectangle_selection = malloc(sizeof(SDL_Rect));

  	image_t def, fui;

  	hud_combat_t hud_pers, hud_ennemi, action;

  	int choix=0, i,fuite=1, alea = rand()%2, wait = 600, pv_ennemi = ennemi->pv;

  	TTF_Font * police = NULL;

  	police=TTF_OpenFont(FONT_PATH, 35);

//////////////Intialisation, chargement, allocation

  	hud_ennemi.existe = 0;
  	hud_pers.existe = 0;

  	ennemi->heal_use = 0;

  	for(int j = 0; j < NB_CARTES_COMBAT; j++)
		tire_carte_deck(cartes, j);

	charge_textures_combat(images, rendu, cartes);

	init_hud_action(&action);

	create_hud(&hud_pers, &hud_ennemi, *ennemi, *perso, rendu, police);

	donne_valeur_rect_images(images, perso);

	creer_texte_combat("Defausse", &def, EMPLACEMENT_DEFAUSSE_X, EMPLACEMENT_DEFAUSSE_Y, rendu, police);
	creer_texte_combat("Fuir", &fui, EMPLACEMENT_DEFAUSSE_X, EMPLACEMENT_FUITE_Y, rendu, police);

	/*Mise en place du rectangle de selection*/
  	rectangle_selection->x = (def.rectangle).x - RECT_SELECT_X_DIFF;
	rectangle_selection->y = (def.rectangle).y - RECT_SELECT_Y_DIFF;
	rectangle_selection->w = (def.rectangle).w +100;
	rectangle_selection->h = (def.rectangle).h +30;

////////////////boucle combat

	Mix_VolumeMusic(40);
	Mix_PlayMusic(musics[fight], -1);

  	while((ennemi->pv > 0 && perso->pv > 0) && fuite==1 ){

  		//affichage de l'écran et déplacement de rectangle de sélection
  		affichage_combat_personnage(rendu, perso, ennemi, def, fui, rectangle_selection, images, hud_ennemi, hud_pers, action);

  		choix = deplacement_rectangle_selection_combat(def.rectangle, fui.rectangle, images, &rectangle_selection, sounds, musics);


  		if(choix == -1){//le joueur fuit le combat
  			perso->fuite = 1;
  			ennemi->pv = pv_ennemi;
  			fuite = 0;
  		}
  		else if(choix == -2){//défausse de carte(s)

  			defausse(rendu, perso, ennemi, rectangle_selection, images, hud_ennemi, hud_pers, action, police, sounds, musics, cartes);

  		}
  		else if(choix < NB_CARTES_COMBAT && cartes[choix]->type != NO_CARTE){//le joueur a selectionné une carte

  			if(alea){//le joueur commence

  				tour_joueur(perso, ennemi, cartes[choix], rendu, sounds);
					actualisation_apres_tour(perso, ennemi, *cartes[choix], &action, &hud_pers, &hud_ennemi, rendu, police, alea);
					affichage_combat_personnage(rendu, perso, ennemi, def, fui, rectangle_selection, images, hud_ennemi, hud_pers, action);
  				SDL_Delay(wait* 2);
					SDL_RenderPresent(rendu);



  				if(ennemi->pv > 0){
	  				tour_ennemi(perso, ennemi, rendu, sounds);
	  				actualisation_apres_tour(perso, ennemi, *cartes[choix], &action, &hud_pers, &hud_ennemi, rendu, police, alea-1);
						affichage_combat_personnage(rendu, perso, ennemi, def, fui, rectangle_selection, images, hud_ennemi, hud_pers, action);
	  				SDL_Delay(wait);
	  			}
  			}
  			else{//l'ennemi commence

  				tour_ennemi(perso, ennemi, rendu, sounds);
  				actualisation_apres_tour(perso, ennemi, *cartes[choix], &action, &hud_pers, &hud_ennemi, rendu, police, alea);
					affichage_combat_personnage(rendu, perso, ennemi, def, fui, rectangle_selection, images, hud_ennemi, hud_pers, action);
  				SDL_Delay(wait* 2);
					SDL_RenderPresent(rendu);



  				if(perso->pv > 0){
	  				tour_joueur(perso, ennemi, cartes[choix], rendu, sounds);
	  				actualisation_apres_tour(perso, ennemi, *cartes[choix], &action, &hud_pers, &hud_ennemi, rendu, police, alea + 1);
						affichage_combat_personnage(rendu, perso, ennemi, def, fui, rectangle_selection, images, hud_ennemi, hud_pers, action);
	  				SDL_Delay(wait);
	  			}
  			}
  			consommable_epuise(cartes, choix, images, rendu);
  		}
  		detruire_action_temp(&action);
  		while(SDL_PollEvent(&event));
	}

	//Si le joueur meurt
	if(perso->pv <= 0) {
		Mix_HaltMusic();
		mort(etat, perso, rendu, musics, sounds, images, police);
	}

	if(ennemi->pv<=0){
		perso->pv=perso->pv_max;
	}
	Mix_HaltMusic();
  	TTF_CloseFont(police);


  	range_carte_deck(cartes);

  	libere_texture(&def.img);
	libere_texture(&fui.img);
	libere_texture(&hud_ennemi.pv.img);
	libere_texture(&hud_ennemi.nom.img);
	libere_texture(&hud_pers.pv.img);
	libere_texture(&hud_pers.nom.img);

  	detruire_action_temp(&action);

	free_image(images);

	if(rectangle_selection != NULL){
		free(rectangle_selection);
		rectangle_selection=NULL;
	}

	perso->sprites[courant] = perso->sprites[idle_gauche];
	perso->sprites[courant].rectangle.x = perso->x;
	perso->sprites[courant].rectangle.y = perso->y;
}
