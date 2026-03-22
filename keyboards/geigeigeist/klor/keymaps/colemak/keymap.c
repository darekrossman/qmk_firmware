#include QMK_KEYBOARD_H

// Combo: Shift + Space = Hyper
const uint16_t PROGMEM hyper_combo[] = {KC_LSFT, LT(1, KC_SPC), COMBO_END};

combo_t key_combos[] = {
    COMBO(hyper_combo, KC_HYPR),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
        LCTL_T(KC_ESC), KC_A, KC_R, KC_S, KC_T, KC_G,                       KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    LCTL_T(KC_QUOT),
        KC_DEL,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V, KC_MUTE, KC_MPLY, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                          KC_LALT, LGUI_T(KC_BSPC), KC_LSFT, LT(3, KC_TAB), MO(2), LT(1, KC_SPC), KC_LALT, LGUI_T(KC_TAB)
    ),
    [1] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                           KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_NO,
        KC_NO,   KC_NO,   KC_LCTL, KC_LGUI, KC_LALT, KC_NO,                  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_CUT,  KC_COPY, KC_NO,   KC_PSTE, KC_NO, KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,  KC_NO,   KC_NO
    ),
    [2] = LAYOUT(
        KC_TILD, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                         KC_CIRC, KC_AMPR, KC_ASTR, KC_NO,   KC_NO,
        KC_NO,   KC_EXLM, KC_LT,   KC_LCBR, KC_LPRN, KC_LBRC,               KC_RBRC, KC_RPRN, KC_RCBR, KC_GT,   KC_BSLS, KC_NO,
        KC_NO,   KC_NO,   KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,  KC_NO, KC_NO,  KC_TILD, KC_GRV,  KC_CIRC, KC_PIPE, KC_NO,   KC_NO,
                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_NO, KC_NO,  QK_BOOT
    ),
    [3] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                           KC_NO,   KC_7,    KC_8,    KC_9,    KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                  KC_NO,   KC_4,    KC_5,    KC_6,    KC_0,    KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,  KC_NO,   KC_1,    KC_2,    KC_3,    KC_NO,   KC_NO,
                           QK_BOOT, KC_NO,   KC_NO,   KC_TRNS, KC_NO,  KC_NO, KC_NO,   KC_NO
    ),
};
