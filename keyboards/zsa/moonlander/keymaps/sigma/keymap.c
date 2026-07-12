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
#include "sigma.h"

// When the zsa/oryx community module is compiled in (via keymap.json), its
// config.h is force-included and defines ORYX_ENABLE, and oryx.h lands on the
// include path -- pull it in so the RGB indicator can yield to Oryx / Keymapp
// while it drives the LEDs over webHID.
#ifdef ORYX_ENABLE
#    include "oryx.h"
#endif

// Indirection so SIGMA_*_L/R halves expand before LAYOUT counts its args.
#define KMAP(...) LAYOUT_moonlander(__VA_ARGS__)

// The Moonlander is an ergo split like the Ergodox, so it borrows the shared
// SIGMA_*_L/R QWERTY halves. On top of that it carries three board-specific
// features the rest of the userspace doesn't (documented in
// docs/sigma_keymaps.md): home-row mods, dedicated keypad / mouse layers, and
// per-key RGB that colours every key by what it types.

// _MOUSE rides above the shared _QWERTY/_FN pair from users/sigma/sigma.h.
enum moonlander_layers {
    _MOUSE = _FN + 1,
};

// The two big thumb keys. Hold either -> _FN (momentary); press both together
// -> switch to _MOUSE; on _MOUSE, either one -> back to _QWERTY. The state
// machine lives in process_record_keymap() below.
enum moonlander_keycodes {
    TH_FNL = SIGMA_SAFE_RANGE, // left big thumb
    TH_FNR,                    // right big thumb
};

// Home-row mods: tap = the letter, hold = a modifier. Order matches the Oryx
// sigma-coding config this board grew out of: Ctrl / Alt / GUI / Shift running
// pinky -> index, mirrored across the two hands.
#define HR_A  LCTL_T(KC_A)
#define HR_S  LALT_T(KC_S)
#define HR_D  LGUI_T(KC_D)
#define HR_F  LSFT_T(KC_F)
#define HR_J  RSFT_T(KC_J)
#define HR_K  RGUI_T(KC_K)
#define HR_L  RALT_T(KC_L)
#define HR_SC RCTL_T(KC_SCLN)

