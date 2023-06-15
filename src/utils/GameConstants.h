#pragma once

// Config parsing delimiters
#define CONF_SCENE_DELIM "#SCENE"
#define CONF_OBJECT_DELIM "#OBJECT"
#define CONF_PARAM_START_DELIM "--"
#define CONF_PARAM_END_DELIM ' '
#define CONF_COMMENT_DELIM "//"
#define CONF_VALUE_DELIM '"'
#define CONF_PREFIX_DELIM "_"

// Misc constants
#define SHARED_DATA (-1)
#define HIT_DIM_MS 300
#define BULLET_POOL_SIZE 50

// Global parameter keywords
#define PARAM_UPDATE_RATE "--update-rate"
#define PARAM_GAME_WIN_Y "--game-win-y"
#define PARAM_GAME_WIN_X "--game-win-x"
#define PARAM_TEXT_WIN_Y "--text-win-y"
#define PARAM_MENU_SCENE "--menu-scene"
#define PARAM_HUB_SCENE "--hub-scene"
#define PARAM_CREATE_BUFF_TOKENS "--buff-tokens"
#define PARAM_ITEM_EQUIP_LIMIT "--item-limit"
#define PARAM_PLAYER_SPAWN_POS "--player-spawn"

// Level / item param prefix keywords
#define PARAM_LEVEL_TITLE_PREFIX "--level-title-"
#define PARAM_LEVEL_DESCRIPTION_PREFIX "--level-description-"
#define PARAM_LEVEL_SCENE_INDEX_PREFIX "--level-scene-"
#define PARAM_LEVEL_REWARD_PREFIX "--level-reward-"
#define PARAM_ITEM_TITLE_PREFIX "--item-title-"
#define PARAM_ITEM_PRICE_PREFIX "--item-price-"
#define PARAM_ITEM_EFFECT_PREFIX "--item-effect-"
#define PARAM_ITEM_EFFECT_CHANGE_PREFIX "--item-effect-change-"

// Object type keywords
#define OBJECT_TEXT "text"
#define OBJECT_MENU "menu"
#define OBJECT_TRIGGER "trigger"
#define OBJECT_PLAYER "player"
#define OBJECT_ENEMY "enemy"
#define OBJECT_MAIN_MENU_MGR "main-menu-manager"
#define OBJECT_HUB_MGR "hub-manager"
#define OBJECT_LEVEL_MGR "level-manager"
#define OBJECT_BULLET_MGR "bullet-manager"

// SceneObject parameter keywords
#define PARAM_SCENE_OBJECT_POSITION "--position"
#define PARAM_SCENE_OBJECT_ACTIVE "--active"
#define PARAM_SCENE_OBJECT_TYPE "--type"
#define PARAM_SCENE_OBJECT_TAGS "--tags"
// DisplayObject parameter keywords
#define PARAM_DISPLAY_OBJECT_COLOR "--color"
#define PARAM_DISPLAY_OBJECT_CONTENTS "--contents"
// CharacterObject parameter keywords
#define PARAM_CHARACTER_LIVES "--lives"
#define PARAM_CHARACTER_COLLISION_CHARS "--collision-chars"
#define PARAM_CHARACTER_DAMAGE_CHARS "--damage-chars"
#define PARAM_CHARACTER_MOVE_DELAY "--move-delay"
#define PARAM_CHARACTER_SHOOT_DELAY "--shoot-delay"
#define PARAM_CHARACTER_SHOOT_RANGE "--shoot-range"
#define PARAM_CHARACTER_SHOOT_VELOCITY "--shoot-velocity"

// Trigger parameter keywords
#define PARAM_TRIGGER_SIZE "--trigger-size"
#define PARAM_TRIGGER_TARGET "--target-tag"

// Enemy parameter keywords
#define PARAM_ENEMY_MOVE_DIR "--move-direction"
#define PARAM_ENEMY_SHOOT_DIR "--shoot-direction"

// Buffs indexes
#define EFFECT_CHANGE_SPEED 0
#define EFFECT_CHANGE_LIVES 1
#define EFFECT_CHANGE_RANGE 2

// MainMenuManager dependencies keywords
#define TAG_M_MENU_MAIN_UI "main-ui"
#define TAG_M_MENU_MENU_OBJ "main-menu"
#define TAG_M_MENU_INFO_OBJ "info-text"
#define TAG_M_MENU_NEW_GAME_UI "new-game-ui"
#define TAG_M_MENU_BUFF_MENU_OBJ "buff-menu"
#define TAG_M_MENU_ROLE_MENU_OBJ "role-menu"

// HubManager dependencies tag keywords
#define TAG_HUB_BUY_TRIGGER "buy-zone"
#define TAG_HUB_EQUIP_TRIGGER "equip-zone"
#define TAG_HUB_EXIT_TRIGGER "exit-zone"
#define TAG_HUB_LEVEL_TRIGGER "enter-level-zone"
#define TAG_HUB_SHOP_UI "shop-ui"
#define TAG_HUB_EQUIP_UI "equip-ui"
#define TAG_HUB_DEFAULT_UI "default-ui"
#define TAG_HUB_SHOP_MENU "shop-menu"
#define TAG_HUB_EQUIP_MENU "equip-menu"

// LevelManager dependencies tag keywords
#define TAG_LEVEL_ABORT_TRIGGER "abort-zone"
#define TAG_LEVEL_SUCCESS_TRIGGER "success-zone"

// Shared tag keywords
#define TAG_PLAYER "player"

// SPACE keypress
#define KEY_SPACE 32
#define KEY_ABILITY 'c'

#define MAX_USER_INPUT_LENGTH 200






