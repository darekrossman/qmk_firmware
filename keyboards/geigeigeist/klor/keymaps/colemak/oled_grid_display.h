#pragma once

#include OLED_FONT_H

#define OLED_CELL_SIZE 12
#define OLED_CELL_GAP_X 1
#define OLED_CELL_GAP_Y 3
#define OLED_SIDE_PADDING 2
#define OLED_TOP_PADDING 2
#define OLED_GLYPH_X_OFFSET ((OLED_CELL_SIZE - OLED_FONT_WIDTH) / 2)
#define OLED_GLYPH_Y_OFFSET ((OLED_CELL_SIZE - OLED_FONT_HEIGHT) / 2)

static const uint8_t oled_row_lengths[] = {5, 6, 6, 4};

static const keypos_t left_oled_rows[][7] = {
    {{.row = 0, .col = 1}, {.row = 0, .col = 2}, {.row = 0, .col = 3}, {.row = 0, .col = 4}, {.row = 0, .col = 5}},
    {{.row = 1, .col = 0}, {.row = 1, .col = 1}, {.row = 1, .col = 2}, {.row = 1, .col = 3}, {.row = 1, .col = 4}, {.row = 1, .col = 5}},
    {{.row = 2, .col = 0}, {.row = 2, .col = 1}, {.row = 2, .col = 2}, {.row = 2, .col = 3}, {.row = 2, .col = 4}, {.row = 2, .col = 5}, {.row = 3, .col = 5}},
    {{.row = 3, .col = 1}, {.row = 3, .col = 2}, {.row = 3, .col = 3}, {.row = 3, .col = 4}},
};

static const keypos_t right_oled_rows[][7] = {
    {{.row = 4, .col = 5}, {.row = 4, .col = 4}, {.row = 4, .col = 3}, {.row = 4, .col = 2}, {.row = 4, .col = 1}},
    {{.row = 5, .col = 5}, {.row = 5, .col = 4}, {.row = 5, .col = 3}, {.row = 5, .col = 2}, {.row = 5, .col = 1}, {.row = 5, .col = 0}},
    {{.row = 7, .col = 5}, {.row = 6, .col = 5}, {.row = 6, .col = 4}, {.row = 6, .col = 3}, {.row = 6, .col = 2}, {.row = 6, .col = 1}, {.row = 6, .col = 0}},
    {{.row = 7, .col = 4}, {.row = 7, .col = 3}, {.row = 7, .col = 2}, {.row = 7, .col = 1}},
};

static uint16_t get_oled_keycode(layer_state_t active_layers, keypos_t key) {
    for (int8_t layer = (int8_t)get_highest_layer(active_layers); layer >= 0; --layer) {
        if (!(active_layers & ((layer_state_t)1 << layer))) {
            continue;
        }

        uint16_t keycode = keymap_key_to_keycode((uint8_t)layer, key);
        if (keycode != KC_TRNS) {
            return keycode;
        }
    }

    return KC_NO;
}

