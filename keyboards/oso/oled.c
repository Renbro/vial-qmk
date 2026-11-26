#include QMK_KEYBOARD_H
#include "split_util.h"

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

static void draw_oso(uint8_t y0) {
    for (uint8_t y = 0; y < ARRAY_SIZE(oso_face); y++) {
        uint32_t row = oso_face[y];
        for (uint8_t x = 0; x < 32; x++) {
            oled_write_pixel(x, y0 + y, (row & (1UL << (31 - x))) != 0);
        }
    }
}

/* Glcd columns for the layer names. Bit 0 is the top. */
static const uint8_t glyph_n[5] = {0x7C, 0x08, 0x04, 0x04, 0x78};
static const uint8_t glyph_u[5] = {0x3C, 0x40, 0x40, 0x20, 0x7C};
static const uint8_t glyph_m[5] = {0x7C, 0x04, 0x78, 0x04, 0x78};
static const uint8_t glyph_s[5] = {0x48, 0x54, 0x54, 0x54, 0x24};
static const uint8_t glyph_y[5] = {0x4C, 0x90, 0x90, 0x90, 0x7C};
static const uint8_t glyph_L[5] = {0x7F, 0x40, 0x40, 0x40, 0x40};
static const uint8_t glyph_digit[10][5] = {
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, {0x00, 0x42, 0x7F, 0x40, 0x00}, {0x72, 0x49, 0x49, 0x49, 0x46},
    {0x21, 0x41, 0x49, 0x4D, 0x33}, {0x18, 0x14, 0x12, 0x7F, 0x10}, {0x27, 0x45, 0x45, 0x45, 0x39},
    {0x3C, 0x4A, 0x49, 0x49, 0x31}, {0x41, 0x21, 0x11, 0x09, 0x07}, {0x36, 0x49, 0x49, 0x49, 0x36},
    {0x46, 0x49, 0x49, 0x29, 0x1E},
};

static const uint8_t *glyph_for(char c) {
    switch (c) {
        case 'n':
            return glyph_n;
        case 'u':
            return glyph_u;
        case 'm':
            return glyph_m;
        case 's':
            return glyph_s;
        case 'y':
            return glyph_y;
        case 'L':
            return glyph_L;
        default:
            if (c >= '0' && c <= '9') {
                return glyph_digit[c - '0'];
            }
            return NULL;
    }
}

