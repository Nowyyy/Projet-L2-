int main_menu(int *continuer, int *etat, SDL_Renderer *rendu, TTF_Font *police);
void deplacement_rectangle_selection(SDL_Rect jouer, SDL_Rect charger, SDL_Rect quitter, SDL_Rect **rect_sel, int *etat);
void affichage_menu(SDL_Renderer *rendu, SDL_Texture *jouer_text, SDL_Texture *charger_text, SDL_Texture *quitter_text, SDL_Rect *rect_sel, SDL_Rect jouer_rect, SDL_Rect charger_rect, SDL_Rect quitter_rect);
