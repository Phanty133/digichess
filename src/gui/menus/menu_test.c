#include "gui/menus/menu_test.h"

static int touch_counter = 0;

uint8_t on_button_click() {
	uart_write_line("button click");
	touch_counter++;

	LCD_Point p0, p1;

	p0.x = 10;
	p0.y = 165;
	p1.x = 230;
	p1.y = 220;

	lcd_select();
	lcd_draw_rect_filled(p0, p1, 0xFFFF);

	char buf[8];
	num2char(touch_counter, buf, 8);

	p0.x = 100;
	p0.y = 165;

	lcd_draw_text(buf, COMICSANSMS(), 32, p0, 0, 0xFFFF);

	return 1;
}

void menu_test_setup() {
	GUI_Menu menu;
	menu.draw_func = menu_test_draw;
	menu.update_func = menu_test_update;
	menu.button_count = 1;

	GUI_MenuButton button;
	button.x = 10;
	button.y = 50;
	button.w = 220;
	button.h = 50;
	button.callback = on_button_click;
	button.hold = 0;

	menu.buttons[0] = button;

	gui_register_menu(MENU_TEST, &menu);
}

void menu_test_draw() {
	lcd_clear();

	LCD_Point p0, p1;
	p0.x = 10;
	p0.y = 50;
	p1.x = p0.x + 220;
	p1.y = p0.y + 50;

	uint16_t bg_color = rgb_24b_to_16b(0x0044DD);

	lcd_draw_rect_filled(p0, p1, bg_color);

	p1.x = p0.x + 22;
	p1.y = p0.y + 10;

	lcd_draw_text("Press here", COMICSANSMS(), 18, p1, 0xFFFF, bg_color);

	p1.x = 10;
	p1.y = p0.y + 70;

	lcd_draw_text("You've pressed", COMICSANSMS(), 16, p1, 0x0000, 0xFFFF);

	p1.x = 100;
	p1.y = p1.y + 45;

	lcd_draw_text("0", COMICSANSMS(), 32, p1, 0x0000, 0xFFFF);

	p1.x = 80;
	p1.y = p1.y + 60;

	lcd_draw_text("times", COMICSANSMS(), 16, p1, 0x0000, 0xFFFF);

	lcd_touch_init_postdraw();
}

uint8_t menu_test_update() {
	return 0;
}