static char get_oled_key_char(uint16_t keycode) {
    if (IS_QK_MOD_TAP(keycode)) {
        return get_oled_key_char(QK_MOD_TAP_GET_TAP_KEYCODE(keycode));
    }

    if (IS_QK_LAYER_TAP(keycode)) {
        uint16_t tap_keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
        switch (tap_keycode) {
            case KC_SPC:
            case KC_TAB:
                return '0' + QK_LAYER_TAP_GET_LAYER(keycode);
            default:
                return get_oled_key_char(tap_keycode);
        }
    }

    if (IS_QK_MOMENTARY(keycode)) {
        return '0' + QK_MOMENTARY_GET_LAYER(keycode);
    }

    if (IS_QK_TO(keycode)) {
        return '0' + QK_TO_GET_LAYER(keycode);
    }

    if (IS_QK_TOGGLE_LAYER(keycode)) {
        return '0' + QK_TOGGLE_LAYER_GET_LAYER(keycode);
    }

    if (IS_QK_ONE_SHOT_LAYER(keycode)) {
        return '0' + QK_ONE_SHOT_LAYER_GET_LAYER(keycode);
    }

    if (keycode >= KC_A && keycode <= KC_Z) {
        return 'A' + (keycode - KC_A);
    }

    if (keycode >= KC_1 && keycode <= KC_9) {
        return '1' + (keycode - KC_1);
    }

    switch (keycode) {
        case KC_0:
            return '0';
        case KC_ESC:
            return 'X';
        case KC_TAB:
            return 'T';
        case KC_BSPC:
            return 'B';
        case KC_ENT:
            return 'E';
        case KC_SPC:
            return 'S';
        case KC_DEL:
            return 'D';
        case KC_HOME:
            return 'H';
        case KC_PGDN:
            return 'D';
        case KC_PGUP:
            return 'U';
        case KC_END:
            return 'N';
        case KC_LEFT:
            return '<';
        case KC_DOWN:
            return 'v';
        case KC_UP:
            return '^';
        case KC_RGHT:
            return '>';
        case KC_LCTL:
            return 'C';
        case KC_LGUI:
            return 'G';
        case KC_LALT:
            return 'A';
        case KC_LSFT:
            return 'S';
        case KC_MUTE:
            return 'M';
        case KC_MPLY:
            return 'P';
        case KC_CUT:
            return 'X';
        case KC_COPY:
            return 'C';
        case KC_PSTE:
            return 'V';
        case BL_DOWN:
            return '-';
        case BL_UP:
            return '+';
        case KC_SCLN:
            return ';';
        case KC_QUOT:
            return '\'';
        case KC_COMM:
            return ',';
        case KC_DOT:
            return '.';
        case KC_SLSH:
            return '/';
        case KC_GRV:
            return '`';
        case KC_TILD:
            return '~';
        case KC_AT:
            return '@';
        case KC_HASH:
            return '#';
        case KC_DLR:
            return '$';
        case KC_PERC:
            return '%';
        case KC_CIRC:
            return '^';
        case KC_AMPR:
            return '&';
        case KC_ASTR:
            return '*';
        case KC_EXLM:
            return '!';
        case KC_LT:
            return '<';
        case KC_GT:
            return '>';
        case KC_PIPE:
            return '|';
        case KC_UNDS:
            return '_';
        case KC_MINS:
            return '-';
        case KC_PLUS:
            return '+';
        case KC_EQL:
            return '=';
        case KC_BSLS:
            return '\\';
        case KC_LBRC:
            return '[';
        case KC_RBRC:
            return ']';
        case KC_LCBR:
            return '{';
        case KC_RCBR:
            return '}';
        case KC_LPRN:
            return '(';
        case KC_RPRN:
            return ')';
        case LCA(KC_F7):
            return '7';
        case LCA(KC_F8):
            return '8';
        case QK_BOOT:
            return '*';
        case KC_TRNS:
        case KC_NO:
            return ' ';
        default:
            return '?';
    }
}

static void oled_draw_horizontal_line(uint8_t x, uint8_t y, uint8_t length) {
    for (uint8_t i = 0; i < length; ++i) {
        oled_write_pixel(x + i, y, true);
    }
}

static void oled_draw_vertical_line(uint8_t x, uint8_t y, uint8_t length) {
    for (uint8_t i = 0; i < length; ++i) {
        oled_write_pixel(x, y + i, true);
    }
}

static void oled_draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
    oled_draw_horizontal_line(x, y, width);
    oled_draw_horizontal_line(x, y + height - 1, width);
    oled_draw_vertical_line(x, y, height);
    oled_draw_vertical_line(x + width - 1, y, height);
}

static void oled_fill_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool on) {
    for (uint8_t row = 0; row < height; ++row) {
        for (uint8_t col = 0; col < width; ++col) {
            oled_write_pixel(x + col, y + row, on);
        }
    }
}

static bool is_oled_key_active(keypos_t key) {
    return matrix_get_row(key.row) & ((matrix_row_t)1 << key.col);
}

