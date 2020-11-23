/****************************************************************************
**
** Copyright (C) 2020 @scriptiot
**
**  EVM是一款通用化设计的虚拟机引擎，拥有语法解析前端接口、编译器、虚拟机和虚拟机扩展接口框架。
**  支持js、python、hml、lua等多种脚本语言，纯Ｃ开发，零依赖，支持主流 ROM > 50KB, RAM > 2KB的MCU;
**  自带垃圾回收（GC）先进的内存管理，采用最复杂的压缩算法，无内存碎片（大部分解释器都存在内存碎片）
**  Version : 1.0
**  Email   : scriptiot@aliyun.com
**  Website : https://github.com/scriptiot
**  Licence: MIT Licence
****************************************************************************/
#include "hml_lvgl_utils.h"

#define FONT(size) if (font_size == size){ \
                       return &lv_font_montserrat_##size; \
                   }

lv_style_t * lvgl_hml_obj_add_style(lv_obj_t * obj, evm_val_t * hml){
    lv_style_t * style = lv_mem_alloc(sizeof(lv_style_t));
    lv_style_init(style);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    lvgl_userdata * userdata = evm_malloc(sizeof(lvgl_userdata));
    userdata->style = style;
    userdata->hml_obj = hml;
    lv_obj_set_user_data(obj, userdata);
    return style;
}

lv_style_t * lvgl_hml_obj_get_style(lv_obj_t * obj){
    lvgl_userdata * userdata = (lvgl_userdata *) lv_obj_get_user_data(obj);
    return userdata->style;
}

evm_val_t * lvgl_get_hml_obj(lv_obj_t * obj){
    lvgl_userdata * userdata = (lvgl_userdata *) lv_obj_get_user_data(obj);
    return userdata->hml_obj;
}

lv_font_t * lvgl_hml_style_get_font_size(int font_size){
#if LV_FONT_MONTSERRAT_12
    FONT(12)
#endif
#if LV_FONT_MONTSERRAT_14
    FONT(14)
#endif
#if LV_FONT_MONTSERRAT_16
    FONT(16)
#endif
#if LV_FONT_MONTSERRAT_18
    FONT(18)
#endif
#if LV_FONT_MONTSERRAT_20
    FONT(20)
#endif
#if LV_FONT_MONTSERRAT_22
    FONT(22)
#endif
#if LV_FONT_MONTSERRAT_24
    FONT(24)
#endif
#if LV_FONT_MONTSERRAT_26
    FONT(26)
#endif
#if LV_FONT_MONTSERRAT_28
    FONT(28)
#endif
#if LV_FONT_MONTSERRAT_30
    FONT(30)
#endif
#if LV_FONT_MONTSERRAT_32
    FONT(32)
#endif
#if LV_FONT_MONTSERRAT_34
    FONT(34)
#endif
#if LV_FONT_MONTSERRAT_36
    FONT(36)
#endif
#if LV_FONT_MONTSERRAT_38
    FONT(38)
#endif
#if LV_FONT_MONTSERRAT_40
    FONT(40)
#endif
#if LV_FONT_MONTSERRAT_42
    FONT(42)
#endif
#if LV_FONT_MONTSERRAT_44
    FONT(44)
#endif
#if LV_FONT_MONTSERRAT_46
    FONT(46)
#endif
#if LV_FONT_MONTSERRAT_48
    FONT(48)
#endif
    return &lv_font_montserrat_14;
}

lv_opa_t lvgl_hml_style_get_opa(int opacity){
    opacity = 10 * opacity / 10 ;
    switch (opacity) {
        case 0: return LV_OPA_TRANSP;
        case 10: return LV_OPA_10;
        case 20: return LV_OPA_20;
        case 30: return LV_OPA_30;
        case 40: return LV_OPA_40;
        case 50: return LV_OPA_50;
        case 60: return LV_OPA_60;
        case 70: return LV_OPA_70;
        case 80: return LV_OPA_80;
        case 90: return LV_OPA_90;
        case 100: return LV_OPA_COVER;
        default:return LV_OPA_COVER;
    }
}

