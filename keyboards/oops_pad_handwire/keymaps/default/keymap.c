// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

bool is_scrolling = false;
static uint16_t scroll_timer = 0;
uint16_t scroll_delay = 20;  // Adjust this value to change scroll speed (higher = slower)


enum custom_keycodes {
    KC_EDIT = SAFE_RANGE,
    KC_SCROLL,
};

enum {
    TD_ESC_L1  // Define Tap Dance for ESC key
};

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Layer Toggle
    [TD_ESC_L1] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_ESC, 1)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x6(
        TD(TD_ESC_L1),  KC_5,    KC_1,    KC_2,    KC_3,    KC_4,
        KC_T,           KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,
        KC_G,           KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,
        KC_B,           KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V
    ),

    [1] = LAYOUT_ortho_4x6(
        _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    KC_EDIT,    _______,
        _______,    _______,    _______,    _______,    _______,    KC_SCROLL
    )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case KC_EDIT:
                tap_code(KC_E);
                wait_ms(15);
                register_code(KC_D);
                return false;
            case KC_SCROLL:
            is_scrolling = true;
            return false;
        }
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        switch(keycode) {
            case KC_EDIT:
                unregister_code(KC_D);
                break;
            case KC_SCROLL:
            is_scrolling = false;
        }
    }
}

void matrix_scan_user(void) { // The very important timer.
    if (is_scrolling) {
            if (timer_elapsed(scroll_timer) > scroll_delay) {
                tap_code(MS_WHLD);
                scroll_timer = timer_read();
            }
        }
}
