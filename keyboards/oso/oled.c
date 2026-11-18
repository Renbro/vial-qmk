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

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    /*
     * Both headers sit with the pins toward the bottom of the board.
     * The right board is a mirror, but the display is not turned around.
     */
    return OLED_ROTATION_270;
}

/* Five glyphs fill the panel. A normal line-feed then inserts a blank row. */
static void write_row(uint8_t row, const char *text) {
    char line[6] = "     ";
    for (uint8_t i = 0; i < 5 && text[i] != '\0'; i++) {
        line[i] = text[i];
    }
    oled_set_cursor(0, row);
    oled_write(line, false);
}

bool oled_task_user(void) {
    draw_oso();

    uint8_t row = 5;
    switch (get_highest_layer(layer_state)) {
        case 0:
            write_row(row, "");
            break;
        case 1:
            write_row(row, "num");
            break;
        case 2:
            write_row(row, "sym");
            break;
        case 15:
            write_row(row, "sys");
            break;
        default: {
            char layer_name[6];
            snprintf(layer_name, sizeof(layer_name), "L%d", get_highest_layer(layer_state));
            write_row(row, layer_name);
            break;
        }
    }

    write_row(++row, "");

    uint8_t mods = get_mods() | get_weak_mods() | get_oneshot_mods();
    led_t   leds = host_keyboard_led_state();

    if (leds.caps_lock) {
        write_row(++row, "caps");
    }
    if (leds.scroll_lock) {
        write_row(++row, "scrl");
    }
    if (mods & MOD_MASK_SHIFT) {
        write_row(++row, "shift");
    }
    if (mods & MOD_MASK_CTRL) {
        write_row(++row, "ctrl");
    }
    if (mods & MOD_MASK_ALT) {
        write_row(++row, "alt");
    }
    if (mods & MOD_MASK_GUI) {
        write_row(++row, "gui");
    }

    while (row < 15) {
        write_row(++row, "");
    }

    return false;
}
