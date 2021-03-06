void charge_sprites_personnage(image_t sprites[], SDL_Renderer *rendu);
void init_animations(animation_t *anim);
void animations_personnage(image_t sprites[], unsigned int timer, touches_t clavier, animation_t *anim, Mix_Chunk *footsteps);
void deplacement_personnage(perso_t *pers, salle_t salle, int *continuer, animation_t *anim, Mix_Chunk *sounds[NB_SON], touches_t *clavier, int *etat);
int test_collision(salle_t salle, perso_t *pers, int direction);
int changement_de_salle(perso_t *pers, salle_t salle, int indice, Mix_Chunk *sounds[NB_SON]);
void initialise_personnage(perso_t *pers);
void change_animation(animation_t *anim, image_t sprites[], int nouvelle_animation);
int collision_perso_ennemi(perso_t pers, ennemi_t ennemi);
int combat_declenche(salle_t salle, perso_t pers);
void creer_texture_depuis_char(image_t *texte_pv, image_t *texte_etage, perso_t perso, SDL_Renderer *rendu,image_t *texte_counter,int *compte_ennemi,int *ennemi_max);
