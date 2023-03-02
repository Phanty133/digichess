#include "gui/gui.h"

static GUI_State state;
static uint8_t prev_loop_touched = 0;
static uint8_t screen_updated = 0;

static GUI_Menu* get_active() {
	return &state.menus[state.active_menu];
}

static void draw_active_menu() {
	get_active()->draw_func();
	screen_updated = 1;
}

void gui_update() {
	GUI_Menu* menu = get_active();

	screen_updated |= menu->update_func();

	uint16_t touch_x;
	uint16_t touch_y;

	if (screen_updated) {
		lcd_touch_init_postdraw();
		screen_updated = 0;
	}

	uint8_t touching = lcd_touch_read_coords(&touch_x, &touch_y, 0);

	if (touching) {
		for (int i = 0; i < menu->button_count; i++) {
			GUI_MenuButton* btn = &menu->buttons[i];

			if (
				(btn->hold || (!btn->hold && !prev_loop_touched))
				&& touch_x >= btn->x
				&& touch_x <= btn->x + btn->w
				&& touch_y >= btn->y
				&& touch_y <= btn->y + btn->h
			) {
				screen_updated |= btn->callback();
			}
		}
	} else if (!touching && prev_loop_touched) {
		prev_loop_touched = 0;
	}
}

void gui_set_menu(GUI_MenuID menu) {
	state.active_menu = menu;
	lcd_select();
	draw_active_menu();
}

void gui_register_menu(GUI_MenuID id, GUI_Menu* menu) {
	memory_copy(&state.menus[id], menu, sizeof(GUI_Menu));
}
