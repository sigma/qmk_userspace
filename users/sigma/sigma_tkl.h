// Shared TKL ANSI sigma keymap content. Included by every TKL ANSI sigma
// keymap.c (drop ctrl via the layouts/tkl_ansi community layout, and the
// keychron boards that don't expose tkl_ansi as a community layout from
// their info.json — each maintains a one-line keymap.c that just includes
// this header).
//
// Each translation unit including this header gets its own copy of the
// `keymaps` array; that's fine because the QMK build links one
// keymap.c per firmware binary.

#pragma once

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
        SIGMA_MOD_ROW(3, 4)
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
