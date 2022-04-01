/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

//
// lcd/dogm/status/cutter.h - Status Screen Laser / Spindle bitmaps
//

#define STATUS_CUTTER_WIDTH 24
#define STATUS_CUTTER_X     80

#if ENABLED(LASER_FEATURE)
  const unsigned char status_cutter_bmp[] PROGMEM = {
    B00000000,B00001000,B00000000,
    B00000000,B00001000,B00000000,
    B00000000,B00001000,B00000000,
    B00000000,B00001000,B00000000,
    B00000000,B00101010,B00000000,
    B00000000,B00011100,B00000000,
    B00000000,B01111111,B00000000,
    B00000000,B00011100,B00000000,
    B00000000,B00101010,B00000000,
    B00000000,B00001000,B00000000,
    B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000
    };
  #ifdef STATUS_CUTTER_ANIM
    const unsigned char status_cutter_on_bmp[] PROGMEM = {
      B00000000,B00001000,B00000000,
      B00000001,B00001000,B01000000,
      B00000000,B10001000,B10000000,
      B00000000,B01001001,B00000000,
      B00000000,B00101010,B00000000,
      B00000000,B00011100,B00000000,
      B00000011,B11111111,B11100000,
      B00000000,B00011100,B00000000,
      B00000000,B00101010,B00000000,
      B00000000,B01001001,B00000000,
      B00000000,B10001000,B10000000,
      B00000001,B00001000,B01000000
    };
  #endif
#else
  const unsigned char status_cutter_bmp[] PROGMEM = {
    B00000001,B11111110,B10000000,
    B00000000,B11000000,B00000000,
    B00000001,B10000000,B10000000,
    B00000001,B00000000,B10000000,
    B00000001,B11111100,B10000000,
    B00000000,B11100000,B00000000,
    B00000001,B11000000,B10000000,
    B00000000,B10000001,B00000000,
    B00000000,B01111010,B00000000,
    B00000000,B00110100,B00000000,
    B00000000,B00011000,B00000000,
    B00000000,B00000000,B00000000
  };
  #ifdef STATUS_CUTTER_ANIM
    const unsigned char status_cutter_on_bmp[] PROGMEM = {
      B00000001,B11111110,B10000000,
      B00000000,B11000000,B00000000,
      B00000001,B10000000,B10000000,
      B00000001,B00000000,B10000000,
      B00000001,B11111100,B10000000,
      B00000000,B11100000,B00000000,
      B00000001,B11000000,B10000000,
      B00000000,B10000001,B00000000,
      B00000000,B01111010,B00000000,
      B00000000,B00110100,B00000000,
      B00000000,B00011000,B00000000,
      B00000000,B00000000,B00000000
    };
  #endif
#endif
