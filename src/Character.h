#pragma once

// TODO: turn the list of stats into an array for more code reuse
typedef struct
{
	int maxHealth;
	int currentHealth;
	int strength;
	int magic;
	int defense;
	int magicDefense;
	int stamina;
	int statPoints;
} Stats;

typedef struct 
{
	int xp;
	int xpForNextLevel;
	int level;
	int gold;
	int escapes;
    int deadTimes;
	Stats stats;
} CharacterData;

int ComputePlayerHealth(int level);
void UpdateCharacterHealth(void);
void UpdateCharacterLevel(void);
const char *UpdateGoldText(void);
void AddStatPointToSpend(void);
void IncrementEscapes(void);

void InitializeCharacter(void);

bool DealPlayerDamage(int damage);
CharacterData *GetCharacter(void);

void HealPlayerByPercent(int percent);
bool PlayerIsInjured(void);

bool GrantExperience(int exp);
void GrantGold(int gold);

void ShowStatMenu(void);
void ShowProgressMenu(void);

void LevelUp(void);
void ShowEndWindow(void);
bool SpendStamina(void);
void HealStamina();
int GetStamina();
