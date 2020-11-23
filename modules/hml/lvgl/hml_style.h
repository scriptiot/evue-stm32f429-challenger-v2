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
#ifndef HML_STYLE_H
#define HML_STYLE_H

#include "evm.h"
#include "lvgl.h"

evm_val_t  hml_lv_set_display_style(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_display(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_x(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_y(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_pos(evm_t * e, evm_val_t *p, int argc, evm_val_t * x, evm_val_t * y);
evm_val_t  hml_obj_set_width(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_height(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_size(evm_t * e, evm_val_t *p, int argc, evm_val_t * width, evm_val_t * height);
evm_val_t  hml_obj_set_alignitems(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_flexdirection(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_backgroundcolor(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_gradient_color(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_gradient_dir(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_gradient_main_stop(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_gradient_grad_stop(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_opacity(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_bordercolor(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_borderwidth(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_borderradius(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_margin(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_margin_left(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_margin_top(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_margin_right(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_margin_bottom(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_padding(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_padding_left(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_padding_top(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_padding_right(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_padding_bottom(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_text_color(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_text_align(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_text_font_size(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_text_letter_space(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_text_font_family(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_text_overflow(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_text_animation_speed(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_fade_in(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_fade_out(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t lv_obj_set_bg_color(lv_obj_t * obj, lv_anim_value_t v);
evm_val_t  hml_obj_set_animation(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_obj_set_x(evm_t * e, evm_val_t *p, int argc, evm_val_t * v);
evm_val_t  hml_lv_set_style(evm_t * e, evm_val_t *hml_obj, int argc, evm_val_t * css_obj);

#endif
