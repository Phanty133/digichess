#include "gui/menus/menu_game.h"
#include "gui/menus/menu_splash.h"

static uint8_t active_player = 1;
static uint8_t promotion_available = 0; // TODO: Integrate with game
static uint8_t redraw_player = 0;
static uint8_t redraw_promotion = 0;

static uint8_t on_promote_click() {
	if (!promotion_available) return 0;

	gui_set_menu(MENU_PROMOTION);

	return 1;
}

void menu_game_setup() {
	GUI_Menu menu;
	menu.draw_func = menu_game_draw;
	menu.update_func = menu_game_update;
	menu.button_count = 1;

	GUI_MenuButton btn_promote;
	btn_promote.x = 20;
	btn_promote.y = 200;
	btn_promote.w = 200;
	btn_promote.h = 40;
	btn_promote.callback = on_promote_click;
	btn_promote.hold = 0;

	menu.buttons[0] = btn_promote;

	gui_register_menu(MENU_GAME, &menu);
}

void menu_game_draw() {
	lcd_clear();

	LCD_Point p0, p1;
	uint16_t prom_fg_color = promotion_available ? 0xFFFF : 0xAD55;
	uint16_t prom_bg_color = promotion_available ? MENU_COLOR_GREEN : MENU_COLOR_GREEN_DARK;
	uint16_t plyr_color = active_player ? MENU_COLOR_BLUE : MENU_COLOR_RED;

	p0.x = 0;
	p0.y = 0;
	p1.x = LCD_WIDTH;
	p1.y = 160;

	lcd_draw_rect_filled(p0, p1, plyr_color);

	p0.x = 20;
	p0.y = 200;
	p1.x = 220;
	p1.y = 240;

	lcd_draw_rect_filled(p0, p1, prom_bg_color);

	p0.x = 0;
	p0.y = 275;
	p1.x = 120;
	p1.y = 320;

	lcd_draw_rect_filled(p0, p1, MENU_COLOR_RED);

	p0.x = 120;
	p0.y = 275;
	p1.x = 240;
	p1.y = 320;

	lcd_draw_rect_filled(p0, p1, MENU_COLOR_BLUE);

	p0.x = 20;
	p0.y = 60;

	lcd_draw_text(
		active_player ? "Blue's turn" : "Red's turn",
		COMICSANSMS(),
		42,
		p0,
		0xFFFF,
		plyr_color
	);

	p0.x = 60;
	p0.y = 207;

	lcd_draw_text("Promote", COMICSANSMS(), 32, p0, prom_fg_color, prom_bg_color);

	p0.x = 50;
	p0.y = 288;

	lcd_draw_text("0", COMICSANSMS(), 32, p0, 0xFFFF, MENU_COLOR_RED);

	p0.x = 175;
	p0.y = 288;

	lcd_draw_text("0", COMICSANSMS(), 32, p0, 0xFFFF, MENU_COLOR_BLUE);
}

void menu_game_change_player() {
	active_player = !active_player;
	redraw_player = 1;
}

uint8_t menu_game_update() {
	uint8_t screen_update = 0;

	if (redraw_player) {
		LCD_Point p0, p1;

		p0.x = 0;
		p0.y = 0;
		p1.x = LCD_WIDTH;
		p1.y = 160;

		uint16_t plyr_color = active_player ? MENU_COLOR_BLUE : MENU_COLOR_RED;

		lcd_draw_rect_filled(p0, p1, plyr_color);

		p0.x = 20;
		p0.y = 60;

		lcd_draw_text(
			active_player ? "Blue's turn" : "Red's turn",
			COMICSANSMS(),
			42,
			p0,
			0xFFFF,
			plyr_color
		);

		screen_update = 1;
		redraw_player = 0;
	}

	if (redraw_promotion) {
		screen_update = 1;
		redraw_promotion = 0;
	}

	return screen_update;
}
