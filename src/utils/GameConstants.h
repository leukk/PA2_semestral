#pragma once

// Game config delimiters
#define CONF_SCENE_DELIM "#SCENE"
#define CONF_OBJECT_DELIM "#OBJECT"
#define CONF_PARAM_START_DELIM "--"
#define CONF_PARAM_END_DELIM ' '
#define CONF_COMMENT_DELIM "//"
#define CONF_VALUE_DELIM '"'
#define CONF_PREFIX_DELIM "_"

// Shared data index
#define SHARED_DATA (-1)

// Global parameter keywords
#define PARAM_UPDATE_RATE "--update-rate"
#define PARAM_GAME_WIN_Y "--game-win-y"
#define PARAM_GAME_WIN_X "--game-win-x"
#define PARAM_TEXT_WIN_Y "--text-win-y"
#define PARAM_MENU_SCENE "--menu-scene"
#define PARAM_HUB_SCENE "--hub-scene"
#define PARAM_CREATE_BUFF_TOKENS "--buff-tokens"
#define PARAM_ITEM_EQUIP_LIMIT "--item-limit"

// Scene parameter keywords
#define PARAM_COLLISION "--collision-chars"
#define PARAM_PLAYER_DAMAGE "--player-damage-chars"
#define PARAM_PLAYER_BULLET "--player-bullet-char"

// Common object parameter keywords
#define PARAM_OBJECT_COMMON_POSITION "--position"
#define PARAM_OBJECT_COMMON_ACTIVE "--active"
#define PARAM_OBJECT_COMMON_TYPE "--type"
#define PARAM_OBJECT_COMMON_TAGS "--tags"

// Object type keywords
#define OBJECT_TEXT "text"
#define OBJECT_MENU "menu"
#define OBJECT_TRIGGER "trigger"
#define OBJECT_PLAYER "player"
#define OBJECT_ENEMY "enemy"
#define OBJECT_MAIN_MENU_MGR "main-menu-manager"
#define OBJECT_HUB_MGR "hub-manager"
#define OBJECT_LEVEL_MGR "level-manager"

// Buffs indexes
#define EFFECT_CHANGE_SPEED 0
#define EFFECT_CHANGE_LIVES 1
#define EFFECT_CHANGE_RANGE 2

// Level / item param prefix keywords
#define PARAM_LEVEL_TITLE_PREFIX "--level-title-"
#define PARAM_LEVEL_DESCRIPTION_PREFIX "--level-description-"
#define PARAM_LEVEL_SCENE_INDEX_PREFIX "--level-scene-"
#define PARAM_LEVEL_REWARD_PREFIX "--level-reward-"
#define PARAM_ITEM_TITLE_PREFIX "--item-title-"
#define PARAM_ITEM_PRICE_PREFIX "--item-price-"
#define PARAM_ITEM_EFFECT_PREFIX "--item-effect-"
#define PARAM_ITEM_EFFECT_CHANGE_PREFIX "--item-effect-change-"


// MainMenuManager dependencies keywords
#define TAG_M_MENU_MAIN_UI "main-ui"
#define TAG_M_MENU_MENU_OBJ "main-menu"
#define TAG_M_MENU_INFO_OBJ "info-text"
#define TAG_M_MENU_NEW_GAME_UI "new-game-ui"
#define TAG_M_MENU_BUFF_MENU_OBJ "buff-menu"
#define TAG_M_MENU_ROLE_MENU_OBJ "role-menu"

// HubManager dependencies keywords
#define TAG_HUB_BUY_TRIGGER "buy-zone"
#define TAG_HUB_EQUIP_TRIGGER "equip-zone"
#define TAG_HUB_EXIT_TRIGGER "exit-zone"
#define TAG_HUB_LEVEL_TRIGGER "enter-level-zone"
#define TAG_HUB_SHOP_UI "shop-ui"
#define TAG_HUB_EQUIP_UI "equip-ui"
#define TAG_HUB_DEFAULT_UI "default-ui"
#define TAG_HUB_SHOP_MENU "shop-menu"
#define TAG_HUB_EQUIP_MENU "equip-menu"

// LevelManager dependencies keywords
#define TAG_LEVEL_ABORT_TRIGGER "abort-zone"
#define TAG_LEVEL_SUCCESS_TRIGGER "success-zone"
#define TAG_LEVEL_COLLECT_OBJ "collect"

// Shared tag keywords
#define TAG_PLAYER "player"
#define TAG_ENEMY "enemy"

// SPACE keypress
#define KEY_SPACE 32





