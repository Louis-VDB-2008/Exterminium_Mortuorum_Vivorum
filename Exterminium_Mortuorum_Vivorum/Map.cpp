//Louis Van den Bossche

#include "Map.h"

#include <fstream>

#include <curses.h>

// Symbole, deplacement a pied et possibilite de nager.
const TileInfo Map::TILE_INFOS[tileCount] =
{
    { '.', true, false, 5 },
    { '~', true, true, 6 },
    { 'A', false, false, 7 },
    { 'E', true, false, 4 }
};

int Map::getIndex(int x, int y) const
{
    return y * width + x;
}

bool Map::isInside(int x, int y) const
{
    return x >= 0 && x < getWidth() && y >= 0 && y < getHeight();
}

TileType Map::getTerrain(int x, int y) const
{
    // Verifier isInside avant cet appel si la position est incertaine.
    return map[getIndex(x, y)];
}

const TileInfo& Map::getTileInfo(int x, int y) const
{
    return TILE_INFOS[getTerrain(x, y)];
}

bool Map::readLines(const std::string& fileName, std::vector<std::string>& lines) const
{
    std::ifstream file(fileName);
    if (!file.is_open()) // vérifie que le fichier est ouvert
    {
        return false;
    }
    std::string line = "";
    while (std::getline(file, line))
    {
        if (!line.empty() && line.back() == '\r') // eface les retour a la ligne 
        {
            line.pop_back();
        }
        if (!line.empty()) // verifie que ce n'est pas vide
        {
            lines.push_back(line);
        }
    }
    return !lines.empty() && !lines[0].empty();
}

bool Map::readSpecialSymbol(char symbol, int x, int y)
{
    if (symbol == 'S')
    {
        playerSpawn = { x, y };
        ++playerCount;
        map.push_back(ground);
    }
    else if (symbol == 'Z')
    {
        enemySpawns.push_back({ x, y });
        map.push_back(ground);
    }
    else if (symbol == 'E')
    {
        exitPosition = { x, y };
        ++exitCount;
        map.push_back(exitTile);
    }
    else
    {
        return false;
    }
    return true;
}

bool Map::readSymbol(char symbol, int x, int y)
{
    if (symbol == '.')
    {
        map.push_back(ground);
    }
    else if (symbol == '~')
    {
        map.push_back(river);
    }
    else if (symbol == 'A')
    {
        map.push_back(mountain);
    }
    else
    {
        return readSpecialSymbol(symbol, x, y);
    }
    return true;
}

bool Map::readRow(const std::string& line, int y) //verifier que toute les ligne font la meme taille
{
    if (static_cast<int>(line.size()) != width)
    {
        return false;
    }
    for (int x = 0; x < width; ++x)
    {
        if (!readSymbol(line[x], x, y))
        {
            return false;
        }
    }
    return true;
}

bool Map::loadMap(const std::string& fileName)
{
    std::vector<std::string> lines;
    if (!readLines(fileName, lines))
    {
        return false;
    }
    width = static_cast<int>(lines[0].size());
    height = static_cast<int>(lines.size());
    playerCount = 0;
    exitCount = 0;
    map.clear();
    enemySpawns.clear();
    for (int y = 0; y < height; ++y)
    {
        if (!readRow(lines[y], y))
        {
            return false;
        }
    }
    return playerCount == 1 && exitCount == 1;
}



void Map::drawMap() const
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            const char symbol = getTileInfo(x, y).symbol;
            int color = getTileInfo(x, y).color;
            attron(COLOR_PAIR(color));
            mvaddch(y, x, symbol);
            attroff(COLOR_PAIR(color));
        }
    }
}

int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}

Vector2 Map::getPlayerSpawn()
{
    return playerSpawn;
}

Vector2 Map::getExit() const
{
    return exitPosition;
}

const std::vector<Vector2>& Map::getEnemySpawns() const
{
    return enemySpawns;
}
