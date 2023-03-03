#include "gui/menus/menu_mode.h"

static uint8_t on_player_click() {
	set_AI_mode(0);
	menu_game_setup();
	gui_set_menu(MENU_GAME);

	uart_write("AI mode: ");
	uart_write_num(get_AI_mode(), 1);
	
	return 1;
}

static uint8_t on_stockfish_click() {
	set_AI_mode(1);
	menu_game_setup();
	gui_set_menu(MENU_GAME);

	uart_write("AI mode: ");
	uart_write_num(get_AI_mode(), 1);

	return 1;
}

void menu_mode_setup() {
	GUI_Menu menu;
	menu.draw_func = menu_mode_draw;
	menu.update_func = menu_mode_update;
	menu.button_count = 2;

	GUI_MenuButton btn_player;
	btn_player.x = 20;
	btn_player.y = 110;
	btn_player.w = 200;
	btn_player.h = 50;
	btn_player.callback = on_player_click;
	btn_player.hold = 0;

	GUI_MenuButton btn_stockfish;
	btn_stockfish.x = 20;
	btn_stockfish.y = 200;
	btn_stockfish.w = 200;
	btn_stockfish.h = 50;
	btn_stockfish.callback = on_stockfish_click;
	btn_stockfish.hold = 0;

	menu.buttons[0] = btn_player;
	menu.buttons[1] = btn_stockfish;

	gui_register_menu(MENU_MODE, &menu);
}

void menu_mode_draw() {
	lcd_clear();

	LCD_Point p0, p1;

	// Draw rectangles

	p0.x = 0;
	p0.y = 0;
	p1.x = LCD_WIDTH;
	p1.y = 45;

	lcd_draw_rect_filled(p0, p1, MENU_COLOR_GREEN);

	p0.x = 20;
	p0.y = 110;
	p1.x = 220;
	p1.y = 160;

	lcd_draw_rect_filled(p0, p1, MENU_COLOR_RED);

	p0.x = 20;
	p0.y = 200;
	p1.x = 220;
	p1.y = 250;

	lcd_draw_rect_filled(p0, p1, MENU_COLOR_BLUE);

	// Draw the text

	p0.x = 12;
	p0.y = 10;

	lcd_draw_text("Mode selection", COMICSANSMS(), 32, p0, 0xFFFF, MENU_COLOR_GREEN);

	p0.x = 80;
	p0.y = 120;

	lcd_draw_text("Player", COMICSANSMS(), 32, p0, 0xFFFF, MENU_COLOR_RED);

	p0.x = 50;
	p0.y = 212;

	lcd_draw_text("Stockfish", COMICSANSMS(), 32, p0, 0xFFFF, MENU_COLOR_BLUE);
}

uint8_t menu_mode_update() {
	return 0;
}
