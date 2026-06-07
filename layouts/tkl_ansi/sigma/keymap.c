#include QMK_KEYBOARD_H
#include "sigma.h"

// Indirection so SIGMA_*_ROW macros expand before LAYOUT counts its args.
#define KMAP(...) LAYOUT_tkl_ansi(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = KMAP(
        KC_ESC,  SIGMA_FN_ROW,                                                                                       KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  SIGMA_NUM_ROW,                                                                    KC_MINS, KC_EQL,  KC_BSPC,            KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  SIGMA_QWE_ROW,                                                                    KC_LBRC, KC_RBRC, KC_BSLS,            KC_DEL,  KC_END,  KC_PGDN,
        SIGMA_CTL,  SIGMA_ASD_ROW,                                                                                   SIGMA_CTL_R,
        SIGMA_LSFT, SIGMA_ZXC_ROW,                                                                                   SIGMA_RSFT,                  KC_UP,
        SIGMA_HYPER, KC_LGUI, KC_LALT,                   KC_SPC,                         KC_RALT, KC_RGUI, SIGMA_FN, SIGMA_HYPER_S,    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN] = KMAP(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            KC_MUTE, _______, _______,
        _______, SIGMA_BT1, SIGMA_BT2, SIGMA_BT3, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    KC_MPLY, KC_MSTP, KC_VOLU,
        SIGMA_BL_TOGG, SIGMA_BL_NEXT, SIGMA_BL_VALU, SIGMA_BL_HUEU, SIGMA_BL_SATU, SIGMA_BL_SPDU, _______, _______, _______, _______, SIGMA_BAT, _______, _______, _______,   KC_MPRV, KC_MNXT, KC_VOLD,
        _______, SIGMA_BL_PREV, SIGMA_BL_VALD, SIGMA_BL_HUED, SIGMA_BL_SATD, SIGMA_BL_SPDD, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,                              _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______
    ),
};

#ifdef RGB_MATRIX_ENABLE
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RM_TOGG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true;
    }
}
#endif
