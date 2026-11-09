#include "pch.h"
#include <gtest/gtest.h>
#include "HeadlessZombie.h"
#include "Mage.h"
#include "Warrior.h"
#include "WarriorMage.h"
#include "Zombie.h"
#include "ZombieSwimmer.h"

TEST(ClassTest, WarriorStartsWithThreeHp)
{
    Warrior warrior;
    EXPECT_EQ(warrior.getHp(), 3);
}

TEST(ClassTest, MageStartsWithOneHp)
{
    Mage mage;
    EXPECT_EQ(mage.getHp(), 1);
}

TEST(ClassTest, WarriorMageCombinesBothClasses)
{
    WarriorMage player;
    EXPECT_EQ(player.getHp(), 3);
    EXPECT_STREQ(player.getClassName(), "WarriorMage");
}

TEST(ClassTest, WarriorCollisionDefeatsEnemyAndCostsHp)
{
    Warrior warrior;
    Zombie enemy;
    warrior.onCollision(&enemy);
    EXPECT_FALSE(enemy.isAlive());
    EXPECT_EQ(warrior.getHp(), 2);
}

TEST(ClassTest, MageSpellDefeatsNearbyEnemy)
{
    Mage mage;
    mage.setPlayerPosition({ 1, 1 });
    Zombie enemy({ 2, 2 });
    mage.castSpell();
    EXPECT_FALSE(enemy.isAlive());
}

TEST(ClassTest, OnlySwimmerCanCrossRiver)
{
    Map map;
    ASSERT_TRUE(map.loadMap("map/Niveau1.txt"));
    Zombie zombie;
    ZombieSwimmer swimmer;
    EXPECT_FALSE(zombie.canMove(map, { 5, 1 }));
    EXPECT_TRUE(swimmer.canMove(map, { 5, 1 }));
}
