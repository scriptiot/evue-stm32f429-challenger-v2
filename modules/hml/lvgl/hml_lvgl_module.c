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
#include "hml_lvgl_module.h"
#include "hml_module.h"
#include "widgets/lv_marquee.h"
/********** Global Variables ***********/

/********** Item ***********/
/********** Properties ***********/

#define BUTTON_CALLBACKS    {EVM_HML_CALLBACK, "onClicked", NULL},\
                            {EVM_HML_CALLBACK, "onPressed", NULL},\
                            {EVM_HML_CALLBACK, "onReleased", NULL},


#define HML_OBJ_PROPERTIES {EVM_HML_INT, "x", (evm_native_fn)hml_obj_set_x}, \
                            {EVM_HML_INT, "y", (evm_native_fn)hml_obj_set_y}, \
                            {EVM_HML_INT, "width", (evm_native_fn)hml_obj_set_width}, \
                            {EVM_HML_INT, "height", (evm_native_fn)hml_obj_set_height}, \
                            {EVM_HML_DOUBLE, "opacity", (evm_native_fn)hml_obj_set_opacity},\

static evm_hml_property_reg_t hml_obj_properties[] = {
    HML_OBJ_PROPERTIES
    {0, NULL, NULL}
};

static evm_hml_property_reg_t hml_text_properties[] = {
    HML_OBJ_PROPERTIES
    {EVM_HML_STRING, "text", (evm_native_fn)hml_Text_text},
    {0, NULL, NULL}
};

/* 赋值 appdir 给lv_scr_act()， 后续获取资源文件路径，需要根据 appdir 进行路径拼接*/
static evm_val_t hml_lv_init(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_string(v)){
        lv_obj_set_user_data(lv_scr_act(), (lv_obj_user_data_t)evm_2_string(v));
    }
    return EVM_VAL_UNDEFINED;
}

static evm_val_t hml_show(evm_t * e, evm_val_t *hml, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    EVM_UNUSED(argc);
    EVM_UNUSED(v);
    lv_obj_t * obj = NULL;
    obj = evm_hml_object_get_pointer(hml);
    if(obj){
        lv_obj_set_parent(obj, lv_scr_act());
        lv_obj_set_hidden(obj, false);
		lv_event_send_refresh_recursive(obj);
    }
    return EVM_VAL_UNDEFINED;
}

static evm_val_t hml_hide(evm_t * e, evm_val_t *hml, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    EVM_UNUSED(argc);
    EVM_UNUSED(v);
    lv_obj_t * obj = NULL;
    obj = evm_hml_object_get_pointer(hml);
    if(obj){
        lv_obj_set_hidden(obj, true);
    }
    return EVM_VAL_UNDEFINED;
}

