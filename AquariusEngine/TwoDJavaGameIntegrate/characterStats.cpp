#include "headers/charactersStats.hpp"
#include <iostream>

std::random_device CharacterStats::rd;
std::default_random_engine CharacterStats::gen{ std::default_random_engine(rd()) };

CharacterStats::CharacterStats(const char* name, int attack, int agility, int defense, int health) :
	name(name), attack(attack), agility(agility), defense(defense), health(health), dead(false), dis(1, health),
	forReset(new int[] {attack, agility, defense, health}) {
}
const char* CharacterStats::getName() {
	return this->name;
}
int CharacterStats::getAttack() {
	return this->attack;
}
int CharacterStats::getAgility() {
	return this->agility;
}
int CharacterStats::getDefense() {
	return this->defense;
}
int CharacterStats::getHealth() {
	return this->health;
}

int CharacterStats::setAttack(int value) {
	this->attack = value;
}

int CharacterStats::setAgility(int value)
{
	this->agility = value;
}

int CharacterStats::setDefense(int value)
{
	this->defense = value;
}

int CharacterStats::setHealth(int value)
{
	this->health = value;
}

void CharacterStats::receiveAttack(const CharacterStats& attacker)
{
	// Health is higher than 0
	if (health > 0) {
		int randomDodgeInRange{ dis(gen) }; // If random generated value is within agility range, then dodge the attack.
		if (randomDodgeInRange <= agility) {
			std::cout << "Dodged attack\n";
		} else {
			int prevHealth = health;
			// If this character's defense is higher than attackers's attack damage, damage will be 0.
			health -= (attacker.attack - ((defense > attacker.attack) ? attacker.attack : defense));
			std::cout << name << " received " << prevHealth - health << " damage\n";
		}
	} else if (!dead){
		std::cout << name << " is dead.\n";
		dead = true;
	}
}

void CharacterStats::resetStats() {
	attack = forReset[0];
	agility = forReset[1];
	defense = forReset[2];
	health = forReset[3];
	dead = false;
}

bool CharacterStats::isDead() {
	return this->dead;
}

CharacterStats::~CharacterStats() {
	delete[] forReset;
}

CharacterStats mainCharStats{ "MainCharacter", 5, 1, 5, 100 };
CharacterStats succubusStats{ "Succubus", 10, 3, 4, 500 };