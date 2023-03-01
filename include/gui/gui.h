#ifndef __GUI_H
#define __GUI_H

#include <stdint.h>

typedef enum {
	SPLASH,
	NUM_OF_MENUS // Used to count the number of menus. All menus must be added before this.
} MenuID;

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
	void (*callback)(void);
} MenuButton;

typedef struct {
	MenuButton buttons[8]; ///< Buttons to poll for. An arbitrary limit of 8 buttons.
} Menu;

typedef struct {
	MenuID active_menu;
	Menu menus[NUM_OF_MENUS];
} GUIState;

/// @brief Polls the touchscreen based on the menu state
/// @return 1 if a press on a button is detected, 0 otherwise
uint8_t poll_touchscreen(GUIState* state);

/// @brief Sets the menu
/// @param state Current GUI state
/// @param menu Menu to set to
void set_menu(GUIState* state, MenuID menu);

#endif