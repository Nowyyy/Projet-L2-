/**

*\file etage_final.c

*\author Tudoret Aurélien, Jourry Axel, Marin Timothée, Malabry Thomas

*\date 13/05/2020

*\version 1.0

*\brief Permet d'afficher et de gèrer le dernier étage et le combat contre le boss
*/



#include "../include/constantes.h"
#include "../include/salle.h"
#include "../include/combat_tour_par_tour.h"
#include "../include/animation.h"
#include "../include/ennemi.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/personnage.h"
#include "../include/fonctions.h"
#include "../include/sauvegardefonc.h"
#include "../include/clavier.h"
#include "../include/labyrinthe.h"


//Ecrit par Aurélien Tudoret
/**
*\fn void charge_textures_etage_final(image_t images[], perso_t *pers, SDL_Renderer *rendu)

*\param images[] contient toutes les images utilisées sauf celle du personnage
*\param *pers le pointeur sur la structure contenant le personnage
*\param *rendu le renderer sur lequel on dessine

*\brief Permet de charger toutes les images et de les ranger dans les structures correspondantes

*/
void charge_textures_etage_final(image_t images[], perso_t *pers, SDL_Renderer *rendu){

	int x= 0;

	charge_image(SOL1_2_PATH,&images[sol], rendu);
	charge_image(MUR1_2_PATH,&images[mur], rendu);
	charge_image(MUR2_2_PATH,&images[mur2], rendu);
	charge_image(PORTE_2_PATH,&images[porte], rendu);
	charge_image(SOL2_2_PATH,&images[sol2], rendu);
	charge_image(SOL3_2_PATH,&images[sol3], rendu);

	charge_image(HEART_PATH, &images[heart], rendu);
	charge_image(TRAPDOOR_PATH, &images[trapdoor], rendu);

	charge_sprites_personnage(pers->sprites, rendu);

	creer_texture_depuis_char(&images[pv], &images[etage], *pers, rendu,&images[countertxt],&x,&x);

	images[heart].rectangle.x = 25;
	images[heart].rectangle.y = WIN_HEIGHT * 0.10;
	images[trapdoor].rectangle.x = 0;
	images[trapdoor].rectangle.y = WIN_HEIGHT * 0.02;

	pers->sprites[courant] = pers->sprites[idle_droite];

	//on place le personnage dans la premiere salle, au centre
	pers->sprites[courant].rectangle.x = pers->x;
	pers->sprites[courant].rectangle.y = pers->y;
}


//Ecrit par Aurélien Tudoret
/**
*\fn void affichage_salle_personnage_etage_final(perso_t pers, salle_t *salle, SDL_Renderer *rendu, image_t images[])

*\param pers la structure contenant le personnage
*\param *salle la salle actuelle
*\param *rendu le renderer sur lequel on dessine
*\param images[] contient toutes les images utilisées sauf celle du personnage

*\brief Permet d'afficher une salle, le personnage et si on est dans la premiere salle, les instructions et commandes du jeu

*/
void affichage_salle_personnage_etage_final(perso_t pers, salle_t *salle, SDL_Renderer *rendu, image_t images[]){


	SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

	SDL_RenderClear(rendu);//nettoie l'écran pour supprimer tout ce qui est dessus

	///////////SALLE
	afficher_salle(salle, rendu, images);

	///////////PERSONNAGE
	SDL_RenderCopy(rendu, pers.sprites[courant].img, NULL, &pers.sprites[courant].rectangle);

	///////////HUD
	SDL_RenderCopy(rendu, images[pv].img, NULL, &images[pv].rectangle);
	SDL_RenderCopy(rendu, images[etage].img, NULL, &images[etage].rectangle);
	SDL_RenderCopy(rendu, images[heart].img, NULL, &images[heart].rectangle);
	SDL_RenderCopy(rendu, images[trapdoor].img, NULL, &images[trapdoor].rectangle);

  	if(salle->boss)
  		if(salle->ennemi->pv > 0)
			SDL_RenderCopy(rendu, salle->ennemi->sprites.img, &salle->ennemi->sprite_courant, &salle->ennemi->sprites.rectangle);

  	SDL_RenderPresent(rendu);//applique les modifs précédentes
}


