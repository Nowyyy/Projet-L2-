int indice_salle(int salle_actuelle, int porte_salle_actuelle, int taille);
int nb_salles_par_etage(int etage);
int salles_compatibles(int salle1, int porte1, int salle2, int porte2, salle_t salles[]);
int tirage_au_sort_porte_a_creer(int indice, int taille, salle_t salles[], int tentatives);
int creation_labyrinthe(salle_t salles[], int taille, int nb_salles_a_creer);
void charge_toutes_textures(image_t images[], perso_t *pers, SDL_Renderer *rendu);
void affichage_salle_personnage(perso_t pers, salle_t *salle, SDL_Renderer *rendu, image_t images[], mini_map_t map, loot_carte_t loot);
void boucle_labyrinthe(int *continuer, int *etat, SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON], Mix_Music * musics[NB_MUSIC], perso_t *pers, TTF_Font *police);
void cree_liaison(salle_t tab[], int salle1, int salle2, int porteS1);
void initialise_salles(salle_t tab[], int taille);
void modifie_texture_hud(perso_t *pers, image_t *pv, image_t *etage, SDL_Renderer *rendu);
void vers_ecran_combat(SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON], touches_t *clavier, perso_t *pers, ennemi_t *ennemi,  Mix_Music *musics[NB_MUSIC]);
void check_ennemi(int* ennemi_max,int compte_ennemi,salle_t salles[],int salle_courante,perso_t *pers);
