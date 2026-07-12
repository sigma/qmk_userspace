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
#pragma once

// Home-row-mod tuning. The A/S/D/F and J/K/L/; keys are mod-taps, so the
// timing decides how readily a hold becomes a modifier. Tweak to taste.
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD          // nested tap inside the term resolves as a hold
#define QUICK_TAP_TERM 0         // a quick re-press+hold is the modifier, not a repeated letter

// The per-key category colours are painted every frame in
// rgb_matrix_indicators_advanced_user(); keep a calm solid base underneath so
// brightness (RM_VALU / RM_VALD) behaves predictably.
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR

// Go dark while the host is asleep: on USB suspend the matrix renders
// RGB_MATRIX_NONE, which also gates off rgb_matrix_indicators_advanced_user()
// (rgb_matrix_task only paints indicators when the effect is non-zero), so the
// semantic highlighting turns off too. Lights return on wake.
#define RGB_MATRIX_SLEEP
// RGB_MATRIX_SLEEP only fires on a real USB suspend (full system sleep); merely
// idling -- screensaver, the display sleeping -- keeps the keyboard powered, so
// the lights would otherwise stay on. Also turn the LEDs off after a stretch of
// no keyboard input (any keypress restores them instantly).
#define RGB_MATRIX_TIMEOUT 300000   // 5 minutes of keyboard inactivity

// Full MIDI keycode set (note/octave/velocity/transpose/...) for the _MIDI
// layer; MIDI_ENABLE is set in rules.mk.
#define MIDI_ADVANCED

// Pairing/identity string the zsa/oryx module reports to Oryx & Keymapp.
// Mainline's moonlander doesn't set one, and we omit the zsa/defaults module
// (it would clash with moonlander.h's TOGGLE_LAYER_COLOR / LED_LEVEL), so
// define it here.
#define SERIAL_NUMBER "sigma/moonlander"