lv_color_t lvgl_hml_style_get_color(evm_val_t * v){
    if( !v ) return LV_COLOR_BLACK;
    if( evm_is_string(v)) {
        const char * s = evm_2_string(v);
        if( !strcmp(s, "white") ) return LV_COLOR_WHITE;
        if( !strcmp(s, "silver") ) return LV_COLOR_SILVER;
        if( !strcmp(s, "gray") ) return LV_COLOR_GRAY;
        if( !strcmp(s, "black") ) return LV_COLOR_BLACK;
        if( !strcmp(s, "red") ) return LV_COLOR_RED;
        if( !strcmp(s, "maroon") ) return LV_COLOR_MAROON;
        if( !strcmp(s, "yellow") ) return LV_COLOR_YELLOW;
        if( !strcmp(s, "olive") ) return LV_COLOR_OLIVE;
        if( !strcmp(s, "lime") ) return LV_COLOR_LIME;
        if( !strcmp(s, "green") ) return LV_COLOR_GREEN;
        if( !strcmp(s, "cyan") ) return LV_COLOR_CYAN;
        if( !strcmp(s, "aqua") ) return LV_COLOR_AQUA;
        if( !strcmp(s, "teal") ) return LV_COLOR_TEAL;
        if( !strcmp(s, "blue") ) return LV_COLOR_BLUE;
        if( !strcmp(s, "green") ) return LV_COLOR_GREEN;
        if( !strcmp(s, "navy") ) return LV_COLOR_NAVY;
        if( !strcmp(s, "magenta") ) return LV_COLOR_MAGENTA;
        if( !strcmp(s, "purple") ) return LV_COLOR_PURPLE;
        if( !strcmp(s, "orange") ) return LV_COLOR_ORANGE;
        if( !strcmp(s, "darkblue") ) return LV_COLOR_MAKE(0, 51, 102);
        if( !strcmp(s, "lightblue") ) return LV_COLOR_MAKE(46, 203, 203);
    } else if( evm_is_number(v) ){
        int i = evm_2_integer(v);
        return LV_COLOR_MAKE((i >>16) & 0xFF, (i >>8) & 0xFF, i & 0xFF);
    }
    return LV_COLOR_BLACK;
}