// Home rows with the mods folded in, shaped like SIGMA_ASD_L/R (5 keys each)
// so they drop straight into the LAYOUT the same way the other rows do.
#define SIGMA_HOME_L HR_A, HR_S, HR_D, HR_F, KC_G
#define SIGMA_HOME_R KC_H, HR_J, HR_K, HR_L, HR_SC

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * _QWERTY - as many keys as possible sit directly here.
     *
     * ,--------------------------------------------.       ,--------------------------------------------.
     * |  `   | 1 | 2 | 3 | 4 | 5 | Home |          | PgUp | 6 | 7 | 8 | 9 | 0 |  -   |
     * |  =   | Q | W | E | R | T | End  |          | PgDn | Y | U | I | O | P |  \   |
     * | Caps | A | S | D | F | G | Del  |          | Bspc | H | J | K | L | ; |  '   |   (A-F/J-; = home-row mods)
     * | LSft | Z | X | C | V | B |------.          |------| N | M | , | . | / | RSft |
     * | Hypr | ( | [ | { | < | Fn |                | Fn | > | } | ] | ) | Hyp+ |
     * `----------------------'   ,-----------.        ,-----------.  `----------------------'
     *                           |Spc|Bsp|Esc |        |Del|Tab|Ent|
     *                           `-----------'          `-----------'
     * (both Fn thumbs: hold = _FN, both together = switch to _MOUSE, either
     *  returns from _MOUSE to _QWERTY.)
     */
    [_QWERTY] = KMAP(
        KC_GRV,  SIGMA_NUM_L,          KC_HOME,        KC_PGUP, SIGMA_NUM_R,          KC_MINS,
        KC_EQL,  SIGMA_QWE_L,          KC_END,         KC_PGDN, SIGMA_QWE_R,          KC_BSLS,
        KC_CAPS, SIGMA_HOME_L,         KC_DEL,         KC_BSPC, SIGMA_HOME_R,         KC_QUOT,
        KC_LSFT, SIGMA_ZXC_L,                                   SIGMA_ZXC_R,          KC_RSFT,
        SIGMA_HYPER, KC_LPRN, KC_LBRC, KC_LCBR, KC_LABK, TH_FNL,   TH_FNR, KC_RABK, KC_RCBR, KC_RBRC, KC_RPRN, SIGMA_HYPER_S,
        KC_SPC,  KC_BSPC, KC_ESC,                                        KC_DEL,  KC_TAB,  KC_ENT
    ),

    /*
     * _FN - arrows as an inverted-T under the index finger (R=up, D/F/G =
     * left/down/right), media / volume, and an aligned right-hand keypad (no
     * symbols). 0 sits below the 2; the right thumb carries Enter and dot.
     * Bootloader / NKRO are not here -- they live on _MOUSE.
     *
     *  F11  F1  F2  F3  F4  F5                    F6  F7  F8  F9  F10  F12
     *       Prv Ply Nxt Up                         7   8   9   /   *   Num
     *       Vo- Vo+ Lt  Dn  Rt                      4   5   6   -   +
     *       Mut Br- Br+ RB+ RB-                     1   2   3
     *                                                   0
     *  thumbs:                                 Enter  .
     */
    [_FN] = KMAP(
        KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
        _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_UP,   _______, _______,    _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_SLASH,    KC_KP_ASTERISK, KC_NUM,
        _______, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RGHT, _______,    _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_MINUS,    KC_KP_PLUS,     _______,
        _______, KC_MUTE, KC_BRID, KC_BRIU, SIGMA_BL_VALU, SIGMA_BL_VALD,   KC_KP_1, KC_KP_2, KC_KP_3, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,   _______, KC_KP_0, _______, _______, _______, _______,
        _______, _______, _______,                                        KC_KP_ENTER, KC_KP_DOT, _______
    ),

    /*
     * _MOUSE - pointer control. Movement on the left R/D/F/G inverted-T and the
     * wheel on a mirrored H/J/K/U inverted-T on the right (U=up, H/J/K =
     * left/down/right); mouse buttons on both thumb arcs. Reached by pressing
     * both big thumbs together; either thumb returns to _QWERTY. Bootloader (B)
     * and NKRO (N) live here.
     */
    [_MOUSE] = KMAP(
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, MS_UP,   _______, _______,    _______, _______, MS_WHLU, _______, _______, _______, _______,
        _______, _______, _______, MS_LEFT, MS_DOWN, MS_RGHT, _______,    _______, MS_WHLL, MS_WHLD, MS_WHLR, _______, _______, _______,
        _______, _______, _______, _______, _______, MD_BOOT,    NK_TOGG, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,
        MS_BTN1, MS_BTN2, MS_BTN3,                                        MS_BTN1, MS_BTN2, MS_BTN3
    ),
};

// ---------------------------------------------------------------------------
// Per-key RGB by keycode category
//
// Every key lights by what it *does* on the active layer:
//   letters        blue       symbols        red
//   home-row mods  dark blue  function keys  yellow
//   numbers        green      layer keys     magenta
//   space cluster  cyan       system keys    orange
//   navigation     pink       other special  purple
// (space cluster = Space/Enter/Tab/Backspace; navigation = arrows, Home/End,
// PgUp/PgDn; system = bootloader, NKRO & other magic toggles, and the
// RGB-matrix lighting controls. Home-row mods share the letter hue but a
// fraction of the brightness, so they read as a darker blue.)
//
// Transparent / no-op keys stay dark, so a non-base layer only lights the keys
// it actually defines. Colours are read back out of the keymap itself, so they
// can never drift out of sync with the layout.
// ---------------------------------------------------------------------------

