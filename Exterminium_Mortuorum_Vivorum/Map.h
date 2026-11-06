//Louis Van den Bossche

#pragma once

#include <string>
#include <vector>

#include "Vector2.h"

enum TileType // Types de terrains
{
    ground = 0,
    river = 1,
    mountain = 2,
    exitTile = 3,
    tileCount = 4
};


struct TileInfo // information des terrains
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
    Vector2 getPlayerSpawn();
    Vector2 getExit() const;
    const std::vector<Vector2>& getEnemySpawns() const; // tableau dynamique constant contenant des structure Vector2

private:
    bool readLines(const std::string& fileName, std::vector<std::string>& lines) const;
    bool readRow(const std::string& line, int y); // vérifie que les lignes font la même taille
    bool readSymbol(char symbol, int x, int y);
    bool readSpecialSymbol(char symbol, int x, int y);

    int width = 0;
    int height = 0;
    int playerCount = 0; // vérifie que player est bien présent
    int exitCount = 0; // vérifie que la sortie est bien présent
    std::vector<TileType> map;
    Vector2 playerSpawn;
    Vector2 exitPosition;
    std::vector<Vector2> enemySpawns;
    static const TileInfo TILE_INFOS[tileCount];
};
