#include "gui/menus/menu_splash.h"

void menu_splash_setup() {
	GUI_Menu menu;
	menu.draw_func = menu_splash_draw;
	menu.update_func = menu_splash_update;
	menu.button_count = 0;

	gui_register_menu(MENU_SPLASH, &menu);
}

void menu_splash_draw() {
	lcd_clear();

	LCD_Point p;
	p.x = 12;
	p.y = 100;

	lcd_draw_text("DigiChess", COMICSANSMS(), 24, p, 0, 0xFFFF);

	delay_milli(2000);
	gui_set_menu(MENU_TEST);
}

uint8_t menu_splash_update() {
	return 0;
}
