/*
Copyright 2018 Yann Hodique <yann.hodique@gmail.com> @sigma

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "sigma.h"

// Layer-mod tokens for via_hacks' left-side hyper / meh-with-shift combos.
#define LM_HYPR(layer)   LM(layer, MOD_LGUI | MOD_LCTL | MOD_LALT)
#define LM_HYPR_S(layer) LM(layer, MOD_LGUI | MOD_LCTL | MOD_LALT | MOD_LSFT)

// Indirection so SIGMA_*_ROW macros expand before LAYOUT counts its args.
#define KMAP(...) LAYOUT_ansi_82(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = KMAP(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_GRV,   SIGMA_NUM_ROW,                                                                                      KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   SIGMA_QWE_ROW,                                                                                      KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        SIGMA_CTL,  SIGMA_ASD_ROW,                                                                                                        SIGMA_CTL_R,        KC_HOME,
        SIGMA_LSFT,           SIGMA_ZXC_ROW,                                                                                              SIGMA_RSFT, KC_UP,
        LM_HYPR(_FN), KC_LCMMD, KC_LOPTN,                              KC_SPC,                                 KC_RCMMD, MO(_FN), LM_HYPR_S(_FN), KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = KMAP(
        XXXXXXX,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   XXXXXXX,            UG_TOGG,
        XXXXXXX,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
        XXXXXXX,  UG_PREV,  UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,            XXXXXXX,
        XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  BAT_LVL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX, XXXXXXX,
        XXXXXXX,  XXXXXXX,  XXXXXXX,                                XXXXXXX,                                 XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FN]     = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
};
#endif
