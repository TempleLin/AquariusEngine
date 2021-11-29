#pragma once
#include <random>

class CharacterStats {
private:
	const char* name;
	int attack, agility, defense, health;
	int* forReset;
	bool dead;
	static std::random_device rd;
	static std::default_random_engine gen;
	std::uniform_int_distribution<int> dis;
public:
	CharacterStats(const char* name, int attack, int agility, int defense, int health);
	const char* getName();
	int getAttack();
	int getAgility();
	int getDefense();
	int getHealth();
	int setAttack(int value);
	int setAgility(int value);
	int setDefense(int value);
	int setHealth(int value);
	void receiveAttack(const CharacterStats& attacker);
	void resetStats();
	bool isDead();
	~CharacterStats();
};

extern CharacterStats mainCharStats;
extern CharacterStats succubusStats;