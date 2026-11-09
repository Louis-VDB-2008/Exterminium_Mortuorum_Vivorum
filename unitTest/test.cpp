#include "pch.h"
#include <gtest/gtest.h>
#include "Map.h"
#include "Game.h"

#include <filesystem>
#include <fstream>
#include <string>

namespace // pour que MapTest ne soit disponible que dans test
{
    class MapTest : public ::testing::Test //::testing::Test =  classe fournie par Google Test.
    {
    protected:
        Map map;
        std::filesystem::path filePath;

        void SetUp() override // avant chaque test
        {
            static int nextId = 0;
            filePath = std::filesystem::temp_directory_path() / ("test_map_" + std::to_string(++nextId) + ".txt");
            //Récupère le chemin du dossier temporaire de Windows : test_map_1.txt ; test_map2.txt, etc  
        }

        void TearDown() override // aprés chaque test
        {
            std::error_code error; // empéche les crash en cas d'erreur
            std::filesystem::remove(filePath, error); // suprime le fichier 
        }

        bool loadText(const std::string& content) // créer une carte et vérifie quelle s'afiche
        {
            std::ofstream file(filePath, std::ios::binary);
            if (!file)
            {
                return false;
            }
            file << content;
            file.close();
            return map.loadMap(filePath.string());
        }
    };
}

TEST_F(MapTest, LoadValidMap)
{
    ASSERT_TRUE(loadText("S.Z\n.~A\n..E\n"));
    EXPECT_EQ(map.getWidth(), 3);
    EXPECT_EQ(map.getHeight(), 3);
    //verifie que la taille de la map est respecter et qu'aucun des caractére utiliser dans le jeux n'est suprimer
}

TEST_F(MapTest, ReadAllTerrainTypes)
{
    ASSERT_TRUE(loadText("S.~AE\n"));
    EXPECT_EQ(map.getTerrain(0, 0), ground);
    EXPECT_EQ(map.getTerrain(1, 0), ground);
    EXPECT_EQ(map.getTerrain(2, 0), river);
    EXPECT_EQ(map.getTerrain(3, 0), mountain);
    EXPECT_EQ(map.getTerrain(4, 0), exitTile);
    // vérifie que getTerrain reconait les terrains, premiere coordonées x, deuxiéme y
}

TEST_F(MapTest, TerrainProperties)
{
    ASSERT_TRUE(loadText("S.~AE\n"));
    EXPECT_TRUE(map.getTileInfo(1, 0).isWalkable);
    EXPECT_FALSE(map.getTileInfo(1, 0).isSwimmable);
    EXPECT_TRUE(map.getTileInfo(2, 0).isWalkable);
    EXPECT_TRUE(map.getTileInfo(2, 0).isSwimmable);
    EXPECT_FALSE(map.getTileInfo(3, 0).isWalkable);
    EXPECT_EQ(map.getTileInfo(4, 0).symbol, 'E');
    // vérifie que les propriétés des terrains sont respecter
}


TEST_F(MapTest, SpawnAndExitPositions)
{
    ASSERT_TRUE(loadText("...E\n.S..\n"));
    EXPECT_EQ(map.getPlayerSpawn().x, 1);
    EXPECT_EQ(map.getPlayerSpawn().y, 1);
    EXPECT_EQ(map.getExit().x, 3);
    EXPECT_EQ(map.getExit().y, 0);
    // vérifie que l'on recoit les bonnes coordonées pour le spawn et la sortie
}

TEST_F(MapTest, EnemyPositions)
{
    ASSERT_TRUE(loadText("SZZ\nZ.E\n"));
    const auto& enemies = map.getEnemySpawns();
    ASSERT_EQ(enemies.size(), 3u);
    EXPECT_EQ(enemies[0].x, 1);
    EXPECT_EQ(enemies[0].y, 0);
    EXPECT_EQ(enemies[1].x, 2);
    EXPECT_EQ(enemies[2].x, 0);
    EXPECT_EQ(enemies[2].y, 1);
    EXPECT_EQ(map.getTerrain(1, 0), ground);
    // vérifie la position des ennemies
}