static uint32_t get_oled_active_mask(bool is_left) {
    const keypos_t(*rows)[7] = is_left ? left_oled_rows : right_oled_rows;
    uint32_t mask            = 0;
    uint8_t  bit             = 0;

    for (uint8_t row = 0; row < ARRAY_SIZE(oled_row_lengths); ++row) {
        for (uint8_t col = 0; col < oled_row_lengths[row]; ++col) {
            if (is_oled_key_active(rows[row][col])) {
                mask |= ((uint32_t)1 << bit);
            }
            ++bit;
        }
    }

    return mask;
}

static uint8_t get_oled_row_width(uint8_t row_length) {
    return row_length * OLED_CELL_SIZE + (row_length - 1) * OLED_CELL_GAP_X;
}

static uint8_t get_oled_row_start_x(bool is_left, uint8_t row_length) {
    const uint8_t row_width = get_oled_row_width(row_length);

    if (is_left) {
        return OLED_DISPLAY_WIDTH - OLED_SIDE_PADDING - row_width;
    }

    return OLED_SIDE_PADDING;
}

static uint8_t get_oled_row_y(uint8_t row) {
    return OLED_TOP_PADDING + row * (OLED_CELL_SIZE + OLED_CELL_GAP_Y);
}

static void oled_draw_char_at(uint8_t x, uint8_t y, char data, bool invert) {
    uint8_t cast_data = (uint8_t)data;

    if (cast_data == ' ' || cast_data < OLED_FONT_START || cast_data > OLED_FONT_END) {
        return;
    }

    const uint8_t *glyph = &font[(cast_data - OLED_FONT_START) * OLED_FONT_WIDTH];

    for (uint8_t col = 0; col < OLED_FONT_WIDTH; ++col) {
        uint8_t bits = pgm_read_byte(glyph + col);

        for (uint8_t row = 0; row < OLED_FONT_HEIGHT; ++row) {
            oled_write_pixel(x + col, y + row, invert ? !(bits & 0x01) : (bits & 0x01));
            bits >>= 1;
        }
    }
}

static void render_oled_keymap(bool is_left, layer_state_t active_layers, uint32_t active_mask) {
    const keypos_t(*rows)[7] = is_left ? left_oled_rows : right_oled_rows;
    uint8_t bit = 0;

    oled_clear();

    for (uint8_t row = 0; row < ARRAY_SIZE(oled_row_lengths); ++row) {
        const uint8_t y = get_oled_row_y(row);
        uint8_t       x = get_oled_row_start_x(is_left, oled_row_lengths[row]);

        for (uint8_t col = 0; col < oled_row_lengths[row]; ++col) {
            const uint16_t keycode = get_oled_keycode(active_layers, rows[row][col]);
            const char     label   = get_oled_key_char(keycode);
            const bool     active  = active_mask & ((uint32_t)1 << bit);

            oled_draw_rect(x, y, OLED_CELL_SIZE, OLED_CELL_SIZE);
            if (active) {
                oled_fill_rect(x + 1, y + 1, OLED_CELL_SIZE - 2, OLED_CELL_SIZE - 2, true);
            }
            oled_draw_char_at(x + OLED_GLYPH_X_OFFSET, y + OLED_GLYPH_Y_OFFSET, label, active);

            x += OLED_CELL_SIZE + OLED_CELL_GAP_X;
            ++bit;
        }
    }
}

bool oled_task_user(void) {
    static layer_state_t last_active_layers = (layer_state_t)-1;
    static bool          last_is_left       = false;
    static uint32_t      last_active_mask   = (uint32_t)-1;
    static uint32_t      last_redraw        = 0;
    const bool           is_left            = is_keyboard_left();
    const layer_state_t  active_layers      = layer_state | default_layer_state;
    const uint32_t       active_mask        = get_oled_active_mask(is_left);

    if (active_layers != last_active_layers || is_left != last_is_left || active_mask != last_active_mask || timer_elapsed32(last_redraw) > 1000) {
        render_oled_keymap(is_left, active_layers, active_mask);
        last_active_layers = active_layers;
        last_is_left       = is_left;
        last_active_mask   = active_mask;
        last_redraw        = timer_read32();
    }

    return false;
}
