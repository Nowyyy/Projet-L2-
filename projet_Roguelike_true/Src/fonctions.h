/**
*\file fonctions.h
*\brief fichier qui permet de référencer tous les prototypes de fonction du système de combat.
*\author {Malabry Thomas Aurélien Tudoret Jourry Axel Marin Timothée}
*\version 1.0
*\date 13/02/2020
*/


/**
*\fn carte_t * creer_carte(char *, type_carte, int *, int)
*\brief permet de créer une carte selon différentes caractéristiques donnés
*\param nom pour le nom de la carte
*\param type pour le type de la carte
*\param cible pour la cible de la carte
*\param valeur pour la valeur de la force de la carte
*/
carte_t * creer_carte(char *, type_carte, int, int);

/**
*\fn perso_t * creer_perso()
*\brief permet de créer un personnage selon différentes caractéristiques
*/
perso_t * creer_perso();

/**
*\fn ennemi_t * creer_ennemi(char *)
*\brief permet de créer un ennemi selon plusieurs caractéristiques
*\param nom pour le nom d'un ennemi
*\return un pointeur sur une variable structure ennemi_t
*/
ennemi_t * creer_ennemi(char *, int, int, int, int);

ennemi_t * generer_ennemi(int);

/**
*\fn void detruire_carte(carte_t **)
*\brief Fonction qui permet de détruire une carte
*\param carte Un pointeur de pointeur de carte qui permet de détruire le pointeur qui pointe sur la structure carte
*/
void detruire_carte(carte_t **);

/**
*\fn detruire_perso(perso_t **)
*\brief Fonction qui permet de détruire un personnage
*\param perso Un pointeur de pointeur de perso qui permet de détruire le pointeur qui pointe sur la structure perso
*/
void detruire_perso(perso_t **);

/**
*\fn void detruire_ennemi(ennemi_t **)
*\brief Fonction qui permet de détruire un ennemi
*\param perso Un pointeur de pointeur de ennemi qui permet de détruire le pointeur qui pointe sur la structure ennemi
*/
void detruire_ennemi(ennemi_t **);

/**
*\fn int initiative (perso_t *, ennemi_t *)
*\brief Fonction qui permet savoir si c'est l'ennemi ou le personnage qui combat en premier
*\param perso Un pointeur sur la structure perso_t qui permet de prendre la vitesse pour la comparé à l'ennemi
*\param perso Un pointeur sur la structure ennemi_t qui permet de prendre la vitesse pour la comparé au personnage
*/
int initiative (perso_t *, ennemi_t *);


/**
*\fn void tour_ennemi(perso_t *, ennemi_t *)
*\brief Fonction qui permet à l'ennemi d'effectuer une action
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action de l'ennemi
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action de l'ennemi
*/
void tour_ennemi(perso_t *, ennemi_t *);


/**
*\fn tour_perso(int, perso_t *, ennemi_t *, carte_t **)
*\brief Fonction qui permet au personnage d'effectuer une action
*\param choix Entier qui va permettre au personnage un choix selon les instructions de l'utilisateur
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action du personnage
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action du personnage
*\param deck Pointeur sur un pointeur de fonction qui permet de connaître le deck du personnage
*/
int tour_perso(int, perso_t *, ennemi_t *, carte_t **);

/**
*\fn void combat(perso_t *, ennemi_t *, carte_t **)
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action du personnage
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action du personnage
*\*\param deck Pointeur sur un pointeur de fonction qui permet de connaître le deck du personnage
*/
void combat(perso_t *, ennemi_t *);

void init_liste();
int liste_vide();
int hors_liste();
void en_tete();
void en_queue();
void precedent();
void suivant();
void valeur_elt(carte_t*);
void modif_elt(carte_t);
void oter_elt();
void ajout_droit(carte_t*);
void ajout_gauche(carte_t*);