#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <menu.h>

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
int createMenu(char **choices, int nbChoices, const char *title);

/**
 * @fn void createMenuText(char **text, int nbText, const char *title)
 * 
 * @brief Créer un menu avec du texte
 * @param text Tableau de texte
 * @param nbText La longueur du tableau
 * @param title Le titre du menu
*/
void createMenuText(char **text, int nbText, const char *title);

/**
 * @fn void afficherMenu(char **choices, int nbChoices, int curr)
 * 
 * @brief Affiche le menu
 * @param choices Tableau de choix
 * @param nbChoices La longueur du tableau
 * @param curr L'index du choix courant
 * @param highlight Mettre en surbrillance l'item courant (0 : non, 1 : oui)
*/
void afficherMenu(char **choices, int nbChoices, int curr, int highlight);

/**
 * @fn int naviguerMenu(char **choices, int nbChoices, int curr)
 * 
 * @brief Navigue dans le menu
 * @param choices Tableau de choix
 * @param nbChoices La longueur du tableau
 * @param curr L'index du choix courant
 * @return L'index du choix sélectionné
*/
int naviguerMenu(char **choices, int nbChoices, int curr);

#endif