// Hues match QMK's named HSV_* values (color.h).
enum category_hue {
    HUE_LETTER   = 170, // blue
    HUE_HOMEROW  = 170, // blue (same hue as letters; dimmed by VAL_HOMEROW_PCT)
    HUE_NUMBER   = 85,  // green
    HUE_SYMBOL   = 0,   // red
    HUE_FUNCTION = 43,  // yellow
    HUE_SPACE    = 128, // cyan
    HUE_NAV      = 234, // pink
    HUE_LAYER    = 213, // magenta
    HUE_SYSTEM   = 21,  // orange
    HUE_SPECIAL  = 191, // purple
};

// Home-row mods keep the letter hue at full saturation but are dimmed to this
// fraction of the active brightness, giving a distinct darker blue.
#define VAL_HOMEROW_PCT 40

typedef enum {
    CAT_OFF,
    CAT_LETTER,
    CAT_HOMEROW,
    CAT_NUMBER,
    CAT_SYMBOL,
    CAT_FUNCTION,
    CAT_SPACE,
    CAT_NAV,
    CAT_LAYER,
    CAT_SYSTEM,
    CAT_SPECIAL,
} key_category_t;

static key_category_t classify_keycode(uint16_t kc) {
    // Layer-switch keys (MO / TG / TO / TT / OSL / DF / LM) plus the custom
    // thumb Fn keys: own colour. Test before unwrapping tap keycodes so a plain
    // layer key lands here.
    if (kc == TH_FNL || kc == TH_FNR ||
        IS_QK_MOMENTARY(kc) || IS_QK_TOGGLE_LAYER(kc) || IS_QK_TO(kc) ||
        IS_QK_LAYER_TAP_TOGGLE(kc) || IS_QK_ONE_SHOT_LAYER(kc) ||
        IS_QK_DEF_LAYER(kc) || IS_QK_LAYER_MOD(kc)) {
        return CAT_LAYER;
    }

    // System / firmware control: bootloader, NKRO & other magic toggles, and
    // the RGB-matrix lighting controls (RM_* / SIGMA_BL_*).
    if (kc == QK_BOOT || kc == MD_BOOT || IS_QK_MAGIC(kc) || IS_RGB_MATRIX_KEYCODE(kc)) {
        return CAT_SYSTEM;
    }

    // Home-row mods (mod-taps) get their own paler blue -- test before
    // unwrapping so every A/S/D/F/J/K/L/; mod-tap lands here regardless of the
    // key it taps.
    if (IS_QK_MOD_TAP(kc)) {
        return CAT_HOMEROW;
    }

    // Layer-taps: colour by the key they tap.
    if (IS_QK_LAYER_TAP(kc)) {
        kc = QK_LAYER_TAP_GET_TAP_KEYCODE(kc);
    }

    // Shifted punctuation (S(KC_1)=KC_EXLM, KC_LPRN, KC_LABK, ...) -> symbol.
    if (kc >= QK_LSFT && kc <= (QK_LSFT | 0xFF)) {
        return CAT_SYMBOL;
    }

    if (kc == KC_NO || kc == KC_TRANSPARENT) return CAT_OFF;
    if (kc >= KC_A && kc <= KC_Z)            return CAT_LETTER;
    if (kc >= KC_1 && kc <= KC_0)            return CAT_NUMBER;   // 1..9 0
    if (kc >= KC_KP_1 && kc <= KC_KP_0)      return CAT_NUMBER;   // keypad digits
    if (kc >= KC_F1 && kc <= KC_F12)         return CAT_FUNCTION; // F1..F12
    if (kc >= KC_F13 && kc <= KC_F24)        return CAT_FUNCTION; // F13..F24
    // Navigation: arrows, Home/End, PgUp/PgDn (HID 0x4A..0x52) but not Delete.
    if (kc >= KC_HOME && kc <= KC_UP && kc != KC_DELETE) return CAT_NAV;

    switch (kc) {
        // "Space" commands: whitespace / line editing on the thumb cluster.
        case KC_SPC: case KC_ENT: case KC_TAB: case KC_BSPC: case KC_KP_ENTER:
            return CAT_SPACE;

        // Punctuation and keypad operators.
        case KC_MINUS: case KC_EQUAL: case KC_LBRC: case KC_RBRC:
        case KC_BSLS:  case KC_NUHS:  case KC_SCLN: case KC_QUOT:
        case KC_GRAVE: case KC_COMMA: case KC_DOT:  case KC_SLASH: case KC_NUBS:
        case KC_KP_SLASH: case KC_KP_ASTERISK: case KC_KP_MINUS:
        case KC_KP_PLUS:  case KC_KP_DOT:
            return CAT_SYMBOL;
    }
    return CAT_SPECIAL;
}

