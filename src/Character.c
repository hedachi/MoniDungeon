#include "pebble.h"

#include "Adventure.h"
#include "Battle.h"
#include "Character.h"
#include "Items.h"
#include "Logging.h"
#include "Menu.h"
#include "UILayers.h"
#include "Utils.h"

CharacterData characterData;

void AddStatPointToSpend(void)
{
	++characterData.stats.statPoints;
}

void UpdateCharacterHealth(void)
{
	UpdateHealthText(characterData.stats.currentHealth, characterData.stats.maxHealth);
}

void UpdateCharacterLevel(void)
{
	UpdateLevelLayerText(characterData.level);
}

const char *UpdateLevelText(void)
{
	static char levelText[] = "00"; // Needs to be static because it's used by the system later.
	IntToString(levelText, 2, characterData.level);
	return levelText;
}

const char *UpdateXPText(void)
{
	static char xpText[] = "0000"; // Needs to be static because it's used by the system later.
	IntToString(xpText, 4, characterData.xp);
	return xpText;
}

const char *UpdateNextXPText(void)
{
	static char nextXPText[] = "0000"; // Needs to be static because it's used by the system later.
	IntToString(nextXPText, 4, characterData.xpForNextLevel);
	return nextXPText;
}

const char *UpdateGoldText(void)
{
	static char goldText[] = "00000"; // Needs to be static because it's used by the system later.
	IntToString(goldText, 5, characterData.gold);
	return goldText;
}

const char *UpdateEscapeText(void)
{
	static char escapeText[] = "000"; // Needs to be static because it's used by the system later.
	IntToString(escapeText, 3, characterData.escapes);
	return escapeText;
}

const char *UpdateDeadText(void)
{
	static char deadText[] = "000"; // Needs to be static because it's used by the system later.
	IntToString(deadText, 3, characterData.deadTimes);
	return deadText;
}

void IncrementEscapes(void)
{
	++characterData.escapes;
}

int ComputePlayerHealth(int level)
{
	return 10 + ((level-1)*(level)/2) + ((level-1)*(level)*(level+1)/(6*32));
}

int ComputeXPForNextLevel(int level)
{
	return XP_FOR_NEXT_LEVEL;
}

void InitializeCharacter(void)
{
	INFO_LOG("Initializing character.");
	characterData.xp = 0;
	characterData.level = 1;
	characterData.gold = 0;
	characterData.escapes = 0;
	characterData.deadTimes = 0;
	characterData.xpForNextLevel = ComputeXPForNextLevel(1);
	characterData.stats.maxHealth = ComputePlayerHealth(1);
	characterData.stats.currentHealth = characterData.stats.maxHealth;
	characterData.stats.strength = 1;
	characterData.stats.magic = 1;
	characterData.stats.defense = 1;
	characterData.stats.magicDefense = 1;
	characterData.stats.stamina = 10;
	characterData.stats.statPoints = 0;

	UpdateCharacterLevel();
	UpdateCharacterHealth();
}

// Returns true on levelup
bool GrantExperience(int xp)
{
	characterData.xp += xp;
	if(characterData.xp >= characterData.xpForNextLevel)
	{
		return true;
	}
	return false;
}

void GrantGold(int gold)
{
	characterData.gold += gold;
	if(characterData.gold > 9999)
		characterData.gold = 9999;
}

bool DealPlayerDamage(int damage)
{
	int returnValue = false;
	characterData.stats.currentHealth = characterData.stats.currentHealth - damage;
	if(characterData.stats.currentHealth <= 0)
	{
		characterData.stats.currentHealth = 0;
		returnValue = true;
	}
	UpdateCharacterHealth();
	return returnValue;
}

CharacterData *GetCharacter(void)
{
	return &characterData;
}

void HealPlayerByPercent(int percent)
{
	characterData.stats.currentHealth += (characterData.stats.maxHealth * percent) / 100;
	if(characterData.stats.currentHealth > characterData.stats.maxHealth)
		characterData.stats.currentHealth = characterData.stats.maxHealth;

	UpdateCharacterHealth();
}

bool PlayerIsInjured(void)
{
	return characterData.stats.currentHealth < characterData.stats.maxHealth;
}

void EndMenuDisappear(Window *window)
{
	ResetGame(false);
}

void EndMenuAppear(Window *window);

MenuDefinition endMenuDef = 
{
	.menuEntries = 
	{
		{"Ok", "Restart game", PopMenu}
	},
	.disappear = EndMenuDisappear,
	.appear = EndMenuAppear,
	.mainImageId = -1
};

void EndMenuAppear(Window *window)
{
	MenuAppear(window);
	if(characterData.stats.currentHealth <= 0) {
		ShowMainWindowRow(0, "You lose", "");
		characterData.deadTimes += 1;
	} else {
		ShowMainWindowRow(0, "You win", "");
	}
	ShowMainWindowRow(1, "Floor", UpdateFloorText());
	ShowMainWindowRow(2, "Level", UpdateLevelText());
	ShowMainWindowRow(3, "Gold", UpdateGoldText());
	ShowMainWindowRow(4, "Dead", UpdateDeadText());
}

