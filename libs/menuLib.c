#include "menuLib.h"

WINDOW *win;

/**
 * @fn int createMenu(char **choices, int nbChoices, const char *title)
 * 
 * @brief Créer un menu
 * @param choices Tableau de choix
 * @param nbChoices La longueur du tableau
 * @param title Le titre du menu
 * @return L'index du choix sélectionné
*/
int createMenu(char **choices, int nbChoices, const char *title) {

  int i; // Compteur
  int curr = 0; // Item courant

  // Initialisation de la fenêtre
  initscr();
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK); // On définit une paire de couleur jaune sur fond noir
  cbreak(); // Pas de bufferisation
  noecho(); // Pas d'affichage des caractères
  keypad(stdscr, TRUE); // On active les touches spéciales (flèches, etc.)

  // Création de la fenêtre avec une taile de 30 lignes et 35 colonnes
  win = newwin(30, 35, 0, 0);

  box(win, 0, 0);
  refresh();

  // Affichage du titre
  mvwprintw(win, 0, 2, "%s", title);

  // Naviguer dans le menu
  curr = naviguerMenu(choices, nbChoices, curr);

  endwin();

  printf("Vous avez choisi : %s\n", choices[curr]);

  return curr;
}

/**
 * @fn void afficherMenu(char **choices, int nbChoices, int curr)
 * 
 * @brief Affiche le menu
 * @param choices Tableau de choix
 * @param nbChoices La longueur du tableau
 * @param curr L'index du choix courant
*/
void afficherMenu(char **choices, int nbChoices, int curr) {
  // Afficher et naviguer dans le menu
  int i;

  curs_set(0); // Désactive le curseur
  for(i = 0; i < nbChoices; i++) {
    if(i == curr) {
      // Mettre en surbrillance l'item courant
      wattron(win, A_REVERSE);
      mvwprintw(win, i+1, 4, "%s", choices[i]);
      wattroff(win, A_REVERSE);
    } else {
      mvwprintw(win, i+1, 4, "%s", choices[i]);
    }
  }
  
  // Rafraîchir la fenêtre
  wrefresh(win);

}

/**
 * @fn int naviguerMenu(char **choices, int nbChoices, int curr)
 * 
 * @brief Navigue dans le menu
 * @param choices Tableau de choix
 * @param nbChoices La longueur du tableau
 * @param curr L'index du choix courant
 * @return L'index du choix sélectionné
*/
int naviguerMenu(char **choices, int nbChoices, int curr) {
  // Naviguer dans le menu
  int c, i;
  while(1) {
      afficherMenu(choices, nbChoices, curr);
        c = getch();
        switch(c) {
            case KEY_UP:
                if (curr > 0) curr--;
                break;
            case KEY_DOWN:
                if (curr < nbChoices - 1) curr++;
                break;
            case 27: // L'utilisateur a appuyé sur la touche Echap
                // On renvoie -1 pour indiquer que l'utilisateur a quitté le menu
                return -1;
            case 10: // L'utilisateur a appuyé sur la touche Entrée
                // On renvoie l'item courant
                return curr;
            break;
        }
    }
    return -1;
}
