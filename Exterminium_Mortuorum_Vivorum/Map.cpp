#include "Map.h"


inline int Map::indice(int x, int y)                                                                                                                        // Transforme les coordonnees (x, y) en indice du tableau
{
    return y * Largeur + x;
}

bool Map::chargerCarte(const std::string& nomFichier)                                                                                                      // Charge la map
{
    std::ifstream fichier(nomFichier);                                                                                                               // Ouvre le fichier du niveau.
    if (!fichier.is_open()) return false;
    std::vector<std::string> lignes;
    std::string ligne;

    while (getline(fichier, ligne))
    {
        if (!ligne.empty() && ligne.back() == '\r')                                                                                             // suprime les espaces et les retour a la ligne
            ligne.pop_back();                                                                                                                   // suprime le caractere

        if (!ligne.empty())                                                                                                                     // si la ligne n'est pas vide rajoute une ligne au tableaus dinamique par vecteur
            lignes.push_back(ligne);
    }
    fichier.close();                                                                                                    // Crée un nouveau tableau d'ennemis avec la taille appropriée.

    Hauteur = static_cast<int>(lignes.size());                                                                                                  // Calcule la hauteur avec le nombre de lignes, convertit ce nombre en entier car ce n'est pas des int
    Largeur = static_cast<int>(lignes[0].size());                                                                                               // Calcule la largeur avec la premiere ligne, convertit ce nombre en entier car ce n'est pas des int

    map.clear();                                                                                                                                // supprime tous les terrains de la carte précédente

    spawnX = -1;                                                                                                                                // Reinitialise la position de depart.
    spawnY = -1;
    sortieX = -1;                                                                                                                               // Reinitialise la position de sortie.                
    sortieY = -1;
    int i = 0;
    for (int y = 0; y < Hauteur; y++)
    {
        for (int x = 0; x < Largeur; x++)
        {
            char symbole = lignes[y][x];                                                                                                        // Lit le symbole de la case actuelle.

            if (symbole == 'S')
            {
                spawnX = x;                                                                                                                     // Enregistre la coordonnee X du depart.        
                spawnY = y;                                                                                                                     // Enregistre la coordonnee Y du depart.
                map.push_back(ground);                                                                                                          // Le depart est du sol dans le tableau de terrain.
            }
            else if (symbole == 'E')
            {
                sortieX = x;                                                                                                                    // Enregistre la coordonnee X de la sortie.
                sortieY = y;                                                                                                                    // Enregistre la coordonnee Y de la sortie.
                map.push_back(ground);                                                                                                          // La sortie reste du sol dans le tableau de terrain.
            }
            else if (symbole == '.')
                map.push_back(ground);                                                                                                          // Ajoute une case de sol.
            else if (symbole == '~')
            {
                map.push_back(river);                                                                                                           // Ajoute une case de riviere.
            }
            else if (symbole == 'A')
            {
                map.push_back(mountain);                                                                                                        // Ajoute une case de montagne.                                                                                                        // Le depart est du sol dans le tableau de terrain.
            }
            else if (symbole == 'Z')
            {
                map.push_back(ground);
            }
            else
                return false;                                                                                                                   // Refuse les symboles inconnus.
        }
    }
    return true;                                                                                                                                // La carte a ete chargee avec succes.
}

void Map::afficherCarte(const Player& hero, const Enemy ennemis[])                                                                           // Affiche le terrain, le heros et les ennemis.
{
    erase();                                                                                                                                    // Efface l'affichage precedent.
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);                                                                                                     // Couleur du heros visible.
    init_pair(2, COLOR_BLUE, COLOR_BLACK);                                                                                                      // Couleur du heros cacher.
    init_pair(3, COLOR_RED, COLOR_BLACK);                                                                                                       // Couleur de l'ennemi.
    init_pair(4, COLOR_GREEN, COLOR_BLACK);                                                                                                     // Couleur de la sortie.
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);                                                                                                    // Couleur du sol.
    init_pair(6, COLOR_CYAN, COLOR_BLACK);                                                                                                      // Couleur de la riviere.
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);                                                                                                   // Couleur de la montagne.

    for (int y = 0; y < Hauteur; y++)
    {
        for (int x = 0; x < Largeur; x++)
        {
            char symbole = '.';
            int i = indice(x, y);                                                                                                               // Calcule les coordonées

            //if (hero.x == x && hero.y == y)
            //{
            //    if (hero.hidden)
            //        symbole = 'S';                                                                                                              // S = heros cacher
            //    else
            //        symbole = 'H';                                                                                                              // H = heros visible
            //}
            //
            //else if (ennemiPresent(ennemis, x, y))
            //    symbole = 'X';                                                                                                                   // X = ennemi
            if (x == sortieX && y == sortieY)
                symbole = 'E';                                                                                                                  // E = sortie
            else if (map[i] == ground)
                symbole = '.';                                                                                                                  // . =  sol.
            else if (map[i] == river)
                symbole = '~';                                                                                                                  // ~ = riviere.
            else if (map[i] == mountain)
                symbole = 'A';                                                                                                                  // A =  montagne.


            if (has_colors() == true)
            {
                if (symbole == 'H')
                    attron(COLOR_PAIR(1));                                                                                                      // Couleur du heros visible.
                else if (symbole == 'S')
                    attron(COLOR_PAIR(2));                                                                                                      // Couleur du heros cacher.
                else if (symbole == 'X')
                    attron(COLOR_PAIR(3));                                                                                                      // Couleur de l'ennemi.
                else if (symbole == 'E')
                    attron(COLOR_PAIR(4));                                                                                                      // Couleur de la sortie.
                else if (symbole == '.')
                    attron(COLOR_PAIR(5));                                                                                                      // Couleur du sol.
                else if (symbole == '~')
                    attron(COLOR_PAIR(6));                                                                                                      // Couleur de la riviere.
                else if (symbole == 'A')
                    attron(COLOR_PAIR(7));                                                                                                      // Couleur de la montagne.
            }
            mvaddch(y, x, symbole);                                                                                                             // Affiche symbole aux coordonnees (y, x), aprés les couleurs pour les appliquer
        }
    }
    mvprintw(Hauteur + 1, 0, "Z : haut S : bas Q : gauche D : droite");
    mvprintw(Hauteur + 2, 0, "R : quitter E : sort      Ennergie pour lancer le sort requis : 20");
    //(Hauteur + 3, 0, "PV : %d", hero.pv);                                                                                               // Affiche les points de vie restants.
    //mvprintw(Hauteur + 5, 0, "Oxygene : %d", hero.oxygene);

    //if (hero.hidden)
    //    mvprintw(Hauteur + 4, 0, "Le heros est cache dans la riviere.");
    //else
    //    mvprintw(Hauteur + 4, 0, "Le heros est visible.");

    mvprintw(Hauteur + 6, 0, "Niveau : %d", niveau);
    mvprintw(Hauteur + 7, 0, "Objectif : atteindre la sortie E.");
    if (has_colors() == false)
    {
        mvprintw(Hauteur + 8, 0, "Votre terminal ne supporte pas les couleurs.");
    }
    //mvprintw(Hauteur + 9, 0, "Energie Total : %d / 30", hero.energie);
    //if (EnergieInsufisante == true) {
    //    mvprintw(Hauteur + 10, 0, "Energie insufissante : %d / 20", hero.energie);
    //}
    //if (EnnemieTuable == true) 
    //{
    //    mvprintw(Hauteur + 10, 0, "Aucun ennemie reperer, sort echouer, ennergie perdue");
    //}
    refresh();                                                                                                                                  // Met a jour l'ecran.
}