char * lvgl_hml_get_symbol(evm_t * e, evm_val_t * v){
    EVM_UNUSED(e);
    if( evm_is_string(v)) {
        const char * s = evm_2_string(v);
        if( !strcmp(s, "audio") ) return LV_SYMBOL_AUDIO;
        if( !strcmp(s, "video") ) return LV_SYMBOL_VIDEO;
        if( !strcmp(s, "list") ) return LV_SYMBOL_LIST;
        if( !strcmp(s, "ok") ) return LV_SYMBOL_OK;
        if( !strcmp(s, "close") ) return LV_SYMBOL_CLOSE;
        if( !strcmp(s, "power") ) return LV_SYMBOL_POWER;
        if( !strcmp(s, "settings") ) return LV_SYMBOL_SETTINGS;
        if( !strcmp(s, "home") ) return LV_SYMBOL_HOME;
        if( !strcmp(s, "download") ) return LV_SYMBOL_DOWNLOAD;
        if( !strcmp(s, "drive") ) return LV_SYMBOL_DRIVE;
        if( !strcmp(s, "refresh") ) return LV_SYMBOL_REFRESH;
        if( !strcmp(s, "mute") ) return LV_SYMBOL_MUTE;
        if( !strcmp(s, "volume_mid") ) return LV_SYMBOL_VOLUME_MID;
        if( !strcmp(s, "volume_max") ) return LV_SYMBOL_VOLUME_MAX;
        if( !strcmp(s, "image") ) return LV_SYMBOL_IMAGE;
        if( !strcmp(s, "edit") ) return LV_SYMBOL_EDIT;
        if( !strcmp(s, "prev") ) return LV_SYMBOL_PREV;
        if( !strcmp(s, "play") ) return LV_SYMBOL_PLAY;
        if( !strcmp(s, "pause") ) return LV_SYMBOL_PAUSE;
        if( !strcmp(s, "stop") ) return LV_SYMBOL_STOP;
        if( !strcmp(s, "next") ) return LV_SYMBOL_NEXT;
        if( !strcmp(s, "eject") ) return LV_SYMBOL_EJECT;
        if( !strcmp(s, "left") ) return LV_SYMBOL_LEFT;
        if( !strcmp(s, "right") ) return LV_SYMBOL_RIGHT;
        if( !strcmp(s, "plus") ) return LV_SYMBOL_PLUS;
        if( !strcmp(s, "minus") ) return LV_SYMBOL_MINUS;
        if( !strcmp(s, "eye_open") ) return LV_SYMBOL_EYE_OPEN;
        if( !strcmp(s, "eye_close") ) return LV_SYMBOL_EYE_CLOSE;
        if( !strcmp(s, "warning") ) return LV_SYMBOL_WARNING;
        if( !strcmp(s, "shuffle") ) return LV_SYMBOL_SHUFFLE;
        if( !strcmp(s, "up") ) return LV_SYMBOL_UP;
        if( !strcmp(s, "down") ) return LV_SYMBOL_DOWN;
        if( !strcmp(s, "loop") ) return LV_SYMBOL_LOOP;
        if( !strcmp(s, "directory") ) return LV_SYMBOL_DIRECTORY;
        if( !strcmp(s, "upload") ) return LV_SYMBOL_UPLOAD;
        if( !strcmp(s, "call") ) return LV_SYMBOL_CALL;
        if( !strcmp(s, "cut") ) return LV_SYMBOL_CUT;
        if( !strcmp(s, "copy") ) return LV_SYMBOL_COPY;
        if( !strcmp(s, "save") ) return LV_SYMBOL_SAVE;
        if( !strcmp(s, "charge") ) return LV_SYMBOL_CHARGE;
        if( !strcmp(s, "paste") ) return LV_SYMBOL_PASTE;
        if( !strcmp(s, "bell") ) return LV_SYMBOL_BELL;
        if( !strcmp(s, "keyboard") ) return LV_SYMBOL_KEYBOARD;
        if( !strcmp(s, "gps") ) return LV_SYMBOL_GPS;
        if( !strcmp(s, "file") ) return LV_SYMBOL_FILE;
        if( !strcmp(s, "wifi") ) return LV_SYMBOL_WIFI;
        if( !strcmp(s, "battery_full") ) return LV_SYMBOL_BATTERY_FULL;
        if( !strcmp(s, "battery_3") ) return LV_SYMBOL_BATTERY_3;
        if( !strcmp(s, "battery_2") ) return LV_SYMBOL_BATTERY_2;
        if( !strcmp(s, "battery_1") ) return LV_SYMBOL_BATTERY_1;
        if( !strcmp(s, "battery_empty") ) return LV_SYMBOL_BATTERY_EMPTY;
        if( !strcmp(s, "usb") ) return LV_SYMBOL_USB;
        if( !strcmp(s, "bluetooth") ) return LV_SYMBOL_BLUETOOTH;
        if( !strcmp(s, "trash") ) return LV_SYMBOL_TRASH;
        if( !strcmp(s, "backspace") ) return LV_SYMBOL_BACKSPACE;
        if( !strcmp(s, "sd_card") ) return LV_SYMBOL_SD_CARD;
        if( !strcmp(s, "new_line") ) return LV_SYMBOL_NEW_LINE;
    }
    return  LV_SYMBOL_DUMMY;
}

lv_chart_type_t lvgl_hml_get_ChartType(evm_t * e, evm_val_t * v){
    EVM_UNUSED(e);
    if( evm_is_string(v)) {
        const char * s = evm_2_string(v);
        if( !strcmp(s, "None") ) return LV_CHART_TYPE_NONE;
        if( !strcmp(s, "Line") ) return LV_CHART_TYPE_LINE;
        if( !strcmp(s, "Bar") ) return LV_CHART_TYPE_COLUMN;
//        if( !strcmp(s, "Point") ) return LV_CHART_TYPE_POINT;
//        if( !strcmp(s, "VLine") ) return LV_CHART_TYPE_VERTICAL_LINE;
//        if( !strcmp(s, "Area") ) return LV_CHART_TYPE_AREA;
    }
    return LV_CHART_TYPE_LINE;
}
