#include QMK_KEYBOARD_H
#include "rdmctmzt_common.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Layer 0: Colemak-DH
     *
     * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
     * │   Tab   │    Q    │    W    │    F    │    P    │    B    │    J    │    L    │    U    │    Y    │    ;    │   Bspc  │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │ Ctl/Esc │    A    │    R    │    S    │    T    │    G    │    M    │    N    │    E    │    I    │    O    │  Ctl/'  │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │   Del   │    Z    │    X    │    C    │    D    │    V    │    K    │    H    │    ,    │    .    │    /    │  Enter  │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │  MO(2)  │  MO(3)  │    `    │   Cmd   │  Shift  │       Space       │   Alt   │  MO(1)  │         │         │         │
     * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
     */
    [0] = LAYOUT_tkl_ansi(
        KC_TAB,    KC_Q,      KC_W,      KC_F,      KC_P,      KC_B,      KC_J,      KC_L,      KC_U,      KC_Y,      KC_SCLN,   KC_BSPC,
        LCTL_T(KC_ESC), KC_A, KC_R,      KC_S,      KC_T,      KC_G,      KC_M,      KC_N,      KC_E,      KC_I,      KC_O,      LCTL_T(KC_QUOT),
        KC_DEL,    KC_Z,      KC_X,      KC_C,      KC_D,      KC_V,      KC_K,      KC_H,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_ENT,
        MO(2),     MO(3),     KC_GRV,    KC_LGUI,   KC_LSFT,   KC_SPC,    KC_LALT,   MO(1),     KC_NO,     KC_NO,     KC_NO
    ),
    /*
     * Layer 1: Reserved - the vendor firmware turns this layer on in Mac mode, so keep it transparent
     *
     * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
     * │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │         ▽         │    ▽    │    ▽    │    ▽    │    ▽    │    ▽    │
     * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
     */
    [1] = LAYOUT_tkl_ansi(
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS
    ),
    /*
     * Layer 2: Fn (left Fn key)
     *
     * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
     * │   Tab   │   BT 1  │   BT 2  │   BT 3  │   2.4G  │ LED Off │  TO(1)  │  TO(0)  │    [    │    ]    │    \    │ LED Tog │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │   Esc   │    1    │    2    │    3    │    4    │    5    │    6    │    7    │    8    │    9    │    0    │    -    │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │  Shift  │   Ins   │   Del   │   Home  │   End   │   PgUp  │   PgDn  │   Hue-  │LED Mode-│LED Mode+│    Up   │ Battery │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │         │   Del   │    `    │   Alt   │ Win Lock│      EE Clear     │   Hue+  │    =    │   Left  │   Down  │  Right  │
     * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
     */
    [2] = LAYOUT_tkl_ansi(
        KC_TAB,    MD_BLE1,   MD_BLE2,   MD_BLE3,   MD_24G,    RM_OFF,    TO(1),     TO(0),     KC_LBRC,   KC_RBRC,   KC_BSLS,   RGB_RTOG,
        KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,
        KC_LSFT,   KC_INS,    KC_DEL,    KC_HOME,   KC_END,    KC_PGUP,   KC_PGDN,   RM_HUED,   RM_PREV,   RM_NEXT,   KC_UP,     QK_BAT,
        KC_NO,     KC_DEL,    KC_GRV,    KC_LALT,   QK_WLO,    EE_CLR,    RM_HUEU,   KC_EQL,    KC_LEFT,   KC_DOWN,   KC_RGHT
    ),
    /*
     * Layer 3: Fn, Mac variant (second Fn key)
     *
     * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
     * │   Tab   │   BT 1  │   BT 2  │   BT 3  │   2.4G  │ LED Off │  TO(1)  │  TO(0)  │    [    │    ]    │    \    │ LED Tog │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │   Esc   │    1    │    2    │    3    │    4    │    5    │    6    │    7    │    8    │    9    │    0    │    -    │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │  Shift  │   Ins   │   Del   │   Home  │   End   │   PgUp  │   PgDn  │   Hue-  │LED Mode-│LED Mode+│   Sat+  │ Battery │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │         │         │    `    │   Cmd   │   Alt   │      EE Clear     │   Hue+  │    =    │ Bright- │   Sat-  │ Bright+ │
     * └─────────┴─────────┴─────────┴─────────┴─────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┘
     */
    [3] = LAYOUT_tkl_ansi(
        KC_TAB,    MD_BLE1,   MD_BLE2,   MD_BLE3,   MD_24G,    RM_OFF,    TO(1),     TO(0),     KC_LBRC,   KC_RBRC,   KC_BSLS,   RGB_RTOG,
        KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,
        KC_LSFT,   KC_INS,    KC_DEL,    KC_HOME,   KC_END,    KC_PGUP,   KC_PGDN,   RM_HUED,   RM_PREV,   RM_NEXT,   RM_SATU,   QK_BAT,
        KC_NO,     KC_NO,     KC_GRV,    KC_LGUI,   KC_LALT,   EE_CLR,    RM_HUEU,   KC_EQL,    RM_VALD,   RM_SATD,   RM_VALU
    )

};
// clang-format on
