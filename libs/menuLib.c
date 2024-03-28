#include "menuLib.h"

WINDOW *win;

#define X_RPI 106
#define Y_RPI 29

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
  init_pair(1, COLOR_GREEN, COLOR_BLACK); // On définit une paire de couleur jaune sur fond noir
  cbreak(); // Pas de bufferisation
  noecho(); // Pas d'affichage des caractères
  keypad(stdscr, TRUE); // On active les touches spéciales (flèches, etc.)

  // Centrer la fenêtre avec dimension RPI
  win = newwin(15, 40, (Y_RPI/2)-10, (X_RPI/2)-25);

  box(win, 0, 0);
  refresh();

  // Affichage du titre en jaune
  wattron(win, A_BOLD);
  wattron(win, COLOR_PAIR(1));
  mvwprintw(win, 0, 2, "%s", title);
  wattroff(win, COLOR_PAIR(1));
  wattroff(win, A_BOLD);

  // Naviguer dans le menu
  curr = naviguerMenu(choices, nbChoices, curr);

  endwin();

  printf("Vous avez choisi : %s\n", choices[curr]);

  return curr;
}


/**
 * @fn void createMenuText(char **text, int nbText, const char *title)
 * 
 * @brief Créer un menu avec du texte
 * @param text Tableau de texte
 * @param nbText La longueur du tableau
 * @param title Le titre du menu
*/
void createMenuText(char **text, int nbText, const char *title) {
  
  int i;
  int curr = 0;

  // Initialisation de la fenêtre
  initscr();
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  cbreak(); // Pas de bufferisation
  noecho(); // Pas d'affichage des caractères
  keypad(stdscr, TRUE);

  // Création de la fenêtre
  win = newwin(30, 50, Y_RPI, X_RPI);
  box(win, 0, 0);
  
  refresh();

  // Affichage du titre
  wattron(win, A_BOLD);
  wattron(win, COLOR_PAIR(1));
  mvwprintw(win, 0, 2, "%s", title);
  wattroff(win, COLOR_PAIR(1));
  wattroff(win, A_BOLD);

  wattron(win, A_REVERSE);
  mvwprintw(win, 28, 16, "Exit (press Esc)");
  wattroff(win, A_REVERSE);

  // Affichage des éléments
  afficherMenu(text, nbText, curr, 0);

  wrefresh(win);

  while(1) {
    curr = getch();
    // escape
    if(curr == 27) break;
  }

  endwin();
}


/**
 * @fn void afficherMenu(char **choices, int nbChoices, int curr)
 * 
 * @brief Affiche le menu
 * @param choices Tableau de choix
 * @param nbChoices La longueur du tableau
 * @param curr L'index du choix courant
 * @param highlight Mettre en surbrillance l'item courant (0 : non, 1 : oui)
*/
void afficherMenu(char **choices, int nbChoices, int curr, int highlight) {
  int i;
  init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Bleu sur fond noir

  curs_set(0);
  for (i = 0; i < nbChoices; i++) {
    if (i == curr && highlight) {
      wattron(win, A_REVERSE);
    }

    // Couleur bleue pour la première lettre
    wattron(win, COLOR_PAIR(2));
    mvwaddch(win, i+1, 4, choices[i][0]); // Affiche la première lettre en bleu
    wattroff(win, COLOR_PAIR(2));
    wprintw(win, "%s", &choices[i][1]); // Le reste en blanc

    // Désactive la surbrillance après l'avoir utilisée
    if (i == curr && highlight) {
      wattroff(win, A_REVERSE);
    }
  }
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
  int c;
  while(1) {
      afficherMenu(choices, nbChoices, curr, 1);
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
