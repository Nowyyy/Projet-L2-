void affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers, ennemi_t * ennemi, image_t def, image_t fuir, SDL_Rect *rect_sel,image_t images[NB_TEXTURES], hud_combat_t ennemi_hud, hud_combat_t pers_hud, hud_combat_t action);
int deplacement_rectangle_selection_combat(SDL_Rect defausse, SDL_Rect fuir, image_t images[NB_TEXTURES], SDL_Rect **rect_sel);
void charge_textures_combat(image_t images[], SDL_Renderer *rendu, carte_t *cartes[]);
void donne_valeur_rect_images(image_t images[]);
void free_image(image_t images[]);
void tour_ennemi(perso_t *pers, ennemi_t *ennemi);
void tour_joueur(perso_t *pers, ennemi_t *ennemi, carte_t carte);
void create_hud(hud_combat_t *hud_pers, hud_combat_t *hud_ennemi, ennemi_t ennemi, perso_t pers, SDL_Renderer *rendu, TTF_Font *font);
void init_hud_action(hud_combat_t *action);
void actualisation_apres_tour(perso_t *pers, ennemi_t *ennemi, carte_t carte, hud_combat_t *action, hud_combat_t *hud_pers, hud_combat_t *hud_ennemi, SDL_Renderer *rendu, TTF_Font *font, int  tour);
void detruire_action_temp(hud_combat_t *action);
void combat_t_p_t(perso_t * perso, ennemi_t * ennemi,SDL_Renderer *rendu, image_t images[NB_TEXTURES]);
