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
#ifndef HML_MOUDLE_H
#define HML_MOUDLE_H

#include "evm.h"

enum EVM_HML_TYPE{
    EVM_HML_INT = 1,
    EVM_HML_DOUBLE = 2,
    EVM_HML_BOOLEAN = 4,
    EVM_HML_STRING = 8,
    EVM_HML_CALLBACK = 16,
    EVM_HML_VALUE = 32,
    EVM_HML_ANY = 64,
    EVM_HML_GROUP = 128,
};

/**
 * @brief 定义hml对象每个属性setter的api接口， 用于注册
 * @param type, 属性参数值对于evm内部数据类型
 * @param name, 属性名称
 * @param api,  属性setter api接口函数
 * @param key, 属性字符串对应的索引key值
 */
typedef struct evm_hml_property_reg_t{
    int type;
    char * name;
    evm_native_fn api;
    uint32_t key;
}evm_hml_property_reg_t;

/**
 * @brief hml注册对象，用于注册
 * @param name, hml对象标签的名称，例如Div/Text/Input
 * @param parent_name, 保留，暂未使用
 * @param api,  hml对象创建的api接口
 * @param properties,  hml对象对应的属性setter api接口
 */
typedef struct evm_hml_object_reg_t{
    char * name;
    char * parent_name;
    evm_native_fn api;
    evm_hml_property_reg_t * properties;
}evm_hml_object_reg_t;

/**
 * @brief 定义关联evm对象的外部对象-hml对象，通过 evm_object_set_ext_data 进行设置
 * @param name, hml对象标签的名称，例如Div/Text/Input
 * @param parent_name, 保留，暂未使用
 * @param api,  hml对象创建的api接口
 * @param properties,  hml对象对应的属性接口列表
 * @param properties_len,  hml对象对应的属性接口列表的长度
 * @param obj, lvgl中UI对象的指针
 * @param viewmodel,  index.js执行后被viewmodel.js属性拦截后的对象，本质上是一个viewmodel对象
 * @param parent,  当前hml对象的父对象指针
 */
typedef struct hml_object_t{
    const char * name;
    char * parent_name;
    evm_native_fn api;
    evm_hml_property_reg_t * properties;
    void * obj;
    int properties_len;
    evm_val_t  viewmodel;
    struct hml_object_t * parent;
} hml_object_t;

typedef struct hml_data_binding_t{
    int16_t src_name;
    evm_val_t tar_obj;
    int is_attribute;
    evm_val_t  function;
    struct hml_data_binding_t * next;
} hml_data_binding_t;

typedef struct hml_func_binding_t{
    evm_val_t obj;
    int is_attribute;
    int16_t name;
    evm_val_t func;
    evm_val_t ret;
    struct hml_func_binding_t * next;
} hml_func_binding_t;

typedef struct hml_page_t {
    evm_val_t index_object;
    evm_val_t css_object;
    evm_val_t hml_object;
    evm_val_t view_model;

    hml_func_binding_t * func_bindings;
    hml_data_binding_t * data_bindings;

    evm_native_fn init;
    evm_native_fn show;
    evm_native_fn hide;
} hml_page_t;

/**
 * @brief 将lvgl中对应hml的ui对象赋值给evm对象外部指针ext_data->obj
 * @param o, hml文件解析后的节点evm对象
 * @param pointer, lvgl中对应hml的ui对象
 * @return
 */
void evm_hml_object_set_pointer(evm_val_t * o, void * pointer);

/**
 * @brief 获取evm对象外部指针ext_data->obj
 * @param o, hml文件解析后的节点evm对象
 * @return lvgl中对应hml的ui对象指针
 */
void * evm_hml_object_get_pointer(evm_val_t * o);

/**
 * @brief 获取evm对象对应的节点标签名称
 * @param e, 虚拟机对象
 * @param o, hml文件解析后的节点evm对象
 * @return 节点的标签名称
 */
const char * evm_hml_object_get_name(evm_t* e, evm_val_t * o);

/**
 * @brief 注册 hml注册对象列表
 * @param e, 虚拟机对象
 * @param regs, hml注册对象列表
 * @return 返回码 Errcode
 */
int evm_hml_object_register(evm_t * e, evm_hml_object_reg_t * regs);

/**
 * @brief 注册 hml注册对象的样式接口列表
 * @param e, 虚拟机对象
 * @param regs, hml注册对象列表
 * @return 返回码 Errcode
 */
int evm_hml_style_register(evm_t * e, evm_hml_property_reg_t * regs);

/**
 * @brief 注册 hml注册对象列表
 * @param e, 虚拟机对象
 * @param regs, hml注册对象列表
 * @return 返回码 Errcode
 */
evm_err_t hml_module(evm_t * e, evm_native_fn init, evm_native_fn set_display_style, evm_native_fn set_style, evm_native_fn show, evm_native_fn hide);


void hml_object_gc_init(evm_t * e, evm_val_t * old_self, evm_val_t *new_self);
void evm_hml_write_value(evm_t * e, evm_val_t * src_obj, char * name, evm_val_t v);

/**
 * @brief 合并对象，把src中所有的属性添加到target
 * @param e, 虚拟机对象
 * @param target, 目标对象
 * @param src, 原对象
 * @return
 */
void merge_obj(evm_t * e, evm_val_t * target, evm_val_t * src);

/**
 * @brief 初始化page
 * @param e, 虚拟机对象
 * @param page, 目标页面
 * @return
 */
void hml_page_init(evm_t * e, hml_page_t * page);

/**
 * @brief 根据page创建UI界面
 * @param e, 虚拟机对象
 * @param page, 目标页面
 * @return
 */
int hml_run(evm_t * e, hml_page_t * page);

/**
 * @brief 应用page的css样式
 * @param e, 虚拟机对象
 * @param hml, 目标hml对象
 * @param css_label, 标签样式
 * @param css_class, class样式
 * @param css_id, id样式
 * @param keyframes, 动画样式
 * @return
 */
int css_run(evm_t * e, evm_val_t * hml, evm_val_t * css_label, evm_val_t * css_class, evm_val_t * css_id, evm_val_t * keyframes);

#endif
