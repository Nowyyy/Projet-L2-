/**
*\file sauvegardefonc.c
*\brief Fichier qui référence les différentes fonctions de sauvegarde
*\author Malabry Thomas Aurélien Tudoret Jourry Axel Marin Timothée
*\version 1.0
*\date 13/05/2020
*/

#include "../include/constantes.h"
#include "../include/fonctions.h"


//Ecrit par Aurélien Tudoret
/**
*\fn int save_existe()

*\return Retourne 1 si une sauvegarde existe, 0 sinon

*\brief Regarde si une sauvegarde existe
*/
int save_existe(){

  FILE *f;

  f = fopen(SAVE_CARTES_COLLEC_PATH, "r");

  if(!f)
    return 0;

  fclose(f);

  return 1;
}


//Ecrit par Thomas Malabry. Ajouts par Aurélien Tudoret
/**
*\fn void savecarte (char *path, int liste)
*\param *path Contient le fichier où l'on va sauvegarder les cartes
*\param liste la liste de carte a sauvegarder
*\brief Fonction qui permet de sauvegarde toutes les données d'une carte
*/
void savecarte (char *path, int liste){

  FILE *fichier=NULL;

  carte_t* carte2;

  fichier=fopen(path,"w");
  choix_liste(liste);
  en_tete();

  if (fichier != NULL)
   {
      if(!liste_vide(liste)){
        while(!hors_liste() && !liste_vide()){
          valeur_elt(&carte2);
          fprintf(fichier,"%d %d %d %s %s\n",carte2->type,carte2->valeur,carte2->consommable,carte2->path,carte2->nom);
          suivant();
        }
      }
      else{
        fprintf(fichier, "\n");
      }
   }
   fclose(fichier);
}


//Ecrit par Thomas Malabry. Ajouts par Aurélien Tudoret et Timothée Marin
/**
*\fn void readcarte(char *path_file, int liste)
*\param *path_file Contient le fichier où l'on va sauvegarder les cartes
*\param liste la liste de carte a sauvegarder
*\brief Fonction qui permet de lire une carte
*/
void readcarte(char *path_file, int liste){

  FILE *fichier=NULL;

  fichier=fopen(path_file,"r");

  char nom[20], path[100];/** Nom d'une carte */
  type_carte type;/** Type d'une carte */
  int valeur, consommable;

  if (fichier != NULL)
    {
      fscanf(fichier,"%d%d%d%s %[^\n]",&type,&valeur,&consommable,path,nom);

      choix_liste(liste);
      en_tete();

        while(!feof(fichier)){
          if(!strcmp(path_file,SAVE_CARTES_NEW_GAME_PATH) && liste == DECK){
            ajout_droit(creer_carte(nom,type,valeur_carte(nom),consommable,path));
          }
          else {
            ajout_droit(creer_carte(nom,type,valeur,consommable,path));
          }
          fscanf(fichier,"%d%d%d%s %[^\n]",&type,&valeur,&consommable,path,nom);
        }
    }
    fclose(fichier);
}


//Ecrit par Thomas Malabry. Ajouts par Aurélien Tudoret
/**
*\fn void saveperso (perso_t *perso)
*\param *perso Pour savoir les données du perso à sauvegarder
*\brief Fonction permet de sauvegarder les données du personnage

*/
void saveperso (perso_t *perso){

  FILE *fichier=NULL;

  char *nom_fichier = malloc(sizeof(char)* 100);

  strcpy(nom_fichier, SAVE_PERSO_PATH);

  fichier=fopen(nom_fichier,"w+");

  if (fichier != NULL)
   {
       fprintf(fichier,"%d %d %d %d %d %d\n",perso->pv,perso->x,perso->y, perso->etage, perso->cmpMort, perso->pv_max);
   }
   fclose(fichier);
   if(nom_fichier != NULL){
     free(nom_fichier);
     nom_fichier=NULL;
   }
}


//Ecrit par Thomas Malabry. Ajouts par Aurélien Tudoret
/**
*\fn void readperso(perso_t *perso)
*\param *perso savoir les données du perso à sauvegarder
*\brief Fonction qui permet de lire les données du personnage
*/
void readperso(perso_t*perso){

  FILE *fichier=NULL;

  char *nom_fichier = malloc(sizeof(char)* 100);

  strcpy(nom_fichier, SAVE_PERSO_PATH);

  fichier=fopen(nom_fichier,"r");

  if (fichier != NULL)
   {
       fscanf(fichier,"%d %d %d %d %d %d\n",&perso->pv,&perso->x,&perso->y,&perso->etage, &perso->cmpMort, &perso->pv_max);
   }
   fclose(fichier);
   if(nom_fichier != NULL){
     free(nom_fichier);
     nom_fichier=NULL;
   }
}
