#include "gui/menus/menu_victory.h"

static uint8_t player_victory = 0; // TODO: Integrate with game

static void on_play_again_click() {
	software_reset();
}

void menu_victory_setup() {
	GUI_Menu menu;
	menu.draw_func = menu_victory_draw;
	menu.update_func = menu_victory_update;
	menu.button_count = 1;

	GUI_MenuButton btn;
	btn.x = 0;
	btn.y = 260;
	btn.w = LCD_WIDTH;
	btn.h = 60;
	btn.callback = on_play_again_click;
	btn.hold = 0;

	menu.buttons[0] = btn;

	gui_register_menu(MENU_VICTORY, &menu);
}

void menu_victory_draw() {
	lcd_clear();

	LCD_Point p0, p1;

	p0.x = 0;
	p0.y = 0;
	p1.x = LCD_WIDTH;
	p1.y = 260;

	uint32_t player_bg_col = player_victory ? MENU_COLOR_BLUE : MENU_COLOR_RED;

	lcd_draw_rect_filled(p0, p1, player_bg_col);

	p0.x = 0;
	p0.y = 260;
	p1.x = LCD_WIDTH;
	p1.y = 320;

	lcd_draw_rect_filled(p0, p1, MENU_COLOR_GREEN);

	p0.x = 25;
	p0.y = 70;

	lcd_draw_text(
		player_victory ? "Blue wins!" : "Red wins!",
		COMICSANSMS(),
		48,
		p0,
		0xFFFF,
		player_bg_col
	);

	p0.x = 30;
	p0.y = 270;

	lcd_draw_text("Play again", COMICSANSMS(), 42, p0, 0xFFFF, MENU_COLOR_GREEN);
}

uint8_t menu_victory_update() {
	return 0;
}