void ShowEndWindow(void)
{
	PushNewMenu(&endMenuDef);
}

const char  *UpdateStatPointText(void)
{
	static char statText[] = "00"; // Needs to be static because it's used by the system later.

	IntToString(statText, 2, characterData.stats.statPoints);
	return statText;
}

const char  *UpdateStrengthText(void)
{
	static char strengthText[] = "00"; // Needs to be static because it's used by the system later.

	IntToString(strengthText, 2, characterData.stats.strength);
	return strengthText;
}

const char  *UpdateDefenseText(void)
{
	static char defenseText[] = "00"; // Needs to be static because it's used by the system later.

	IntToString(defenseText, 2, characterData.stats.defense);
	return defenseText;
}

const char  *UpdateMagicText(void)
{
	static char magicText[] = "00"; // Needs to be static because it's used by the system later.

	IntToString(magicText, 2, characterData.stats.magic);
	return magicText;
}

const char  *UpdateMagicDefenseText(void)
{
	static char magicDefenseText[] = "00"; // Needs to be static because it's used by the system later.

	IntToString(magicDefenseText, 2, characterData.stats.magicDefense);
	return magicDefenseText;
}

const char  *UpdateStaminaText(void)
{
	static char staminaText[] = "00"; // Needs to be static because it's used by the system later.

	IntToString(staminaText, 2, characterData.stats.stamina);
	return staminaText;
}

void DrawStatWindow(void)
{
	ShowMainWindowRow(0, "Stat Points", UpdateStatPointText());	
	ShowMainWindowRow(1, "Strength", UpdateStrengthText());
	ShowMainWindowRow(2, "Defense", UpdateDefenseText());
	ShowMainWindowRow(3, "Magic", UpdateMagicText());
	ShowMainWindowRow(4, "MagicDef", UpdateMagicDefenseText());
	ShowMainWindowRow(5, "Stamina", UpdateStaminaText());
}

void IncrementStat(int *stat)
{
	if(characterData.stats.statPoints)
	{
		++(*stat);
		--characterData.stats.statPoints;
		DrawStatWindow();
	}
}

void IncrementStrength(void)
{
	IncrementStat(&characterData.stats.strength);
}

void IncrementDefense(void)
{
	IncrementStat(&characterData.stats.defense);
}

void IncrementMagic(void)
{
	IncrementStat(&characterData.stats.magic);
}

void IncrementMagicDefense(void)
{
	IncrementStat(&characterData.stats.magicDefense);
}

void IncrementStamina(void)
{
	//FIXME not implementd
}

void HealStamina(void)
{
	if (characterData.stats.stamina < 10) {
		characterData.stats.stamina += 1;
	}
}

void LevelUp(void)
{
	INFO_LOG("Level up.");
	characterData.stats.statPoints += STAT_POINTS_PER_LEVEL;
	++characterData.level;
	characterData.xpForNextLevel += ComputeXPForNextLevel(characterData.level);
	characterData.stats.maxHealth = ComputePlayerHealth(characterData.level);
	if(characterData.stats.maxHealth > 9999)
		characterData.stats.maxHealth = 9999;
	characterData.stats.currentHealth = characterData.stats.maxHealth;
	UpdateCharacterLevel();
	UpdateCharacterHealth();
	ShowStatMenu();
}

void StatMenuAppear(Window *window);

MenuDefinition statMenuDef = 
{
	.menuEntries = 
	{
		{"Quit", "Return to main menu", PopMenu},
		{"Increase", "Increase strength", IncrementStrength},
		{"Increase", "Increase defense", IncrementDefense},
		{"Increase", "Increase magic", IncrementMagic},
		{"Increase", "Increase magic defense", IncrementMagicDefense},
		{"-", "Added per 1 minutes", IncrementStamina},
	},
	.appear = StatMenuAppear,
	.mainImageId = -1
};

void StatMenuAppear(Window *window)
{
	MenuAppear(window);
	DrawStatWindow();
}

void ShowStatMenu(void)
{
	PushNewMenu(&statMenuDef);
}

void ProgressMenuAppear(Window *window);

MenuDefinition progressMenuDef = 
{
	.menuEntries = 
	{
		{"Quit", "Return to main menu", PopMenu},
	},
	.appear = ProgressMenuAppear,
	.mainImageId = -1
};

void ProgressMenuAppear(Window *window)
{
	MenuAppear(window);
	ShowMainWindowRow(0, "Progress", "");	
	ShowMainWindowRow(1, "Level", UpdateLevelText());
	ShowMainWindowRow(2, "XP", UpdateXPText());
	ShowMainWindowRow(3, "Next XP", UpdateNextXPText());
	ShowMainWindowRow(4, "Gold", UpdateGoldText());
	//ShowMainWindowRow(5, "Escapes", UpdateEscapeText());
	ShowMainWindowRow(5, "Dead", UpdateDeadText());
}

void ShowProgressMenu(void)
{
	PushNewMenu(&progressMenuDef);
}

bool SpendStamina(void) {
	if (characterData.stats.stamina > 0) {
		characterData.stats.stamina--;
		return true;
	} else {
		return false;
	}
}

int GetStamina(void) {
	return characterData.stats.stamina;
}
