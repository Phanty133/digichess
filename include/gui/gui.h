#ifndef __GUI_H
#define __GUI_H

#include <stdint.h>
#include "memory.h"
#include "uart.h"
#include "drivers/ili9341/lcd_controls.h"

// int promotion_started = 0;
// int promotion_selected = 0;

/// @enum GUI_MenuID
/// @brief All possible menus
typedef enum {
	MENU_SPLASH,
	MENU_MODE,
	MENU_GAME,
	MENU_PROMOTION,
	MENU_VICTORY,
	MENU_TEST,
	NUM_OF_MENUS ///< Used to count the number of menus. All menus must be added before this.
} GUI_MenuID;

/// @struct GUI_MenuButton
/// @brief Defines an interactive screen region
typedef struct {
	uint16_t x; ///< Left X coordinate
	uint16_t y; ///< Top Y coordinate
	uint16_t w; ///< Width
	uint16_t h; ///< Height
	uint8_t hold; ///< If 1, will trigger every frame the button is held down. If 0, will trigger only on first tap
	uint8_t (*callback)(void); ///< Gets called when the region has been tapped. Should return 1 if the function made a screen update
} GUI_MenuButton;

/// @struct GUI_Menu
/// @brief Defines the properties and functions of an interactive menu
typedef struct {
	void (*draw_func)(void); ///< Gets called when the menu is first set
	uint8_t (*update_func)(void); ///< Gets called every frame. Should return 1 if the function made a screen update
	GUI_MenuButton buttons[8]; ///< Buttons to poll for. An arbitrary limit of 8 buttons.
	uint32_t button_count;
} GUI_Menu;

/// @struct GUI_State
/// @brief Holds the current state of the GUI
typedef struct {
	GUI_MenuID active_menu;
	GUI_Menu menus[NUM_OF_MENUS];
} GUI_State;

/// @brief Polls the touchscreen based on the menu state
void gui_update();

/// @brief Sets the menu
/// @param menu Menu to set to
void gui_set_menu(GUI_MenuID menu);

/// @brief Registers a new menu
void gui_register_menu(GUI_MenuID id, GUI_Menu* menu);

#endif