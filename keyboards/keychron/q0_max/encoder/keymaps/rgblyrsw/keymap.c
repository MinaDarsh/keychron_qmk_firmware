/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum keycodes {
    LYR_INC = SAFE_RANGE,
    LYR_DEC
};

#define LAYER_CYCLE_START 0
#define LAYER_CYCLE_END 3

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_tenkey_27(
        RGB_TOG, KC_MPRV, KC_MPLY, KC_MNXT, _______,
        KC_APP,  KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_SLEP, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_PSCR, KC_P4,   KC_P5,   KC_P6,
        KC_INS,  KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        _______, KC_P0,            KC_PDOT          ),

    [1] = LAYOUT_tenkey_27(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______,          _______          ),

    [2] = LAYOUT_tenkey_27(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______,          _______          ),

    [3] = LAYOUT_tenkey_27(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______,          _______          )
};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0]   = {ENCODER_CCW_CW(LYR_DEC, LYR_INC)},
    [1]   = {ENCODER_CCW_CW(LYR_DEC, LYR_INC)},
    [2]   = {ENCODER_CCW_CW(LYR_DEC, LYR_INC)},
    [3]   = {ENCODER_CCW_CW(LYR_DEC, LYR_INC)},
};
#endif // ENCODER_MAP_ENABLE

bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
    case 0:
        rgb_matrix_set_color_all(255,255,255);
        break;
    case 1:
        rgb_matrix_set_color_all(255,0,0);
        break;
    case 2:
        rgb_matrix_set_color_all(0,255,0);
        break;
    case 3:
        rgb_matrix_set_color_all(0,0,255);
        break;
    default:
        break;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
# if defined (ENCODER_MAP_ENABLE)
    uint8_t current_layer = get_highest_layer(layer_state);
    switch (keycode) {
    case LYR_INC:
        if (!record->event.pressed) {
            return false;
        }

        if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
            return false;
        }

        uint8_t next_layer = current_layer + 1;
        if (next_layer > LAYER_CYCLE_END) {
            next_layer = LAYER_CYCLE_START;
        }
        layer_move(next_layer);
        return false;
    case LYR_DEC:
        if (!record->event.pressed) {
            return false;
        }

        if (current_layer > LAYER_CYCLE_END || current_layer < LAYER_CYCLE_START) {
            return false;
        }

        int8_t prev_layer = current_layer - 1;
        if (prev_layer < LAYER_CYCLE_START) {
            prev_layer = LAYER_CYCLE_END;
        }
        layer_move(prev_layer);
        return false;
# endif
    }
    return true;
}
