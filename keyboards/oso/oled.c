#include QMK_KEYBOARD_H

/*
 * 32x32 trace of the Oso mark. Bit 31 is the left pixel.
 * The drawing is square, and so is this bitmap. The panel is only 32px
 * wide once it is turned on its side.
 */
static const uint32_t oso_face[] = {
    0x0000F000, 0x000BE000, 0x001E7E00, 0x006C4600, 0x3EE00F7C, 0x638007C6, 0xD1B09F8B, 0xD8BEA03F,
    0xBC0E403E, 0xF80FB01F, 0xF807E01F, 0x7807831E, 0x79C38F9E, 0x10F3DC0C, 0x107FF98C, 0x33FFFF8C,
    0x33FA5F84, 0x23F81FC4, 0x6011C806, 0xC007E003, 0xE007E007, 0x7007E00F, 0x7003C00E, 0x7010880E,
    0x7C30983E, 0x7E0FE07E, 0x1F2004F8, 0x0FF1C7F0, 0x07F9DFE0, 0x01FFFF80, 0x007FFE00, 0x000FF000,
};

static void draw_oso(void) {
    for (uint8_t y = 0; y < ARRAY_SIZE(oso_face); y++) {
        uint32_t row = oso_face[y];
        for (uint8_t x = 0; x < 32; x++) {
            oled_write_pixel(x, y, (row & (1UL << (31 - x))) != 0);
        }
    }
}

static void status_line(const char *label, bool on) {
    oled_write_ln_P(label, on);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    /* The 128x32 panel is mounted on its long edge, pins toward the bottom. */
    return is_keyboard_left() ? OLED_ROTATION_270 : OLED_ROTATION_90;
}

bool oled_task_user(void) {
    draw_oso();
    oled_set_cursor(0, 5);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("base"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("num"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("sym"), false);
            break;
        case 15:
            oled_write_ln_P(PSTR("sys"), false);
            break;
        default: {
            char layer_name[6];
            snprintf(layer_name, sizeof(layer_name), "L%d", get_highest_layer(layer_state));
            oled_write_ln(layer_name, false);
            break;
        }
    }

    uint8_t mods = get_mods() | get_weak_mods() | get_oneshot_mods();
    led_t   leds = host_keyboard_led_state();

    status_line(PSTR("caps"), leds.caps_lock);
    status_line(PSTR("scrl"), leds.scroll_lock);
    status_line(PSTR("shift"), (mods & MOD_MASK_SHIFT) != 0);
    status_line(PSTR("ctrl"), (mods & MOD_MASK_CTRL) != 0);
    status_line(PSTR("alt"), (mods & MOD_MASK_ALT) != 0);
    status_line(PSTR("gui"), (mods & MOD_MASK_GUI) != 0);

    return false;
}
