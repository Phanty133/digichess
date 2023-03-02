#include "gui/gui_register_menus.h"

void gui_register_all_menus() {
	menu_splash_setup();
	menu_test_setup();
	menu_promotion_setup();
	menu_mode_setup();
	menu_game_setup();
	menu_victory_setup();
}