//Ecrit par Aurélien Tudoret
/**
*\fn void creation_salles_dernier_etage(salle_t salles[], int taille, SDL_Renderer *rendu)


*\param salles[] le tableau de structure de salle.
*\param taille la taille de l'étage
*\param *rendu le renderer sur lequel on dessine

*\brief Créée les deux salles du dernier étage, les lies l'une à l'autre et rempli les tableau de collisions
*/
void creation_salles_dernier_etage(salle_t salles[], int taille, SDL_Renderer *rendu){

	ennemi_t ennemi_tmp;

	ennemi_selon_etage(5, 1, &ennemi_tmp);

	initialise_salles(salles, taille); //initialisation de toutes les salles.

	salles[0].s_d = 1;
	salles[1].s_g = 0;

	ajout_porte_salle(salles[1].salle, 3);
	ajout_porte_salle(salles[0].salle, 1);

	salles[1].ennemi = creer_ennemi(ennemi_tmp.pv, ennemi_tmp.attaque, ennemi_tmp.attaque, ennemi_tmp.attaque, sorcerer, rendu);

	salles[1].boss = TRUE; // on marque tout de suite la salle du boss

	salles[1].ennemi->last = SDL_GetTicks();

	//remplissage tableau de collisions pour les murs et les portes
	for(int i = 0; i < taille; i++){
		rempli_tableau_murs_portes(salles, i);
	}
}


//Créé par Aurélien Tudoret. Modifications par Axel Jourry
/**
*\fn void ecran_victoire(SDL_Renderer * rendu, TTF_Font *police, Mix_Music *musics[NB_MUSIC], int mort)

*\param *rendu le renderer sur lequel on dessine
*\param *police la police utilisée pour écrire à l'écran
*\param *musics[NB_MUSIC] le tableau contenant les musiques
*\param mort le nombre de morts du joueur

*\brief Affiche le message de victoire à l'intention du joueur, signifiant sa réussite totale dans le jeu
*/
void ecran_victoire(SDL_Renderer * rendu, TTF_Font *police, Mix_Music *musics[NB_MUSIC], int mort){

	char texte_victoire[50] = "Felicitations ! Vous vous etes echappes !";
	int x_cmpPartie = WIN_WIDTH / 2-90;
	int y_cmpPartie = WIN_HEIGHT * 0.8;
	SDL_Texture *cmpPartie_texture;
	SDL_Rect cmpPartie_text;
	char cmpPartie[20];
	image_t texte_struct;
	image_t logo[1];

//Affichage du logo du jeu
	get_text_and_rect(rendu, WIN_WIDTH *0.20, WIN_HEIGHT / 2, texte_victoire, police, &texte_struct.img, &texte_struct.rectangle);
	charge_image("../Images/logo.png", &logo[0], rendu);

	logo[0].rectangle.x = 140;
	logo[0].rectangle.y = 60;

//Affichage du compteur de mort
	sprintf(cmpPartie, "en %d morts", mort);

	SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

	SDL_RenderClear(rendu);

//Affichage du texte de fin
	get_text_and_rect(rendu, x_cmpPartie, y_cmpPartie, cmpPartie, police, &cmpPartie_texture, &cmpPartie_text);

	SDL_RenderCopy(rendu, cmpPartie_texture, NULL, &cmpPartie_text);
	SDL_RenderCopy(rendu, logo[0].img, NULL, &logo[0].rectangle);
	SDL_RenderCopy(rendu, texte_struct.img, NULL, &texte_struct.rectangle);

	SDL_RenderPresent(rendu);
	Mix_VolumeMusic(30);
	Mix_PlayMusic(musics[victory], 0);

	while(Mix_PlayingMusic() == 1);


	libere_texture(&texte_struct.img);

	if(logo[0].img!=NULL){
		SDL_DestroyTexture(logo[0].img);
		logo[0].img=NULL;
	}
}


