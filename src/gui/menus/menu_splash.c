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
	p.x = 30;
	p.y = 70;

	lcd_draw_image(p, LOGO());

	delay_milli(3000);
	gui_set_menu(MENU_MODE);
}

uint8_t menu_splash_update() {
	return 0;
}
