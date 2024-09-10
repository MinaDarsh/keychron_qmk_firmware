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

bool is_alt_tab_active = false;
bool is_alt_shift_tab_active = false;
uint16_t alt_tab_timer = 0;

enum layers {
    MAC_BASE,
    WIN_BASE,
    QWERTY,
    KNOB_ALT,
    COM_FN,
};

enum keycodes {
    TQWERTY = SAFE_RANGE,
    KNOBALT,
    FUNCTIO,
    ALTTABK,
    ALTSFTK
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_66(
        KC_HOME,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,   KC_RBRC,  KC_BSLS,
        KC_ESC,   KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     KC_K,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,   KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,     KC_M,     KC_H,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,   KC_UP,	   KC_DEL,
        KC_LCTL,  KC_LOPTN, KC_LCMMD, FUNCTIO,       KC_SPC,                  KC_BSPC,            KC_RCMMD, KC_ROPTN, KC_LEFT,   KC_DOWN,  KC_RGHT),

    [WIN_BASE] = LAYOUT_ansi_66(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
        _______,  KC_LGUI,  KC_LALT,  _______,       _______,                 _______,            KC_RALT,  KC_RCTL,  _______,   _______,  _______),

    [QWERTY] = LAYOUT_ansi_66(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
        _______,  _______,  _______,  KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     _______,   _______,  _______,
        _______,  _______,  KC_S,     KC_D,     KC_F,     _______,  KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  _______,   _______,
        _______,  _______,  _______,  _______,  KC_V,     KC_B,     KC_N,     KC_M,     _______,  _______,  _______,  _______,   _______,  _______,
        _______,  _______,  _______,  _______,       _______,                 _______,            _______,  _______,  _______,   _______,  _______),

    [KNOB_ALT] = LAYOUT_ansi_66(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  LCA(KC_QUOT),
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,
        _______,  _______,  _______,  _______,       _______,                 _______,            _______,  _______,  _______,   _______,  _______),

    [COM_FN] = LAYOUT_ansi_66(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_MPLY,
        KC_GRV,   TQWERTY,  RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_SPI,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PSCR,  KC_SCRL,   KC_PAUS,  KC_INS,
        _______,  RGB_TOG,  RGB_RMOD, RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_SPD,  NK_TOGG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    BAT_LVL,  KNOBALT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,   KC_PGUP,  _______,
        _______,  GU_TOGG,  _______,  _______,       _______,                 _______,            _______,  _______,  KC_HOME,   KC_PGDN,  KC_END)
};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)

void matrix_scan_user(void) {
    if (is_alt_tab_active || is_alt_shift_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            unregister_code(KC_LSFT);
            is_alt_tab_active = false;
            is_alt_shift_tab_active = false;
        }
    }
};

const uint16_t PROGMEM encoder_map[][2][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_WH_U, KC_WH_D),ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_BASE] = {ENCODER_CCW_CW(ALTSFTK, ALTTABK),ENCODER_CCW_CW(_______, _______)},
    [QWERTY]   = {ENCODER_CCW_CW(_______, _______),ENCODER_CCW_CW(_______, _______)},
    [KNOB_ALT] = {ENCODER_CCW_CW(KC_LBRC, KC_RBRC),ENCODER_CCW_CW(KC_MINS, KC_QUOT)},
    [COM_FN]   = {ENCODER_CCW_CW(_______, _______),ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
};

#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    switch (keycode) {
    case TQWERTY:
        if (record->event.pressed) {
            if (!layer_state_is(QWERTY)) {
                layer_on(QWERTY);
            } else {
                layer_off(QWERTY);
            }
            return false;
        }
    case KNOBALT:
        if (record->event.pressed) {
            if (!layer_state_is(KNOB_ALT)) {
                layer_on(KNOB_ALT);
            } else {
                layer_off(KNOB_ALT);
            }
            return false;
        }
    case FUNCTIO:
        if (record->event.pressed) {
            layer_on(COM_FN);
        } else {
            layer_off(COM_FN);
        }
        return false;
# if defined (ENCODER_MAP_ENABLE)
    case ALTTABK:
        if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                is_alt_shift_tab_active = false;
                unregister_code(KC_LSFT);
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            tap_code(KC_TAB);
        }
        return false;
    case ALTSFTK:
        if (record->event.pressed) {
            if (!is_alt_shift_tab_active) {
                is_alt_shift_tab_active = true;
                is_alt_tab_active = false;
                register_code(KC_LALT);
                register_code(KC_LSFT);
            }
            alt_tab_timer = timer_read();
            tap_code(KC_TAB);
        }
        return false;
# endif
    }
    return true;
}
