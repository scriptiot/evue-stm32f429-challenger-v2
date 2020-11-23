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
#ifndef HML_BASE_H
#define HML_BASE_H

#include "evm.h"
#include "lvgl.h"
#include "../hml_lvgl_utils.h"

evm_t * get_global_e(void);
void set_global_e(evm_t * e);

char * lvgl_app_dir(void);
bool lvgl_is_obj_type(lv_obj_t * obj, const char* type_name);
void lvgl_hml_run_callback(evm_t * e, lv_obj_t * obj, evm_val_t  viewmodel, const char * name, int argc, evm_val_t * args);
void lv_hml_event_handler(lv_obj_t * obj, lv_event_t event);

#endif
