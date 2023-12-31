//
//  GameConfig.h
//  Combine Number
//
//  Created by Harry Nguyen on 12/7/23.
//

#ifndef GameConfig_h
#define GameConfig_h

#define WIDTH_HEIGHT_CELL 98
#define TOTAL_ROW_CELL 6
#define TOTAL_COLUMN_CELL 6
#define MIN_SAME_VALUE 3
#define DEFAULT_SUGGESTION_TIME 2
#define DEFAULT_UNDO_TIME 3
#define DEFAULT_REMOVE_NUMBER_TIME 3
#define CIRCLE_RADIUS 8.0
#define DROP_DOWN_ANIMATION_SPEED 1800.0 // pixels per second
#define TOUCH_ANIMATION_SPEED 40.0 // pixels per second
#define TOUCH_ANIMATION_DELTA 4.0
#define MAX_GUIDE_NUMBER_SHOW_ON_SCREEN 5

#define FONT_LABEL_NAME "ManilaSansBld.otf"
#define FONT_SIZE_TILE_GAME_LABEL 54
#define FONT_SIZE_GAME_OVER_LABEL 54
#define FONT_SIZE_EARN_MAXIMUM_LABEL_IN_HOME_SCENE 44
#define FONT_SIZE_WARNING_LABEL 36
#define FONT_SIZE_EARN_MAXIMUM_LABEL_IN_GAME_SCENE 36
#define FONT_SIZE_NUMBER_LABEL 36
#define FONT_SIZE_GUIDE_LABEL 32

#define LINE_WIDTH 4.0

#define DELAY_WARNING_LABEL_DISAPPEAR 1.0
#define TIME_RUN_MESSAGE_LABEL_ANIMATION 0.3
#define DELAY_DROP_NUMBER 0.05
#define TIME_RUN_ANIMATION 0.2

#define GAME_OVER_MOVE_TO_DURATION 0.2
#define GUIDE_LINE_MOVE_TO_DURATION 1.5

#define NUMBER_DISABLE_OPACITY 50

#define HEIGHT_TOP_POP_UP_LAYER 168.0
#define HEIGHT_BOTTOM_POP_UP_LAYER 148.0

#define GUIDE_TITLE_TEXT "Combines 3 or more numbers to"
#define GUIDE_SUB_TITLE_TEXT "create a bigger number."

#define BACK_BUTTON_NAME "back_button.png"
#define PLAY_BUTTON_NAME "play_button.png"
#define RESET_BUTTON_NAME "reset_button.png"
#define SOUND_BUTTON_ON_NAME "sound-on-icon.png"
#define SOUND_BUTTON_OFF_NAME "sound-off-icon.png"
#define HAPTIC_BUTTON_ON_NAME "phone-vibration-on.png"
#define HAPTIC_BUTTON_OFF_NAME "phone-vibration-off.png"
#define LIGHT_ON_BUTTON_NAME "light-on-icon.png"
#define EARN_POINT_ICON_NAME "earn_point_icon.png"
#define MAXIMUM_NUMBER_ICON_NAME "maximum_number_icon.png"
#define GUIDE_ICON_NAME "guide_icon.png"
#define UNDO_ICON_NAME "undo-icon.png"
#define REMOVE_NUMBER_ICON_NAME "hammer-icon.png"
#define TROPHY_ICON_NAME "trophy-icon.png"

#define TITLE_GAME "Combine Number"

#define KEY_HIGHEST_EARN_POINT "KEY_HIGHEST_EARN_POINT"
#define KEY_HIGHEST_NUMBER "KEY_HIGHEST_NUMBER"
#define KEY_FRIST_TIME_OPEN_GAME "KEY_FRIST_TIME_OPEN_GAME"
#define KEY_SOUND_GAME "KEY_SOUND_GAME"
#define KEY_HAPTIC_GAME "KEY_HAPTIC_GAME"

#define AD_BANNER_ID "ca-app-pub-2381211844174227/3315056023"
#define AD_INTERSTITIAL_ID "ca-app-pub-2381211844174227/8375811011"

#define AD_GAME_OVER_KEY "AD_GAME_OVER_KEY "
#define AD_GAME_OVER_FREQUENCY 5

#define AD_OPEN_GAME_KEY "AD_OPEN_GAME_KEY"
#define AD_OPEN_GAME_FREQUENCY 8
#define EDIT_NUMBER_MESSAGE "TOUCH ANY NUMBER TO REMOVE"

enum {
  IDLE = 0,
  REVERT_ANIMATION_AFTER_TOUCH = 1,
  TOUCH_ANIMATION = 2,
} STATUS;

enum {
  LINE_TAG = 0,
  NUMBER_TAG = 1,
  GUIDE_ICON_TAG = 2,
} TAG;

enum {
  FIRST_TIME_OPEN = 0,
  CLICK_SUGGESTION = 1,
} GUIDE_LINE_CALLED;

enum {
  CLICK_BUTTON_SOUND = 0,
  TOUCH_NUMBER_SOUND = 1,
  REMOVE_NUMBER_SOUND = 2,
  INCREASE_NEW_NUMBER_SOUND = 3,
  GAME_OVER_SOUND = 4,
} SOUND_TAG;

#endif /* GameConfig_h */
