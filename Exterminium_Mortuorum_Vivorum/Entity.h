#pragma once

class Entity
{
public:
	void DisplayStats();

	void Attack(Entity& target);

	// Geter, Setter
	int GetLife();
	int SetLife(int value);
	
	
	virtual void onCollision() = 0;
	void applyDamage(int value);
	bool isAlive();
	void move();
	virtual void onUpdate() = 0;

private:
	int x;
	int y;
	int life;
	int attack;
	//int defense;
};

