#include QMK_KEYBOARD_H

/*
 * Column 0 is the outer column on both halves. Row 0 is the bottom alpha row,
 * then home, top, and number. Row 4 is the ring utility plus the 5-way switch.
 * Row 5 is the middle utility plus the thumb cluster.
 *
 * Core keys follow the Calico Vial backup. The outer thumbs and the right-hand
 * utility / 5-way keys are Oso-only.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0 - Base */
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,          KC_7,          KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,          KC_U,          KC_I,    KC_O,    KC_P,    KC_QUOT,
        KC_LGUI, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,          KC_J,          KC_K,    KC_L,    KC_SCLN, KC_RGUI,
        KC_LALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,          KC_M,          KC_COMM, KC_DOT,  KC_SLSH, KC_RALT,
        KC_NO,   KC_NO,                                                                                                              KC_PSCR, KC_NO,
        KC_UP,   KC_LEFT, KC_ENT,  KC_RIGHT, KC_DOWN,                           KC_MPLY, KC_MNXT, KC_NO,   KC_MPRV, KC_MUTE,
        KC_LGUI, KC_LSFT, KC_SPC,  KC_LCTL, KC_LALT,                            KC_RCTL, LT(2,KC_ENT), LT(1,KC_BSPC), KC_RSFT, KC_RGUI
    ),

    /* Layer 1 - Numbers / F-keys / Nav */
    [1] = LAYOUT(
        KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,         KC_F7,         KC_F8,   KC_F9,   KC_F10,  KC_F12,
        S(KC_5), KC_SLSH, KC_7,    KC_8,    KC_9,    S(KC_8),                            KC_INS,        KC_HOME,       KC_PGDN, KC_PGUP, KC_END,  KC_TRNS,
        KC_TRNS, KC_DOT,  KC_4,    KC_5,    KC_6,    KC_MINS,                            KC_CAPS,       KC_LEFT,       KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS,
        KC_TRNS, KC_EQL,  KC_1,    KC_2,    KC_3,    S(KC_EQL),                          KC_PSCR,       LCA(KC_LEFT), LCA(KC_RGHT), MEH(KC_LEFT), MEH(KC_RGHT), KC_TRNS,
        KC_NO,   KC_NO,                                                                                                              KC_TRNS, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_0,    KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    /* Layer 2 - Symbols / media */
    [2] = LAYOUT(
        MO(15),  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, S(KC_9), S(KC_0), S(KC_GRV), KC_GRV, KC_TRNS,                           KC_TRNS,       KC_TRNS,       KC_TRNS, KC_CAPS, KC_TRNS, KC_VOLU,
        KC_TRNS, KC_LBRC, KC_RBRC, S(KC_LBRC), S(KC_RBRC), S(KC_MINS),                   KC_TRNS,       KC_MPRV,       KC_MPLY, KC_MUTE, KC_MNXT, KC_VOLD,
        KC_TRNS, S(KC_BSLS), KC_TRNS, KC_TRNS, KC_BSLS, KC_TRNS,                         KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_NO,   KC_NO,                                                                                                              KC_TRNS, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    /* Layer 15 - Maintenance */
    [15] = LAYOUT(
        MO(15),  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,       KC_TRNS,       NK_TOGG, QK_RBT,  EE_CLR,  QK_BOOT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_NO,   KC_NO,                                                                                                              KC_TRNS, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
