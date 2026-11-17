#include QMK_KEYBOARD_H

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    /* The 128x32 panel is mounted on its long edge, pins toward the bottom. */
    return is_keyboard_left() ? OLED_ROTATION_270 : OLED_ROTATION_90;
}

bool oled_task_user(void) {
    oled_write_P(PSTR("oso\n"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("base "), false);
            break;
        case 1:
            oled_write_P(PSTR("num  "), false);
            break;
        case 2:
            oled_write_P(PSTR("sym  "), false);
            break;
        case 15:
            oled_write_P(PSTR("sys  "), false);
            break;
        default:
            oled_write_P(PSTR("layer"), false);
            break;
    }

    return false;
}