int hml_lvgl_module(evm_t * e){
    set_global_e(e);
    evm_hml_object_reg_t hml_objects[] = {
        {"div", NULL, (evm_native_fn)hml_Div, hml_obj_properties},
        {"list", NULL, (evm_native_fn)hml_List, hml_obj_properties},
        {"list-item", NULL, (evm_native_fn)hml_ListItem, hml_obj_properties},
        {"stack", NULL, (evm_native_fn)hml_Stack, hml_obj_properties},
        {"swiper", NULL, (evm_native_fn)hml_Swiper, hml_obj_properties},
        {"image", NULL, (evm_native_fn)hml_Image, hml_obj_properties},
        {"image-animator", NULL, (evm_native_fn)hml_ImageAnimator, hml_obj_properties},
        {"progress", NULL, (evm_native_fn)hml_Progress, hml_obj_properties},
        {"text", NULL, (evm_native_fn)hml_Text, hml_text_properties},
        {"marquee", NULL, (evm_native_fn)hml_Marquee, hml_obj_properties},
        {"chart", NULL, (evm_native_fn)hml_Chart, hml_obj_properties},
        {"input", NULL, (evm_native_fn)hml_Input, hml_obj_properties},
        {"slider", NULL, (evm_native_fn)hml_Slider, hml_obj_properties},
        {"switch", NULL, (evm_native_fn)hml_Switch, hml_obj_properties},
        {"picker-view", NULL, (evm_native_fn)hml_PickerView, hml_obj_properties},
        {NULL, NULL, NULL, NULL}
    };

    evm_hml_property_reg_t hml_style_properties[] = {
        {EVM_HML_STRING, "display", (evm_native_fn)hml_obj_set_display, evm_str_insert(e, "display", 0)},
        {EVM_HML_INT, "left", (evm_native_fn)hml_obj_set_x, evm_str_insert(e, "left", 0)},
        {EVM_HML_INT, "top", (evm_native_fn)hml_obj_set_y, evm_str_insert(e, "top", 0)},
        {EVM_HML_INT, "width", (evm_native_fn)hml_obj_set_width, evm_str_insert(e, "width", 0)},
        {EVM_HML_INT, "height", (evm_native_fn)hml_obj_set_height, evm_str_insert(e, "height", 0)},
        {EVM_HML_STRING, "align-items", (evm_native_fn)hml_obj_set_alignitems, evm_str_insert(e, "align-items", 0)},
        {EVM_HML_STRING, "flex-direction", (evm_native_fn)hml_obj_set_flexdirection, evm_str_insert(e, "flex-direction", 0)},
        {EVM_HML_STRING, "background-color", (evm_native_fn)hml_obj_set_backgroundcolor, evm_str_insert(e, "background-color", 0)},
        {EVM_HML_INT, "opacity", (evm_native_fn)hml_obj_set_opacity, evm_str_insert(e, "opacity", 0)},
        {EVM_HML_STRING, "border-color", (evm_native_fn)hml_obj_set_bordercolor, evm_str_insert(e, "border-color", 0)},
        {EVM_HML_INT, "border-width", (evm_native_fn)hml_obj_set_borderwidth, evm_str_insert(e, "border-width", 0)},
        {EVM_HML_INT, "border-radius", (evm_native_fn)hml_obj_set_borderradius, evm_str_insert(e, "border-radius", 0)},
        {EVM_HML_INT, "margin", (evm_native_fn)hml_obj_set_margin, evm_str_insert(e, "margin", 0)},
        {EVM_HML_INT, "margin-left", (evm_native_fn)hml_obj_set_margin_left, evm_str_insert(e, "margin-left", 0)},
        {EVM_HML_INT, "margin-top", (evm_native_fn)hml_obj_set_margin_top, evm_str_insert(e, "margin-top", 0)},
        {EVM_HML_INT, "margin-right", (evm_native_fn)hml_obj_set_margin_right, evm_str_insert(e, "margin-right", 0)},
        {EVM_HML_INT, "margin-bottom", (evm_native_fn)hml_obj_set_margin_bottom, evm_str_insert(e, "margin-bottom", 0)},
        {EVM_HML_INT, "padding", (evm_native_fn)hml_obj_set_padding, evm_str_insert(e, "padding", 0)},
        {EVM_HML_INT, "padding-left", (evm_native_fn)hml_obj_set_padding_left, evm_str_insert(e, "padding-left", 0)},
        {EVM_HML_INT, "padding-top", (evm_native_fn)hml_obj_set_padding_top, evm_str_insert(e, "padding-top", 0)},
        {EVM_HML_INT, "padding-right", (evm_native_fn)hml_obj_set_padding_right, evm_str_insert(e, "padding-right", 0)},
        {EVM_HML_INT, "padding-bottom", (evm_native_fn)hml_obj_set_padding_bottom, evm_str_insert(e, "padding-bottom", 0)},
        {EVM_HML_STRING, "color", (evm_native_fn)hml_obj_set_text_color, evm_str_insert(e, "color", 0)},
        {EVM_HML_STRING, "text-align", (evm_native_fn)hml_obj_set_text_align, evm_str_insert(e, "text-align", 0)},
        {EVM_HML_INT, "font-size", (evm_native_fn)hml_obj_set_text_font_size, evm_str_insert(e, "font-size", 0)},
        {EVM_HML_INT, "letter-spacing", (evm_native_fn)hml_obj_set_text_letter_space, evm_str_insert(e, "letter-spacing", 0)},
        {EVM_HML_STRING, "font-family", (evm_native_fn)hml_obj_set_text_font_family, evm_str_insert(e, "font-family", 0)},
        {EVM_HML_STRING, "text-overflow", (evm_native_fn)hml_obj_set_text_overflow, evm_str_insert(e, "text-overflow", 0)},
        {EVM_HML_INT, "animation-speed", (evm_native_fn)hml_obj_set_text_animation_speed, evm_str_insert(e, "animation-speed", 0)},
        {EVM_HML_ANY, "fade-in", (evm_native_fn)hml_obj_set_fade_in, evm_str_insert(e, "fade-in", 0)},
        {EVM_HML_ANY, "fade-out", (evm_native_fn)hml_obj_set_fade_out, evm_str_insert(e, "fade-out", 0)},
        {EVM_HML_ANY, NULL, NULL, 0}
    };

    evm_hml_object_register(e, hml_objects);
    evm_hml_style_register(e, hml_style_properties);
    int err = hml_module(e, (evm_native_fn)hml_lv_init,
                            (evm_native_fn)hml_lv_set_display_style,
                            (evm_native_fn)hml_lv_set_style,
                            (evm_native_fn)hml_show,
                            (evm_native_fn)hml_hide);

    static lv_style_t scr_style;
    lv_style_init(&scr_style);
    lv_style_set_bg_opa(&scr_style, LV_STATE_DEFAULT, LV_OPA_TRANSP);
    lv_obj_add_style(lv_scr_act(), LV_OBJ_PART_MAIN, &scr_style);
    return err;
}