//Ecrit par Aurélien Tudoret, Ajouts par Axel Jourry
/**
*\fn void etage_final(SDL_Renderer *rendu, int *continuer, int *etat, Mix_Chunk *sounds[NB_SON], Mix_Music *musics[NB_MUSIC], perso_t *pers, TTF_Font *police)

*\param *rendu le renderer sur lequel on dessine
*\param *continuer le pointeur sur variable permettant de savoir si le joueur souhaite quitter le programme
*\param *etat le pointeur sur variable permettant de connaître l'écran dans lequel on est
*\param *sounds[NB_SON] le tableau contenant les sons
*\param *musics[NB_MUSIC] le tableau contenant les musiques
*\param *pers la structure du personnage
*\param *police la police utilisée pour écrire du texte sur l'écran de jeu

*\brief Permet de gèrer le dernier étage du jeu
*/
void etage_final(SDL_Renderer *rendu, int *continuer, int *etat, Mix_Chunk *sounds[NB_SON], Mix_Music *musics[NB_MUSIC], perso_t *pers, TTF_Font *police){

//////Déclarations

	image_t images[NB_TEXTURES_LABY];

	salle_t salles[TAILLE_ETAGE_FINAL];

	animation_t anim;

	touches_t clavier;

	SDL_Event event;

	int indice_salle = 0, test = 1;

//////Initialisations

	init_tableau_images(images);

	creation_salles_dernier_etage(salles, TAILLE_ETAGE_FINAL, rendu);

	init_animations(&anim);

	init_tab_clavier(clavier.tab);

	charge_textures_etage_final(images, pers, rendu);

	textures_aleatoires(salles, TAILLE_ETAGE_FINAL);



/////////////////////////// boucle du labyrinthe / explo / combat ///////////////////////////
	while(*continuer == TRUE && *etat == labyrinthe && test){

		if(salles[indice_salle].boss && salles[indice_salle].ennemi->pv > 0)
			animation_ennemi(salles[indice_salle].ennemi);

		affichage_salle_personnage_etage_final(*pers, &salles[indice_salle], rendu, images);

		deplacement_personnage(pers, salles[indice_salle], continuer, &anim, sounds, &clavier, etat);

		indice_salle = changement_de_salle(pers, salles[indice_salle], indice_salle, sounds);

		SDL_Delay(5);

		if(combat_declenche(salles[indice_salle], *pers) == 1 && salles[indice_salle].ennemi->pv > 0 && *etat == labyrinthe){

			vers_ecran_combat(rendu, sounds, &clavier, pers, salles[indice_salle].ennemi, musics, etat);

			test = (pers->pv > 0 && salles[indice_salle].ennemi->pv <= 0) ? 0 : 1;
		}

		if(pers->fuite){//le joueur à fuit le combat, on le renvoie dans la première salle du niveau
			pers->fuite = 0;
			indice_salle = 0;
		}
	}

	Mix_HaltMusic();

	while (SDL_PollEvent (&event));

	if(pers->pv > 0 && !test){
	// Affichage de l'écran de fin de jeu si le joueur est vainqueur
		affichage_salle_personnage_etage_final(*pers, &salles[indice_salle], rendu, images);
		Mix_HaltMusic();

		SDL_Delay(2000);//pour voir la salle vide dans le laby
		ecran_victoire(rendu, police, musics, pers->cmpMort);
		*etat = mainMenu;

		initialise_personnage(pers);

		saveperso(pers);//on sauvegarde le personnage et le deck afin de les préserver
  		savecarte(SAVE_CARTES_COLLEC_PATH, COLLEC);

		//on détruit les listes, afin d'éviter les conflits entre les sauvegardes et la duplication
		//de cartes
		detruire_liste(DECK);
		detruire_liste(COLLEC);
		init_liste();

		//Charge à nouveau les cartes de la collec précédement sauvegardées
 		readcarte(SAVE_CARTES_COLLEC_PATH, COLLEC);

		transfert_mort();//on prend des cartes de la collec pour les mettre dans le deck

  		savecarte(SAVE_CARTES_DECK_PATH, DECK);//on sauvegarde le deck remplit de nouvelles cartes
	}

	//////////////////////// On libère tous les emplacements mémoires utilisés par les images ////
	for(int i = 0; i < NB_SPRITES_PERSONNAGE; i++)
		libere_texture(&pers->sprites[i].img);

	for(int i = sol; i < NB_TEXTURES_LABY; i++)
		libere_texture(&images[i].img);

	destruction_tous_ennemis(salles, TAILLE_ETAGE_FINAL);
}