static uint8_t category_hue(key_category_t cat) {
    switch (cat) {
        case CAT_LETTER:   return HUE_LETTER;
        case CAT_HOMEROW:  return HUE_HOMEROW;
        case CAT_NUMBER:   return HUE_NUMBER;
        case CAT_SYMBOL:   return HUE_SYMBOL;
        case CAT_FUNCTION: return HUE_FUNCTION;
        case CAT_SPACE:    return HUE_SPACE;
        case CAT_NAV:      return HUE_NAV;
        case CAT_LAYER:    return HUE_LAYER;
        case CAT_SYSTEM:   return HUE_SYSTEM;
        default:           return HUE_SPECIAL;
    }
}

static uint8_t category_value(key_category_t cat, uint8_t base) {
    // Home-row mods are dimmed to a fraction of the active brightness -> darker.
    if (cat == CAT_HOMEROW) {
        return (uint8_t)((uint16_t)base * VAL_HOMEROW_PCT / 100);
    }
    return base;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
#ifdef ORYX_ENABLE
    // Oryx / Keymapp is painting the LEDs itself over webHID -- don't fight it.
    if (rawhid_state.rgb_control) {
        return false;
    }
#endif

    uint8_t layer = get_highest_layer(layer_state);
    uint8_t val   = rgb_matrix_get_val(); // let RM_VALU/VALD keep working

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led = g_led_config.matrix_co[row][col];
            if (led == NO_LED || led < led_min || led >= led_max) {
                continue;
            }

            keypos_t       pos = {.col = col, .row = row};
            key_category_t cat = classify_keycode(keymap_key_to_keycode(layer, pos));
            if (cat == CAT_OFF) {
                rgb_matrix_set_color(led, 0, 0, 0);
            } else {
                HSV hsv = {category_hue(cat), 255, category_value(cat, val)};
                RGB rgb = hsv_to_rgb(hsv);
                rgb_matrix_set_color(led, rgb.r, rgb.g, rgb.b);
            }
        }
    }
    return false;
}

// Thumb Fn keys (TH_FNL / TH_FNR). Hold either -> _FN (momentary). Press both
// together -> switch to the _MOUSE layer (persistent). While on _MOUSE, either
// thumb returns to _QWERTY. process_record_user() in users/sigma dispatches
// here for keymap-specific keycodes.
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    static bool l_held = false, r_held = false, mouse_mode = false;

    if (keycode != TH_FNL && keycode != TH_FNR) {
        return true;
    }

    bool *self = (keycode == TH_FNL) ? &l_held : &r_held;

    if (record->event.pressed) {
        *self = true;
        if (mouse_mode) {
            // On the mouse layer, either thumb returns to the base layer.
            layer_off(_MOUSE);
            mouse_mode = false;
        } else if (l_held && r_held) {
            // Both thumbs together -> switch to the mouse layer.
            layer_off(_FN);
            layer_on(_MOUSE);
            mouse_mode = true;
        } else {
            // A single thumb -> momentary _FN.
            layer_on(_FN);
        }
    } else {
        *self = false;
        if (!mouse_mode && !l_held && !r_held) {
            layer_off(_FN);
        }
    }
    return false;
}

void keyboard_post_init_user(void) {
    // Make sure the matrix is on so the category colours are visible at boot.
    rgb_matrix_enable_noeeprom();
}
