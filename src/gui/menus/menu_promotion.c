#include "gui/menus/menu_promotion.h"


uint8_t on_selection_click() {
	return 1;
}

void menu_promotion_setup() {
	GUI_Menu menu;
	menu.draw_func = menu_promotion_draw;
	menu.update_func = menu_promotion_update;
	menu.button_count = 4;

	GUI_MenuButton queen;
	queen.x = 10;
	queen.y = 70;
	queen.w = 220;
	queen.h = 50;
	queen.callback = on_selection_click;
	queen.hold = 0;

	GUI_MenuButton rook;
	rook.x = 10;
	rook.y = 140;
	rook.w = 220;
	rook.h = 50;
	rook.callback = on_selection_click;
	rook.hold = 0;
	
	GUI_MenuButton bishop;
	bishop.x = 10;
	bishop.y = 210;
	bishop.w = 220;
	bishop.h = 50;
	bishop.callback = on_selection_click;
	bishop.hold = 0;
	
	GUI_MenuButton horse;
	horse.x = 10;
	horse.y = 280;
	horse.w = 220;
	horse.h = 50;
	horse.callback = on_selection_click;
	horse.hold = 0;
	
	menu.buttons[0] = queen;
	menu.buttons[1] = rook;
	menu.buttons[2] = bishop;
	menu.buttons[3] = horse;


	gui_register_menu(MENU_PROMOTION, &menu);
}

void menu_promotion_draw() {
	lcd_clear();

	/// Queen 
	LCD_Point p0, p1;
	p0.x = 10;
	p0.y = 70;
	p1.x = p0.x + 220;
	p1.y = p0.y + 50;

	uint16_t bg_color = rgb_24b_to_16b(0x0044DD);

	lcd_draw_rect_filled(p0, p1, bg_color);

	p1.x = p0.x + 20;
	p1.y = p0.y + 10;

	lcd_draw_text("Queen", COMICSANSMS(), 18, p1, 0xFFFF, bg_color);

	// Rook
	p0.x = 10;
	p0.y = 140;
	p1.x = p0.x + 220;
	p1.y = p0.y + 50;

	bg_color = rgb_24b_to_16b(0x0044DD);

	lcd_draw_rect_filled(p0, p1, bg_color);

	p1.x = p0.x + 20;
	p1.y = p0.y + 10;

	lcd_draw_text("Rook", COMICSANSMS(), 18, p1, 0xFFFF, bg_color);

	// Bishop
	p0.x = 10;
	p0.y = 210;
	p1.x = p0.x + 220;
	p1.y = p0.y + 50;

	bg_color = rgb_24b_to_16b(0x0044DD);

	lcd_draw_rect_filled(p0, p1, bg_color);

	p1.x = p0.x + 20;
	p1.y = p0.y + 10;

	lcd_draw_text("Bishop", COMICSANSMS(), 18, p1, 0xFFFF, bg_color);

	// Horse
	p0.x = 10;
	p0.y = 280;
	p1.x = p0.x + 220;
	p1.y = p0.y + 50;

	bg_color = rgb_24b_to_16b(0x0044DD);

	lcd_draw_rect_filled(p0, p1, bg_color);

	p1.x = p0.x + 22;
	p1.y = p0.y + 10;

	lcd_draw_text("Horse", COMICSANSMS(), 18, p1, 0xFFFF, bg_color);


	// p1.x = 10;
	// p1.y = p0.y + 70;


	
	// lcd_draw_text("You've pressed", COMICSANSMS(), 16, p1, 0x0000, 0xFFFF);

	// p1.x = 100;
	// p1.y = p1.y + 45;

	// lcd_draw_text("0", COMICSANSMS(), 32, p1, 0x0000, 0xFFFF);

	// p1.x = 80;
	// p1.y = p1.y + 20;

	// lcd_draw_text("times", COMICSANSMS(), 16, p1, 0x0000, 0xFFFF);

	lcd_touch_init_postdraw();
}

uint8_t menu_promotion_update() {
	return 0;
}
