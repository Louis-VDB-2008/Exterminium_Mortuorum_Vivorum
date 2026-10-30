#pragma once
class Game
{
private:
	static Game* instance;
public:
	static Game* GetInstance();
	void run();
};

