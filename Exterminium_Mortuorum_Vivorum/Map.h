//Louis Van den Bossche

#pragma once

#include <string>
#include <vector>

#include "Vector2.h"

// Types de terrains presents dans les fichiers de niveaux.
enum TileType
{
    ground = 0,
    river = 1,
    mountain = 2,
    exitTile = 3,
    tileCount = 4
};

// Informations communes a chaque type de terrain.
struct TileInfo
{
    char symbol = '.';
    bool isWalkable = false;
    bool isSwimmable = false;
    int color = 5;
};

class Map
{
public:
    bool loadMap(const std::string& fileName);
    int getIndex(int x, int y) const;
    bool isInside(int x, int y) const;
    TileType getTerrain(int x, int y) const;
    const TileInfo& getTileInfo(int x, int y) const;
    void drawMap() const;
    int getWidth() const;
    int getHeight() const;
    Vector2 getPlayerSpawn() const;
    Vector2 getExit() const;
    const std::vector<Vector2>& getEnemySpawns() const;

private:
    // Separe les etapes pour garder des fonctions courtes.
    bool readLines(const std::string& fileName,
        std::vector<std::string>& lines) const;
    bool readRow(const std::string& line, int y);
    bool readSymbol(char symbol, int x, int y);
    bool readSpecialSymbol(char symbol, int x, int y);

    int width = 0;
    int height = 0;
    int playerCount = 0;
    int exitCount = 0;
    std::vector<TileType> map;
    Vector2 playerSpawn;
    Vector2 exitPosition;
    std::vector<Vector2> enemySpawns;
    static const TileInfo TILE_INFOS[tileCount];
};
