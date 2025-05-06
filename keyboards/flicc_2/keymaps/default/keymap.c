#include QMK_KEYBOARD_H

enum custom_keycodes {
    KC_EDIT = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_5x6(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        TG(1)  , KC_SPC,  _______,  _______, _______,  _______
    ),
    [1] = LAYOUT_numpad_5x6(
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_EDIT, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case KC_EDIT:
                tap_code(KC_E);
                wait_ms(15);
                register_code(KC_D);
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
        }
    }
}
