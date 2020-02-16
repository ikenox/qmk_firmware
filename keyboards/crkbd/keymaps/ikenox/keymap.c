#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC_ KC_TRNS

#define KC_TMB1 LGUI_T(KC_TAB)
#define KC_TMB2 LSFT_T(KC_SPC)
#define KC_TMB5 RCTL_T(KC_BSPC)
#define KC_TMB6 RALT_T(KC_ENT)
#define KC_TMB7 KC_DEL
#define KC_RGB_TOG RGB_TOG
#define KC_RGB_MOD RGB_MOD
#define KC_TMB8 RALT(KC_ENT)
#define KC_TMB9 LGUI(KC_TAB)
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_GUIKN GUI_T(KC_LANG1)
#define KC_CTLSP LCTL(KC_SPC)
#define KC_RGB_HUI RGB_HUI
#define KC_RGB_VAI RGB_VAI
#define KC_RGB_VAD RGB_VAD

#define KC_LOWER MO(_LOWER)
#define KC_RAISE MO(_RAISE)

#define KC_ALTKN ALT_T(KC_LANG1)

#define KC_RAENT KC_ENT
#define KC_LASPC KC_SPC

#define KC_RSBSL RSFT_T(KC_BSLS)
#define KC_RSSLS RSFT_T(KC_SLSH)

#define KC_RST  RESET
#define KC_DBUG DEBUG

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc(
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,             Y  , U  , I  , O  , P  ,MINS,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     LCTL, A  , S  , D  , F  , G  ,             H  , J  , K  , L  ,SCLN,QUOT,
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
     RST  ,    ,    ,   ,     ,   ,                 ,    ,   ,    ,RGB_VAI, RGB_HUI,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,               ,    ,    ,    ,RGB_VAD,RGB_MOD,
  //|----+----+----+----+----+----|           |----+----+----+----+----+----|
     DBUG ,    ,    ,    ,    ,    ,                ,    ,    ,    ,    ,RGB_TOG,
  //`----+----+----+----+----+----+----| |----+----+----+----+----+----+----'
                             ,    ,    ,      ,    ,
  //                    `----+----+----' `----+----+----'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}
