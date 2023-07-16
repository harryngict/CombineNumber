//
//  GameConfig.h
//  Combine Number
//
//  Created by Harry Nguyen on 12/7/23.
//

#ifndef GameConfig_h
#define GameConfig_h

#define WIDTH_HEIGHT_CELL 116
#define TOTAL_ROW_CELL 5
#define TOTAL_COLUMN_CELL 6
#define MIN_SAME_VALUE 3
#define DEFAULT_SUGGESTION_TIME 3
#define CIRCLE_RADIUS 8.0
#define DROP_DOWN_ANIMATION_SPEED 1800.0 // pixels per second
#define TOUCH_ANIMATION_SPEED 40.0 // pixels per second
#define TOUCH_ANIMATION_DELTA 4.0

#define FONT_NAME_NUMBER_LABEL "ManilaSansBld.otf"
#define FONT_SIZE_TILE_GAME_LABEL 54
#define FONT_SIZE_GAME_OVER_LABEL 54
#define FONT_SIZE_EARN_MAXIMUM_LABEL_IN_HOME_SCENE 44
#define FONT_SIZE_EARN_MAXIMUM_LABEL_IN_GAME_SCENE 36
#define FONT_SIZE_NUMBER_LABEL 38
#define FONT_SIZE_GUIDE_LABEL 32

#define LINE_WIDTH 4.0

#define DELAY_DROP_NUMBER 0.05
#define TIME_RUN_ANIMATION 0.2

#define GAME_OVER_MOVE_TO_DURATION 0.2
#define GUIDE_LINE_MOVE_TO_DURATION 1.5

#define NUMBER_DISABLE_OPACITY 50

#define HEIGHT_GAME_OVER_LAYER 168.0
#define HEIGHT_TOP_MENU_LAYER 168.0
#define HEIGHT_GUIDE_POP_UP_LAYER 168.0

#define GUIDE_TITLE_TEXT "Combines 3 or more numbers to"
#define GUIDE_SUB_TITLE_TEXT "create a bigger number."

#define BACK_BUTTON_NAME "back_button.png"
#define PLAY_BUTTON_NAME "play_button.png"
#define RESET_BUTTON_NAME "reset_button.png"
#define LIGHT_ON_BUTTON_NAME "light-on-icon.png"
#define LIGHT_OFF_BUTTON_NAME "light-off-icon.png"
#define EARN_POINT_ICON_NAME "earn_point_icon.png"
#define MAXIMUM_NUMBER_ICON_NAME "maximum_number_icon.png"
#define GUIDE_ICON_NAME "guide_icon.png"

#define TITLE_GAME "Combine Number"

#define KEY_HIGHEST_EARN_POINT "KEY_HIGHEST_EARN_POINT"
#define KEY_HIGHEST_NUMBER "KEY_HIGHEST_NUMBER"
#define KEY_FRIST_TIME_OPEN_GAME "KEY_FRIST_TIME_OPEN_GAME"

#define AD_BANNER_ID "ca-app-pub-2381211844174227/3315056023"
#define AD_INTERSTITIAL_ID "ca-app-pub-2381211844174227/8375811011"

#define AD_GAME_OVER_KEY "AD_CLICK_GAME_OVER_KEY"
#define AD_GAME_OVER_FREQUENCY 6

#define AD_OPEN_GAME_KEY "AD_OPEN_GAME_KEY"
#define AD_OPEN_GAME_FREQUENCY 12


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

#endif /* GameConfig_h */