TEST_F(MapTest, IndexCalculation)
{
    ASSERT_TRUE(loadText("S...\n...E\n"));
    EXPECT_EQ(map.getIndex(0, 0), 0);
    EXPECT_EQ(map.getIndex(3, 0), 3);
    EXPECT_EQ(map.getIndex(0, 1), 4);
    EXPECT_EQ(map.getIndex(2, 1), 6);
    // verifie que la fonction getIndex transforme bien des coordonnées 2D EN 1D
}

TEST_F(MapTest, InsideMap)
{
    ASSERT_TRUE(loadText("S..\n..E\n"));
    EXPECT_TRUE(map.isInside(0, 0));
    EXPECT_TRUE(map.isInside(2, 1));
    EXPECT_FALSE(map.isInside(-1, 0));
    EXPECT_FALSE(map.isInside(0, -1));
    EXPECT_FALSE(map.isInside(3, 0));
    EXPECT_FALSE(map.isInside(0, 2));
    // vérifie que le jeux sache bien ce qui est dedans ou dehors de la map
}

TEST_F(MapTest, RejectMissingFile)
{
    EXPECT_FALSE(map.loadMap(filePath.string()));
    // refuse les cartes incorrectes.
}

TEST_F(MapTest, RejectEmptyFile)
{
    EXPECT_FALSE(loadText(""));
    // refuse les cartes incorrectes.
}

TEST_F(MapTest, RejectDifferentRowWidths)
{
    EXPECT_FALSE(loadText("S..\n.E\n"));
    // refuse les cartes incorrectes.
}

TEST_F(MapTest, RejectUnknownSymbol)
{
    EXPECT_FALSE(loadText("S?E\n"));
    // refuse les cartes incorrectes.
}

TEST_F(MapTest, RejectMissingPlayer)
{
    EXPECT_FALSE(loadText("..E\n"));
    // refuse les cartes incorrectes.
}

TEST_F(MapTest, RejectMissingExit)
{
    EXPECT_FALSE(loadText("S..\n"));
    // refuse les cartes incorrectes.
}

TEST_F(MapTest, RejectMultiplePlayers)
{
    EXPECT_FALSE(loadText("SSE\n"));
    // refuse les cartes incorrectes.
}

TEST_F(MapTest, RejectMultipleExits)
{
    EXPECT_FALSE(loadText("SEE\n"));
}

TEST_F(MapTest, IgnoreEmptyLines)
{
    ASSERT_TRUE(loadText("\nS.E\n\n"));
    EXPECT_EQ(map.getHeight(), 1);
    // vérifie que le code ignore les lignes vides
}

TEST_F(MapTest, AcceptWindowsLineEndings)
{
    ASSERT_TRUE(loadText("S..\r\n..E\r\n"));
    EXPECT_EQ(map.getHeight(), 2);
    // vérifie les fin de lignes
}

TEST_F(MapTest, ReloadResetsMapAndEnemies)
{
    ASSERT_TRUE(loadText("SZE\n"));
    ASSERT_EQ(map.getEnemySpawns().size(), 1u);
    ASSERT_TRUE(loadText("S.\n.E\n"));
    EXPECT_TRUE(map.getEnemySpawns().empty());
    EXPECT_EQ(map.getWidth(), 2);
    EXPECT_EQ(map.getHeight(), 2);
    // vérifie que l'on peut charger des nouvelles cartes
}

TEST(GameTest, SingletonReturnsSameInstance)
{
    EXPECT_EQ(Game::getInstance(), Game::getInstance());
    // verifie que le singleton n'as qu'une instance
}

TEST(GameTest, RejectOutOfRangeLevels)
{
    Game* game = Game::getInstance();
    EXPECT_FALSE(game->loadLevel(0));
    EXPECT_FALSE(game->loadLevel(-1));
    EXPECT_FALSE(game->loadLevel(5));
    // vérifie que l'on ne peut pas lancer un niveau qui n'existe pas
}
