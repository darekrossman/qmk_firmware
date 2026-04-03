#include QMK_KEYBOARD_H

// Combo: Shift + Space = Hyper
const uint16_t PROGMEM hyper_combo[] = {KC_LSFT, LT(1, KC_SPC), COMBO_END};

combo_t key_combos[] = {
    COMBO(hyper_combo, KC_HYPR),
};

// OLED: modifier display + Mac-hardcoded status
#ifdef OLED_ENABLE
static void render_mod_status(void) {
    uint8_t mods = get_mods() | get_oneshot_mods();
    oled_write(mods & MOD_MASK_CTRL  ? "CTL " : "    ", false);
    oled_write(mods & MOD_MASK_SHIFT ? "SFT " : "    ", false);
    oled_write(mods & MOD_MASK_ALT   ? "ALT " : "    ", false);
    oled_write_ln(mods & MOD_MASK_GUI ? "CMD" : "   ", false);
}

static void render_status(void) {
    static const char PROGMEM sep_v[]  = {0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0};
    static const char PROGMEM sep_h1[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};
    static const char PROGMEM sep_h2[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};
    static const char PROGMEM face_1[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xE1, 0};
    static const char PROGMEM face_2[] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xE1, 0};
    static const char PROGMEM os_m_1[] = {0x95, 0x96, 0};
    static const char PROGMEM os_m_2[] = {0xB5, 0xB6, 0};
    static const char PROGMEM s_lock[] = {0x8F, 0x90, 0};
    static const char PROGMEM n_lock[] = {0x91, 0x92, 0};
    static const char PROGMEM c_lock[] = {0x93, 0x94, 0};
    static const char PROGMEM b_lock[] = {0xE1, 0xE1, 0};
#    ifdef AUDIO_ENABLE
    static const char PROGMEM aud_en[] = {0xAF, 0xB0, 0};
    static const char PROGMEM aud_di[] = {0xCF, 0xD0, 0};
#    endif

    oled_write_ln_P(sep_v, false);
    oled_write_P(os_m_1, false);
    oled_write_P(sep_h1, false);
    oled_write_P(face_1, false);
    oled_write_P(os_m_2, false);
    oled_write_P(sep_h1, false);
    oled_write_P(face_2, false);
    oled_write_ln_P(sep_v, false);

    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(led_usb_state.num_lock ? n_lock : b_lock, false);
    oled_write_P(led_usb_state.caps_lock ? c_lock : b_lock, false);
    oled_write_P(led_usb_state.scroll_lock ? s_lock : b_lock, false);
    oled_write_P(sep_h2, false);

#    ifndef AUDIO_ENABLE
    oled_write_P(b_lock, false);
#    endif
    oled_write_P(b_lock, false);

#    ifdef AUDIO_ENABLE
    oled_write_P(is_audio_on() ? aud_en : aud_di, false);
#    endif
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_clear();
        render_mod_status();
        render_status();
        return false;
    }
    return true; // let klor.c render the face on slave side
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
        LCTL_T(KC_ESC), KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    LCTL_T(KC_QUOT),
        KC_DEL,         KC_Z,    KC_X,    KC_C,    KC_D,    KC_V, KC_MUTE,  KC_MPLY, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                        KC_LALT, LGUI_T(KC_BSPC), KC_LSFT, LT(3, KC_TAB),   MO(2), LT(1, KC_SPC), KC_LALT, LGUI_T(KC_TAB)
    ),
    [1] = LAYOUT(
                 KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_NO,
        KC_NO,   KC_NO,   KC_LCTL, KC_LGUI, KC_LALT, KC_NO,                  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_CUT,  KC_COPY, KC_NO,   KC_PSTE, KC_NO, KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                   KC_NO,   KC_NO,   KC_LSFT, KC_NO, KC_NO,  KC_NO,   KC_NO,   KC_NO
    ),
    [2] = LAYOUT(
                 KC_TILD, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                  KC_CIRC, KC_AMPR, KC_ASTR, KC_NO,   KC_NO,
        KC_NO,   KC_EXLM, KC_LT,   KC_LCBR, KC_LPRN, KC_LBRC,                  KC_RBRC, KC_RPRN, KC_RCBR, KC_GT,   KC_BSLS, KC_NO,
        KC_NO,   KC_NO,   KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,  KC_NO,   KC_NO,  KC_TILD, KC_GRV,  KC_CIRC, KC_PIPE, KC_NO,   KC_NO,
                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_NO, KC_NO,  QK_BOOT
    ),
    [3] = LAYOUT(
                 KC_NO,   KC_NO,   KC_NO,   BL_DOWN, BL_UP,        KC_NO,  KC_7,  KC_8,    KC_9,    KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   LCA(KC_F8),   KC_NO,  KC_4,  KC_5,    KC_6,    KC_0,    KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   LCA(KC_F7),   KC_NO,  KC_NO, KC_NO,   KC_1,    KC_2,    KC_3,  KC_NO,  KC_NO,
                          QK_BOOT, KC_NO,   KC_NO,   KC_TRNS,      KC_NO,  KC_NO, KC_NO,   KC_NO
    ),
};
