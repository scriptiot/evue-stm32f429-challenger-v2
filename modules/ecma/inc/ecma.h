/****************************************************************************
**
** Copyright (C) 2020 @scriptiot
**
**  EVM是一款通用化设计的虚拟机引擎，拥有语法解析前端接口、编译器、虚拟机和虚拟机扩展接口框架。
**  支持js、python、qml、lua等多种脚本语言，纯Ｃ开发，零依赖，内置REPL，支持主流 ROM > 40KB, RAM > 2KB的MCU;
**  自带垃圾回收（GC）先进的内存管理，采用最复杂的压缩算法，无内存碎片（大部分解释器都存在内存碎片）
**  Version	: 1.0
**  Email	: scriptiot@aliyun.com
**  Website	: https://github.com/scriptiot/evm
**            https://gitee.com/scriptiot/evm
**  Licence: Apache-2.0
****************************************************************************/

#ifndef ECMA_H
#define ECMA_H

#include "evm.h"

#ifndef CONFIG_EVM_ECMA_TIMEOUT_SIZE
#define CONFIG_EVM_ECMA_TIMEOUT_SIZE   16
#endif

#ifdef CONFIG_EVM_ECMA_OBJECT
#define ECMA_OBJECT_ATTR_SIZE   9
#define ECMA_OBJECT_PROP_SIZE   9
extern evm_val_t * ecma_Object;
#endif

#ifdef CONFIG_EVM_ECMA_ARRAY
#define ECMA_ARRAY_ATTR_SIZE    14
extern evm_val_t * ecma_Array;
#endif

#ifdef CONFIG_EVM_ECMA_REGEXP
extern evm_val_t * ecma_RegExp;
#endif

#ifdef CONFIG_EVM_ECMA_MATH
extern evm_val_t * ecma_Math;
#endif

#ifdef CONFIG_EVM_ECMA_NUMBER
extern evm_val_t * ecma_Number;
#define ECMA_NUMBER_ATTR_SIZE   3
#define ECMA_NUMBER_PROP_SIZE   2
#endif

#ifdef CONFIG_EVM_ECMA_STRING
extern evm_val_t * ecma_String;
#define ECMA_STRING_ATTR_SIZE   3
#define ECMA_STRING_PROP_SIZE   2
#endif

#define ARG_LENGTH_ERR { evm_set_err(e, ec_type, "Invalid argument length");return EVM_VAL_UNDEFINED; }
#define ARG_TYPE_ERR   { evm_set_err(e, ec_type, "Invalid argument type");return EVM_VAL_UNDEFINED; }

extern evm_val_t * ecma_function_prototype;
extern evm_val_t * ecma_object_prototype;

int ecma_module(evm_t * e);

#ifdef CONFIG_EVM_ECMA_TIMEOUT
void ecma_timeout_poll(evm_t * e);
#endif

extern uint16_t ecma_hash_constructor;
extern uint16_t ecma_hash_prototype;
extern uint16_t ecma_hash_create;
extern uint16_t ecma_hash_keys;
extern uint16_t ecma_hash_values;
extern uint16_t ecma_hash_entries;
extern uint16_t ecma_hash_getPrototypeOf;
extern uint16_t ecma_hash_getOwnPropertyNames;
extern uint16_t ecma_hash_forEach;
extern uint16_t ecma_hash_call;
extern uint16_t ecma_hash___proto__;
extern uint16_t ecma_hash_hasOwnProperty;
extern uint16_t ecma_hash_isPrototypeOf;
extern uint16_t ecma_hash_toString;
extern uint16_t ecma_hash_valueOf;
extern uint16_t ecma_hash_length;
extern uint16_t ecma_hash_push;
extern uint16_t ecma_hash_pop;
extern uint16_t ecma_hash_concat;
extern uint16_t ecma_hash_fill;
extern uint16_t ecma_hash_indexOf;
extern uint16_t ecma_hash_shift;
extern uint16_t ecma_hash_slice;
extern uint16_t ecma_hash_copyWithin;
extern uint16_t ecma_hash_unshift;
extern uint16_t ecma_hash_filter;
extern uint16_t ecma_hash_map;
extern uint16_t ecma_hash_find;
extern uint16_t ecma_hash_join;
extern uint16_t ecma_hash_defineProperty;

#endif
