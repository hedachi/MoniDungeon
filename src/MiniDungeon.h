#pragma once

// Game tuning 
#define STAT_POINTS_PER_LEVEL 2
#define XP_FOR_NEXT_LEVEL 5 * level

// Feature tuning
#define PAD_WITH_SPACES 1
#define DISABLE_MENU_BMPS 0

// Publish 0 turns on the test menu
#define PUBLISH 1
	
// Logging
#define DEBUG_LOGGING 0 // DEBUG_LOGGING 1 turns on DEBUG_LOG. DEBUG_LOGGING 2 turns on DEBUG_VERBOSE_LOG also.
#define ERROR_LOGGING 1 // ERROR_LOG should be used for actual incorrect operation.
#define WARNING_LOGGING 1 // WARNING_LOG should be used strange edge cases that are not expected
#define INFO_LOGGING 1 // INFO_LOG should be used to log game flow.

// Features to turn off to make space
#define ALLOW_RANDOM_DUNGEON_GRAPHICS 1
#define BOUNDS_CHECKING 1
#define EVENT_CHANCE_SCALING 1

#define ALLOW_SHOP 1
#if ALLOW_SHOP
	#define ALLOW_ITEM_SHOP 1
	#define ALLOW_STAT_SHOP 1
#else
	#define ALLOW_ITEM_SHOP 0
	#define ALLOW_STAT_SHOP 0
#endif	

// Set up the test menu based on previous choices
#if PUBLISH
	#define ALLOW_TEST_MENU 0
#else
	#define ALLOW_TEST_MENU 1
#endif

// This needs to be large enough to handle the maximum size of the window stack
#define MAX_MENU_WINDOWS 4
// This determines how many text rows there are in the interface
#define MAX_MENU_ENTRIES 6
	
void ResetGame(bool isInit);
