/**
 * MK4duo 3D Printer Firmware
 *
 * Based on Marlin, Sprinter and grbl
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 * Copyright (C) 2013 - 2016 Alberto Cotronei @MagoKimbra
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ULTRALCD_H
#define ULTRALCD_H

#if ENABLED(ULTRA_LCD)
  #if HAS(BUZZER)
    #include "buzzer.h"
  #endif

  #define BUTTON_EXISTS(BN) (defined(BTN_## BN) && BTN_## BN >= 0)
  #define BUTTON_PRESSED(BN) !READ(BTN_## BN)

  int lcd_strlen(const char* s);
  int lcd_strlen_P(const char* s);
  void lcd_update();
  void lcd_init();
  bool lcd_hasstatus();
  void lcd_setstatus(const char* message, const bool persist = false);
  void lcd_setstatuspgm(const char* message, const uint8_t level = 0);
  void lcd_setalertstatuspgm(const char* message);
  void lcd_reset_alert_level();
  bool lcd_detected(void);
  void lcd_kill_screen();
  void kill_screen(const char* lcd_msg);

  #if ENABLED(LCD_USE_I2C_BUZZER)
    void lcd_buzz(long duration, uint16_t freq);
  #endif

  #if ENABLED(LCD_PROGRESS_BAR) && PROGRESS_MSG_EXPIRE > 0
    void dontExpireStatus();
  #endif

  #if ENABLED(DOGLCD)
    extern int lcd_contrast;
    void set_lcd_contrast(int value);
  #elif ENABLED(SHOW_BOOTSCREEN)
    void bootscreen();
  #endif

  #define LCD_MESSAGEPGM(x) lcd_setstatuspgm(PSTR(x))
  #define LCD_ALERTMESSAGEPGM(x) lcd_setalertstatuspgm(PSTR(x))

  #define LCD_UPDATE_INTERVAL 100
  #define LCD_TIMEOUT_TO_STATUS 15000

  #if ENABLED(ULTIPANEL)
    extern volatile uint8_t buttons;  // the last checked buttons in a bit array.
    void lcd_buttons_update();
    void lcd_quick_feedback(); // Audible feedback for a button click - could also be visual
    bool lcd_clicked();
    void lcd_ignore_click(bool b = true);

    #if ENABLED(FILAMENT_CHANGE_FEATURE)
      void lcd_filament_change_show_message(FilamentChangeMessage message);
    #endif

  #else
    FORCE_INLINE void lcd_buttons_update() {}
  #endif

  extern int plaPreheatHotendTemp;
  extern int plaPreheatHPBTemp;
  extern int plaPreheatFanSpeed;
  extern int absPreheatHotendTemp;
  extern int absPreheatHPBTemp;
  extern int absPreheatFanSpeed;
  extern int gumPreheatHotendTemp;
  extern int gumPreheatHPBTemp;
  extern int gumPreheatFanSpeed;

  #if HAS(LCD_FILAMENT_SENSOR) || HAS(LCD_POWER_SENSOR)
    extern millis_t previous_lcd_status_ms;
  #endif

  bool lcd_blink();

  #if ENABLED(ULTIPANEL)
    #define BLEN_B 1
    #define BLEN_A 0
    #if BUTTON_EXISTS(ENC)
      // encoder click is directly connected
      #define BLEN_C 2
      #define EN_C (_BV(BLEN_C))
    #endif
    #if BUTTON_EXISTS(BACK)
      #define BLEN_D 3
      #define EN_D (_BV(BLEN_D))
    #endif
    #define EN_A (_BV(BLEN_A))
    #define EN_B (_BV(BLEN_B))
  #endif

  #if ENABLED(REPRAPWORLD_KEYPAD)

    #define REPRAPWORLD_BTN_OFFSET 0 // bit offset into buttons for shift register values

    #define BLEN_REPRAPWORLD_KEYPAD_F3     0
    #define BLEN_REPRAPWORLD_KEYPAD_F2     1
    #define BLEN_REPRAPWORLD_KEYPAD_F1     2
    #define BLEN_REPRAPWORLD_KEYPAD_DOWN   3
    #define BLEN_REPRAPWORLD_KEYPAD_RIGHT  4
    #define BLEN_REPRAPWORLD_KEYPAD_MIDDLE 5
    #define BLEN_REPRAPWORLD_KEYPAD_UP     6
    #define BLEN_REPRAPWORLD_KEYPAD_LEFT   7

    #define EN_REPRAPWORLD_KEYPAD_F3      (_BV(REPRAPWORLD_BTN_OFFSET + BLEN_REPRAPWORLD_KEYPAD_F3))
    #define EN_REPRAPWORLD_KEYPAD_F2      (_BV(REPRAPWORLD_BTN_OFFSET + BLEN_REPRAPWORLD_KEYPAD_F2))
    #define EN_REPRAPWORLD_KEYPAD_F1      (_BV(REPRAPWORLD_BTN_OFFSET + BLEN_REPRAPWORLD_KEYPAD_F1))
    #define EN_REPRAPWORLD_KEYPAD_DOWN    (_BV(REPRAPWORLD_BTN_OFFSET + BLEN_REPRAPWORLD_KEYPAD_DOWN))
    #define EN_REPRAPWORLD_KEYPAD_RIGHT   (_BV(REPRAPWORLD_BTN_OFFSET + BLEN_REPRAPWORLD_KEYPAD_RIGHT))
    #define EN_REPRAPWORLD_KEYPAD_MIDDLE  (_BV(REPRAPWORLD_BTN_OFFSET + BLEN_REPRAPWORLD_KEYPAD_MIDDLE))
    #define EN_REPRAPWORLD_KEYPAD_UP      (_BV(REPRAPWORLD_BTN_OFFSET + BLEN_REPRAPWORLD_KEYPAD_UP))
    #define EN_REPRAPWORLD_KEYPAD_LEFT    (_BV(REPRAPWORLD_BTN_OFFSET + BLEN_REPRAPWORLD_KEYPAD_LEFT))

    #define REPRAPWORLD_KEYPAD_MOVE_Z_DOWN  (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_F3)
    #define REPRAPWORLD_KEYPAD_MOVE_Z_UP    (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_F2)
    #define REPRAPWORLD_KEYPAD_MOVE_Y_DOWN  (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_DOWN)
    #define REPRAPWORLD_KEYPAD_MOVE_X_RIGHT (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_RIGHT)
    #define REPRAPWORLD_KEYPAD_MOVE_HOME    (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_MIDDLE)
    #define REPRAPWORLD_KEYPAD_MOVE_Y_UP    (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_UP)
    #define REPRAPWORLD_KEYPAD_MOVE_X_LEFT  (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_LEFT)

    #define REPRAPWORLD_KEYPAD_PRESSED      (buttons_reprapworld_keypad & ( \
                                              EN_REPRAPWORLD_KEYPAD_F3 | \
                                              EN_REPRAPWORLD_KEYPAD_F2 | \
                                              EN_REPRAPWORLD_KEYPAD_F1 | \
                                              EN_REPRAPWORLD_KEYPAD_DOWN | \
                                              EN_REPRAPWORLD_KEYPAD_RIGHT | \
                                              EN_REPRAPWORLD_KEYPAD_MIDDLE | \
                                              EN_REPRAPWORLD_KEYPAD_UP | \
                                              EN_REPRAPWORLD_KEYPAD_LEFT) \
                                            )

    #define LCD_CLICKED ((buttons & EN_C) || (buttons_reprapworld_keypad & EN_REPRAPWORLD_KEYPAD_F1))
  #elif ENABLED(NEWPANEL)
    #define LCD_CLICKED (buttons & EN_C)
  #endif

#elif DISABLED(NEXTION)

  FORCE_INLINE void lcd_update() {}
  FORCE_INLINE void lcd_init() {}
  FORCE_INLINE bool lcd_hasstatus() { return false; }
  FORCE_INLINE void lcd_setstatus(const char* message, const bool persist=false) {UNUSED(message); UNUSED(persist);}
  FORCE_INLINE void lcd_setstatuspgm(const char* message, const uint8_t level=0) {UNUSED(message); UNUSED(level);}
  FORCE_INLINE void lcd_buttons_update() {}
  FORCE_INLINE void lcd_reset_alert_level() {}
  FORCE_INLINE bool lcd_detected(void) { return true; }

  #define LCD_MESSAGEPGM(x) NOOP
  #define LCD_ALERTMESSAGEPGM(x) NOOP

#endif // ULTRA_LCD

#if ENABLED(SDSUPPORT) && ENABLED(SD_SETTINGS)
  extern void set_sd_dot();
  extern void unset_sd_dot();
#endif

#endif // ULTRALCD_H