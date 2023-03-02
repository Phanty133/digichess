#include "gui/menus/menu_promotion.h"

uint8_t on_queen_click() {
	return 0;
}

uint8_t on_knight_click() {
	return 0;
}

uint8_t on_rook_click() {
	return 0;
}

uint8_t on_bishop_click() {
	return 0;
}

uint8_t on_cancel_click() {
	gui_set_menu(MENU_GAME);
}

void menu_promotion_setup() {
	GUI_Menu menu;
	menu.draw_func = menu_promotion_draw;
	menu.update_func = menu_promotion_update;
	menu.button_count = 5;

	GUI_MenuButton queen;
	queen.x = 20;
	queen.y = 55;
	queen.w = 200;
	queen.h = 45;
	queen.callback = on_queen_click;
	queen.hold = 0;

	GUI_MenuButton rook;
	rook.x = 20;
	rook.y = 165;
	rook.w = 200;
	rook.h = 45;
	rook.callback = on_rook_click;
	rook.hold = 0;
	
	GUI_MenuButton bishop;
	bishop.x = 20;
	bishop.y = 220;
	bishop.w = 200;
	bishop.h = 45;
	bishop.callback = on_bishop_click;
	bishop.hold = 0;
	
	GUI_MenuButton knight;
	knight.x = 20;
	knight.y = 110;
	knight.w = 200;
	knight.h = 45;
	knight.callback = on_knight_click;
	knight.hold = 0;

	GUI_MenuButton cancel;
	cancel.x = 20;
	cancel.y = 275;
	cancel.w = 200;
	cancel.h = 40;
	cancel.callback = on_cancel_click;
	cancel.hold = 0;
	
	menu.buttons[0] = queen;
	menu.buttons[1] = rook;
	menu.buttons[2] = bishop;
	menu.buttons[3] = knight;
	menu.buttons[4] = cancel;

	gui_register_menu(MENU_PROMOTION, &menu);
}

void menu_promotion_draw() {
	lcd_clear();

	LCD_Point p0, p1;

	// Title bar
	p0.x = 0;
	p0.y = 0;
	p1.x = LCD_WIDTH;
	p1.y = 45;

	lcd_draw_rect_filled(p0, p1, MENU_COLOR_GREEN);

	p0.x = 20;
	p0.y = 55;
	p1.x = 220;
	p1.y = 100;

	lcd_draw_rect_filled(p0, p1, MENU_COLOR_BLUE);

	p0.x = 20;
	p0.y = 110;
	p1.x = 220;
	p1.y = 155;

	lcd_draw_rect_filled(p0, p1, MENU_COLOR_BLUE);

	p0.x = 20;
	p0.y = 165;
	p1.x = 220;
	p1.y = 210;

	lcd_draw_rect_filled(p0, p1, MENU_COLOR_BLUE);

	p0.x = 20;
	p0.y = 220;
	p1.x = 220;
	p1.y = 265;

	lcd_draw_rect_filled(p0, p1, MENU_COLOR_BLUE);

	p0.x = 20;
	p0.y = 275;
	p1.x = 220;
	p1.y = 315;

	lcd_draw_rect_filled(p0, p1, MENU_COLOR_RED);

	// Images

	p0.x = 25;
	p0.y = 55;

	lcd_draw_image(p0, QUEEN());

	p0.x = 25;
	p0.y = 110;

	lcd_draw_image(p0, KNIGHT());

	p0.x = 25;
	p0.y = 165;

	lcd_draw_image(p0, ROOK());

	p0.x = 25;
	p0.y = 220;

	lcd_draw_image(p0, BISHOP());

	// Text

	p0.x = 50;
	p0.y = 10;

	lcd_draw_text("Promotion", COMICSANSMS(), 32, p0, 0xFFFF, MENU_COLOR_GREEN);

	p0.x = 80;
	p0.y = 65;

	lcd_draw_text("Queen", COMICSANSMS(), 32, p0, 0xFFFF, MENU_COLOR_BLUE);
	
	p0.x = 80;
	p0.y = 120;

	lcd_draw_text("Knight", COMICSANSMS(), 32, p0, 0xFFFF, MENU_COLOR_BLUE);

	p0.x = 80;
	p0.y = 175;

	lcd_draw_text("Rook", COMICSANSMS(), 32, p0, 0xFFFF, MENU_COLOR_BLUE);

	p0.x = 80;
	p0.y = 230;

	lcd_draw_text("Bishop", COMICSANSMS(), 32, p0, 0xFFFF, MENU_COLOR_BLUE);

	p0.x = 80;
	p0.y = 280;

	lcd_draw_text("Cancel", COMICSANSMS(), 32, p0, 0xFFFF, MENU_COLOR_RED);
}

uint8_t menu_promotion_update() {
	return 0;
}
