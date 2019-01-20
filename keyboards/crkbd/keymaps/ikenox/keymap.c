#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "oled.h"
#endif

#include "edvorakjp.h"

/*
 * enum custom_keycodes {
 *   KC_LOCK = NEW_SAFE_RANGE,
 * };
 */

#define KC_ KC_TRNS

#define KC_TMB1 LGUI_T(KC_TAB)
#define KC_TMB2 LSFT_T(KC_SPC)
#define KC_TMB3 TD(TD_LOWER) // act as LOWER when hold, as KC_LANG2(=English) when tapped
#define KC_TMB4 TD(TD_RAISE) // act as RAISE when hold, as KC_LANG1(=Japanese) when tapped
#define KC_TMB5 RCTL_T(KC_BSPC)
#define KC_TMB6 RALT_T(KC_ENT)
#define KC_TMB7 KC_DEL
#define KC_RGB_TOG RGB_TOG
#define KC_TMB8 RALT(KC_ENT)
#define KC_TMB9 LGUI(KC_TAB)
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_GUIKN GUI_T(KC_LANG1)
#define KC_CTLSP LCTL(KC_SPC)

#define KC_LOWER MO(_LOWER)
#define KC_RAISE MO(_RAISE)

#define KC_ALTKN ALT_T(KC_LANG1)

#define KC_RAENT KC_ENT
#define KC_LASPC KC_SPC

#define KC_RSBSL RSFT_T(KC_BSLS)
#define KC_RSSLS RSFT_T(KC_SLSH)

#define KC_RST  RESET
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_EDJP EDVORAK
#define KC_QWER QWERTY

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_EDVORAK] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     ESC ,QUOT,COMM,DOT , P  , Y  ,             F  , G  , S  , R  , W  ,BSLS,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
    CTLTB, A  , O  , E  , I  , U  ,             D  , M  , T  , N  , B  ,MINS,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     LSFT,SCLN, Q  , V  , Z  , X  ,             H  , J  , K  , L  , C ,RSSLS,
  //`----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                      GUIEI,RAISE,LASPC,  RAENT,LOWER,ALTKN \
  //                    `----+----+----' `----+----+----'
  ),

  [_QWERTY] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,             Y  , U  , I  , O  , P  ,MINS,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
    CTLTB, A  , S  , D  , F  , G  ,             H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,             N  , M  ,COMM,DOT ,SLSH,RSBSL,
  //`----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                      GUIEI,RAISE,LASPC,  RAENT,LOWER,ALTKN \
  //                    `----+----+----' `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     TILD,EXLM, AT ,HASH, DLR,PERC,            AMPR,ASTR,LPRN,LCBR,LBRC,UNDS,\
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
      GRV, 1  , 2  , 3  , 4  , 5  ,            PLUS, EQL,RPRN,RCBR,RBRC,PIPE,\
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     CIRC, 6  , 7  , 8  , 9  , 0  ,                ,BSPC, LT , GT ,    ,    ,\
  //`----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                      GUIEI,RAISE,LASPC,  RAENT,LOWER,ALTKN \
  //                    `----+----+----' `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     TILD,EXLM, AT ,HASH, DLR,PERC,            AMPR,ASTR,LPRN,LCBR,LBRC,UNDS,\
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
      GRV, 1  , 2  , 3  , 4  , 5  ,            PLUS, EQL,RPRN,RCBR,RBRC,PIPE,\
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     CIRC, 6  , 7  , 8  , 9  , 0  ,                ,BSPC, LT , GT ,    ,    ,\
  //`----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                      GUIEI,RAISE,LASPC,  RAENT,LOWER,ALTKN \
  //                    `----+----+----' `----+----+----'
  ),

  [_ADJUST] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,    ,    ,   ,     ,   ,                 ,    ,   ,    ,    ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,    ,    ,QWER,WIN ,RST ,            RTOG,MAC ,EDJP,    ,    ,    ,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                ,    ,    ,    ,    ,RGB_TOG,
  //`----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                             ,    ,    ,      ,    ,
  //                    `----+----+----' `----+----+----'
  )
};

#ifdef SSD1306OLED
void matrix_init_keymap(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  iota_gfx_init(!has_usb());   // turns on the display
}

void matrix_scan_user(void) {
  iota_gfx_task();  // this is what updates the display continuously
}
#endif

#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
uint32_t layer_state_set_keymap(uint32_t state) {
  //switch (biton32(state)) {
  //  case _LOWER:
  //    rgblight_sethsv_noeeprom_goldenrod();
  //    break;
  //  case _RAISE:
  //    rgblight_sethsv_noeeprom_turquoise();
  //    break;
  //  case _ADJUST:
  //    rgblight_sethsv_noeeprom_springgreen();
  //    break;
  //  default: //  for any other layers, or the default layer
  //    //rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT + 3);
  //    //rgblight_sethsv_noeeprom_red();
  //    rgblight_sethsv_noeeprom_white();
  //    break;
  //}
  return state;
}
#endif


