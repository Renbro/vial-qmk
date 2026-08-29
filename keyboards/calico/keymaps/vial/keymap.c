#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Layer 0 - Base */
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,          KC_7,          KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,          KC_U,          KC_I,    KC_O,    KC_P,    KC_QUOT,
        KC_LALT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,          KC_J,          KC_K,    KC_L,    KC_SCLN, KC_RALT,
        KC_LGUI, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,          KC_M,          KC_COMM, KC_DOT,  KC_SLSH, KC_RGUI,
                                            KC_LSFT, KC_SPC,  KC_LCTL,          LT(2,KC_ENT), LT(1,KC_BSPC), KC_RSFT
    ),

    /* Layer 1 - Numbers / F-keys / Nav / Media */
    [1] = LAYOUT(
        KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,         KC_F7,         KC_F8,   KC_F9,   KC_F10,  KC_F12,
        KC_TRNS, KC_SLSH, KC_7,    KC_8,    KC_9,    KC_ASTR,                            KC_INS,        KC_HOME,       KC_PGDN, KC_PGUP, KC_END,  KC_VOLU,
        KC_TRNS, KC_EQL,  KC_4,    KC_5,    KC_6,    KC_MINS,                            KC_CAPS,       KC_LEFT,       KC_DOWN, KC_UP,   KC_RGHT, KC_VOLD,
        KC_TRNS, KC_DOT,  KC_1,    KC_2,    KC_3,    KC_PLUS,                            KC_PSCR,       KC_MPRV,       KC_MPLY, KC_MUTE, KC_MNXT, KC_TRNS,
                                            KC_TRNS, KC_0,    KC_TRNS,          KC_TRNS,       KC_TRNS,       KC_TRNS
    ),

    /* Layer 2 - Symbols */
    [2] = LAYOUT(
        MO(15),  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_HASH,                            KC_QUES,       KC_TILD,       KC_GRV,  KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LPRN, KC_RPRN, KC_UNDS, KC_BSLS, KC_DLR,                             KC_EXLM,       KC_AT,         KC_DQUO, KC_COLN, KC_CIRC, KC_TRNS,
        KC_TRNS, KC_PIPE, KC_LABK, KC_RABK, KC_AMPR, KC_PERC,                            KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,       KC_TRNS,       KC_TRNS
    ),

    /* Layer 15 - Maintenance */
    [15] = LAYOUT(
        MO(15),  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,       KC_TRNS,       NK_TOGG, QK_RBT,  EE_CLR,  QK_BOOT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,       KC_TRNS,       KC_TRNS
    )
};