/* Two pixels wide and three tall, so three letters fill the 32px panel. */
static void draw_big_layer(const char *text) {
    for (uint8_t y = 0; y < 24; y++) {
        for (uint8_t x = 0; x < 32; x++) {
            oled_write_pixel(x, y, false);
        }
    }

    uint8_t count = 0;
    while (text[count] != '\0' && count < 3) {
        count++;
    }
    if (count == 0) {
        return;
    }

    uint8_t span = count * 10 + (count - 1);
    uint8_t x0   = (32 - span) / 2;
    for (uint8_t i = 0; i < count; i++) {
        const uint8_t *glyph = glyph_for(text[i]);
        if (glyph == NULL) {
            continue;
        }
        uint8_t gx = x0 + i * 11;
        for (uint8_t col = 0; col < 5; col++) {
            for (uint8_t bit = 1; bit < 8; bit++) {
                bool on = (glyph[col] & (1U << bit)) != 0;
                for (uint8_t dy = 0; dy < 3; dy++) {
                    for (uint8_t dx = 0; dx < 2; dx++) {
                        oled_write_pixel(gx + col * 2 + dx, 2 + (bit - 1) * 3 + dy, on);
                    }
                }
            }
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

/* The stock 6x8 font, read straight from its table for the tall rows below. */
#include OLED_FONT_H

/*
 * Rows of the stock font drawn twice as tall: 5 glyphs x 6px = 30px wide,
 * 16px high. The panel is only 32px across, so height is the room to grow.
 */
#define TALL_ROW_HEIGHT 16
#define TALL_TOP 32

static void draw_tall_row(uint8_t y0, const char *text) {
    for (uint8_t y = 0; y < TALL_ROW_HEIGHT; y++) {
        for (uint8_t x = 0; x < 32; x++) {
            oled_write_pixel(x, y0 + y, false);
        }
    }

    uint8_t count = 0;
    while (text[count] != '\0' && count < 5) {
        count++;
    }
    if (count == 0) {
        return;
    }

    uint8_t x0 = (32 - (count * 6 - 1)) / 2;
    for (uint8_t i = 0; i < count; i++) {
        const unsigned char *glyph = &font[(uint8_t)text[i] * 6];
        for (uint8_t col = 0; col < 5; col++) {
            uint8_t bits = pgm_read_byte(&glyph[col]);
            for (uint8_t bit = 0; bit < 8; bit++) {
                if (bits & (1U << bit)) {
                    oled_write_pixel(x0 + i * 6 + col, y0 + bit * 2, true);
                    oled_write_pixel(x0 + i * 6 + col, y0 + bit * 2 + 1, true);
                }
            }
        }
    }
}

/*
 * A half without USB waits for the master. The split watchdog reboots it
 * about every 2 s until the master is heard, so a dead TRRS link would keep
 * it on the splash. Give a normal start this long, then say there is no link.
 */
#define NO_LINK_GRACE 1000

bool oled_task_user(void) {
    static uint32_t splash_start;
    static bool     splash_ready = false;
    static bool     splash_done  = false;
    if (!is_keyboard_master() && !split_watchdog_check()) {
        /* Same rows as the splash, which overwrites them once linked. */
        bool late = timer_read32() > NO_LINK_GRACE;
        draw_tall_row(48, late ? "no" : "");
        draw_tall_row(48 + TALL_ROW_HEIGHT, late ? "link" : "");
        return false;
    }
    /* The splash starts on the master at power-up, on the other half once it
     * hears the master. */
    if (!splash_ready) {
        splash_start = timer_read32();
        splash_ready = true;
    }
    if (!splash_done) {
        if (timer_elapsed32(splash_start) < 5000) {
            /* 32px mark, centered on the 128px panel. */
            draw_oso(48);
            return false;
        }
        /*
         * Text rows are 5 glyphs x 6px = 30px, so they never touch the last
         * two columns of the 32px panel. Wipe the mark once so none of it
         * is left behind there.
         */
        oled_clear();
        splash_done = true;
    }

    const char *layer_name = "";
    char        layer_buf[6];
    switch (get_highest_layer(layer_state)) {
        case 0:
            break;
        case 1:
            layer_name = "num";
            break;
        case 2:
            layer_name = "sym";
            break;
        case 15:
            layer_name = "sys";
            break;
        default:
            snprintf(layer_buf, sizeof(layer_buf), "L%d", get_highest_layer(layer_state));
            layer_name = layer_buf;
            break;
    }
    draw_big_layer(layer_name);

    /* Clear the gap under the layer block. Six tall rows then fill the rest. */
    for (uint8_t y = 24; y < TALL_TOP; y++) {
        for (uint8_t x = 0; x < 32; x++) {
            oled_write_pixel(x, y, false);
        }
    }

    uint8_t mods = get_mods() | get_weak_mods() | get_oneshot_mods();
    led_t   leds = host_keyboard_led_state();

    const char *lines[8];
    uint8_t     n = 0;
    /* The master runs alone when the other half does not answer. */
    if (is_keyboard_master() && !is_transport_connected()) {
        lines[n++] = "no";
        lines[n++] = "link";
    }
    if (leds.caps_lock) lines[n++] = "caps";
    if (leds.scroll_lock) lines[n++] = "scrl";
    if (mods & MOD_MASK_SHIFT) lines[n++] = "shift";
    if (mods & MOD_MASK_CTRL) lines[n++] = "ctrl";
    if (mods & MOD_MASK_ALT) lines[n++] = "alt";
    if (mods & MOD_MASK_GUI) lines[n++] = "gui";

    for (uint8_t i = 0; i < 6; i++) {
        draw_tall_row(TALL_TOP + i * TALL_ROW_HEIGHT, i < n ? lines[i] : "");
    }

    return false;
}
