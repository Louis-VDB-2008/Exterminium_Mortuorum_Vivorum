#pragma once
#include <iostream>
#include <random>
#include <curses.h>                                                                                                                         // fennetre et couleurs
#include <cstdlib>                                                                                                                          // Pour utiliser abs().
#include <fstream>                                                                                                                          // Pour lire les fichiers de niveaux.
#include <string>                                                                                                                           // Pour utiliser des string
#include <vector>                                                                                                                           // Pour stocker la carte dans un tableau dynamique.
#include <windows.h>                                                                                                                        // Nécessaire pour Windows API, musique
#include <mmsystem.h>                                                                                                                       // Nécessaire pour le système multimédia, musique
#include "vector2.h"
#include "Player.h"
#include "Enemy.h"


class Map
{
public:
    
    int indice(int x, int y);
    bool chargerCarte(const std::string& nomFichierenemies);
    void afficherCarte(const Player& hero, const Enemy ennemis[]);
    enum tile_type
    {
        ground = 0,
        river = 1,
        mountain = 2
    };

    std::vector<tile_type> map;

    std::string nomFichier = "map/Niveau" + std::to_string(niveau) + ".txt";                                                                          // Construit le nom du fichier du niveau, to string convertit le int en string
    Enemy* ennemis = nullptr;

    int Largeur = 0;
    int Hauteur = 0;
    int spawnX = 0;                                                                                                                             // Position X du spawn du heros.
    int spawnY = 0;                                                                                                                             // Position Y du spawn du heros.
    int sortieX = -1;                                                                                                                           // Position X de la sortie.
    int sortieY = -1;                                                                                                                           // Position Y de la sortie.
    int niveau = 0;
    bool gameOver = false;                                                                                                                      // boucle pour que le jeux continue
    bool Etat = false;                                                                                                                          // pour lancer le sort
    int NB_ENNEMIS = 1;                                                                                                                         // Nombre d'ennemis pour le moment const plutart variables
    int niveauMax = 4;
    
    //void playerSpawn(const vector2& position)


};

