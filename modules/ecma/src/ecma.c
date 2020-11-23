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

#include "ecma.h"

uint16_t ecma_hash_constructor;
uint16_t ecma_hash_prototype;
uint16_t ecma_hash_create;
uint16_t ecma_hash_keys;
uint16_t ecma_hash_values;
uint16_t ecma_hash_entries;
uint16_t ecma_hash_getPrototypeOf;
uint16_t ecma_hash_getOwnPropertyNames;
uint16_t ecma_hash_forEach;
uint16_t ecma_hash_call;
uint16_t ecma_hash___proto__;
uint16_t ecma_hash_hasOwnProperty;
uint16_t ecma_hash_isPrototypeOf;
uint16_t ecma_hash_toString;
uint16_t ecma_hash_valueOf;

uint16_t ecma_hash_length;
uint16_t ecma_hash_push;
uint16_t ecma_hash_pop;
uint16_t ecma_hash_concat;
uint16_t ecma_hash_fill;
uint16_t ecma_hash_indexOf;
uint16_t ecma_hash_shift;
uint16_t ecma_hash_slice;
uint16_t ecma_hash_copyWithin;
uint16_t ecma_hash_unshift;
uint16_t ecma_hash_filter;
uint16_t ecma_hash_map;
uint16_t ecma_hash_find;
uint16_t ecma_hash_join;

uint16_t ecma_hash_defineProperty;

#ifdef CONFIG_EVM_ECMA_OBJECT
extern evm_val_t * ecma_object_init(evm_t * e);
extern void ecma_object_attrs_apply(evm_t * e, evm_val_t * o, evm_val_t * prototype);
#endif
#ifdef CONFIG_EVM_ECMA_ARRAY
extern evm_val_t * ecma_array_init(evm_t * e);
#endif
#ifdef CONFIG_EVM_ECMA_NUMBER
extern evm_val_t * ecma_number_init(evm_t * e);
#endif
#ifdef CONFIG_EVM_ECMA_MATH
extern evm_val_t * ecma_math_init(evm_t * e);
#endif
#ifdef CONFIG_EVM_ECMA_STRING
extern evm_val_t * ecma_string_init(evm_t * e);
#endif
#ifdef CONFIG_EVM_ECMA_REGEXP
extern evm_val_t * ecma_regex_init(evm_t * e);
#endif
#ifdef CONFIG_EVM_ECMA_TIMEOUT_SIZE
extern int ecma_timeout_init(evm_t * e);
#endif
#ifdef CONFIG_EVM_ECMA_DATE
extern evm_val_t * ecma_date_init(evm_t * e);
#endif

evm_val_t * ecma_object_prototype;
evm_val_t * ecma_function_prototype;

static evm_val_t ecma_typeof(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(e);EVM_UNUSED(p);
    if( argc > 0){
        switch (evm_type(v)) {
            case TYPE_BOOLEAN: return evm_mk_foreign_string((intptr_t)"boolean");
            case TYPE_NUMBER: return evm_mk_foreign_string((intptr_t)"number");
            case TYPE_HEAP_STRING:
            case TYPE_FOREIGN_STRING: return evm_mk_foreign_string((intptr_t)"string");
            case TYPE_FUNCTION: return evm_mk_foreign_string((intptr_t)"function");
            case TYPE_UNDEFINED: return evm_mk_foreign_string((intptr_t)"undefined");
        default:
            return evm_mk_foreign_string((intptr_t)"object");
        }
    }
    return EVM_VAL_UNDEFINED;
}

static evm_val_t ecma_new(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(e);EVM_UNUSED(p);
    if(argc > 0){
        switch (evm_type(v)) {
        case TYPE_FUNCTION:{
            evm_val_t * fn = v;
            if( evm_script_get_native(v) != NULL){
                evm_native_fn fn = evm_script_get_native(v);
                return fn(e, v, argc - 1, v + 1);
            } else {
                evm_val_t * o = evm_object_create(e, GC_DICT, 0, 0);
            #ifdef CONFIG_EVM_ECMA_OBJECT
                evm_val_t * prototype = evm_attr_get_by_key(e, fn, ecma_hash_prototype);
                ecma_object_attrs_apply(e, o, prototype);
                evm_attr_set_key_value(e, o, 1, ecma_hash_constructor, *fn);
            #endif
                evm_run_callback(e, fn, o, v + 1, argc - 1);
                return *o;
            }
        }break;
        case TYPE_CLASS:{
            evm_val_t * o = evm_object_create_by_class(e, GC_DICT, v);
            if( evm_class_get_native(v) != NULL){
                evm_native_fn fn = evm_class_get_native(v);
                fn(e, o, argc - 1, v + 1);
            } else {
                evm_run_callback(e, v, o, v + 1, argc - 1);
            }
            return *o;
        }break;
        default:
            break;
        }
    }
    return EVM_VAL_UNDEFINED;
}

static evm_val_t ecma_function_call(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    if( argc >= 1 && p && evm_is_script(p) && evm_is_object(v) ){
        evm_val_t ret_val = evm_run_callback(e, p, v, v + 1, argc - 1);
        return ret_val;
    }
    return EVM_VAL_UNDEFINED;
}

static evm_val_t * ecma_prototype_create(evm_t *e ){
    evm_val_t * o = evm_object_create(e, GC_DICT, 0, 1);
    evm_attr_set_key_value(e, o, 0, ecma_hash_constructor, evm_mk_native( (intptr_t)ecma_new ));
    return o;
}

static evm_val_t ecma_set_prototype(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(p);
    if( argc > 0 ){
        switch (evm_type(v)) {
        case TYPE_FUNCTION:
            if( evm_attr_create(e, v, 4) == ec_ok ){
                evm_attr_set_key_value(e, v, 0, ecma_hash_constructor, *v);
                evm_attr_set_key_value(e, v, 1, ecma_hash_prototype, * ecma_prototype_create(e));
                evm_attr_set_key_value(e, v, 2, ecma_hash_call, evm_mk_native((intptr_t)ecma_function_call));
                evm_attr_set_key_value(e, v, 3, ecma_hash___proto__, *ecma_object_prototype);
            }
            evm_set_parent(v, ecma_object_prototype);
            break;
        case TYPE_OBJECT:
        #ifdef CONFIG_EVM_ECMA_OBJECT
            ecma_object_attrs_apply(e, v, ecma_object_prototype);
        #endif
            evm_set_parent(v, ecma_object_prototype);
            break;
        default:
            break;
        }
    }
    return EVM_VAL_UNDEFINED;
}

static evm_val_t ecma_isNaN(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(e);EVM_UNUSED(p);
    if( argc == 0 ) return EVM_VAL_TRUE;
    if( argc > 0 ) if( evm_is_nan(v) ) return EVM_VAL_TRUE;
    return EVM_VAL_FALSE;
}

static evm_val_t ecma_parseInt(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(e);EVM_UNUSED(p);
	return EVM_VAL_UNDEFINED;
}

int ecma_module(evm_t * e){
    ecma_hash_constructor = evm_str_insert(e, "constructor", 1);
    ecma_hash_prototype = evm_str_insert(e, "prototype", 1);
    ecma_hash_create = evm_str_insert(e, "create", 1);
    ecma_hash_call = evm_str_insert(e, "call", 1);
    ecma_hash_keys = evm_str_insert(e, "keys", 1);
    ecma_hash_values = evm_str_insert(e, "values", 1);
    ecma_hash_entries = evm_str_insert(e, "entries", 1);
    ecma_hash_getPrototypeOf = evm_str_insert(e, "getPrototypeOf", 1);
    ecma_hash_getOwnPropertyNames = evm_str_insert(e, "getOwnPropertyNames", 1);
    ecma_hash_forEach = evm_str_insert(e, "forEach", 1);
    ecma_hash___proto__ = evm_str_insert(e, "__proto__", 1);
    ecma_hash_hasOwnProperty = evm_str_insert(e, "hasOwnProperty", 1);
    ecma_hash_isPrototypeOf = evm_str_insert(e, "isPrototypeOf", 1);
    ecma_hash_toString = evm_str_insert(e, "toString", 1);
    ecma_hash_valueOf = evm_str_insert(e, "valueOf", 1);
    ecma_hash_length = evm_str_insert(e, "length", 1);
    ecma_hash_push = evm_str_insert(e, "push", 1);
    ecma_hash_pop = evm_str_insert(e, "pop", 1);
    ecma_hash_concat = evm_str_insert(e, "concat", 1);
    ecma_hash_fill = evm_str_insert(e, "fill", 1);
    ecma_hash_indexOf = evm_str_insert(e, "indexOf", 1);
    ecma_hash_shift = evm_str_insert(e, "shift", 1);
    ecma_hash_slice = evm_str_insert(e, "slice", 1);
    ecma_hash_copyWithin = evm_str_insert(e, "copyWithin", 1);
    ecma_hash_unshift = evm_str_insert(e, "unshift", 1);
    ecma_hash_filter = evm_str_insert(e, "filter", 1);
    ecma_hash_map = evm_str_insert(e, "map", 1);
    ecma_hash_find = evm_str_insert(e, "find", 1);
    ecma_hash_join = evm_str_insert(e, "join", 1);

    ecma_hash_defineProperty = evm_str_insert(e, "defineProperty", 1);

    ecma_function_prototype = evm_object_create(e, GC_DICT, 0, 0);
    ecma_object_prototype = evm_object_create(e, GC_DICT, 0, 0);

#ifdef CONFIG_EVM_ECMA_OBJECT
    ecma_Object = ecma_object_init(e);
    ecma_object_attrs_apply(e, ecma_object_prototype, ecma_function_prototype);
#endif
#ifdef CONFIG_EVM_ECMA_ARRAY
    ecma_Array = ecma_array_init(e);
#endif
#ifdef CONFIG_EVM_ECMA_NUMBER
    ecma_Number = ecma_number_init(e);
#endif
#ifdef CONFIG_EVM_ECMA_MATH
    ecma_Math = ecma_math_init(e);
#endif
#ifdef CONFIG_EVM_ECMA_STRING
    ecma_String = ecma_string_init(e);
#endif
#ifdef CONFIG_EVM_ECMA_REGEXP
    ecma_RegExp = ecma_regex_init(e);
#endif
#ifdef CONFIG_EVM_ECMA_TIMEOUT_SIZE
    ecma_timeout_init(e);
#endif
    evm_builtin_t natives[] = {
        {".set_prototype", evm_mk_native( (intptr_t)ecma_set_prototype )},
        {".new", evm_mk_native( (intptr_t)ecma_new )},
        {"isNaN", evm_mk_native( (intptr_t)ecma_isNaN )},
        {"typeof", evm_mk_native( (intptr_t)ecma_typeof )},
    #ifdef CONFIG_EVM_ECMA_REGEXP
        {"RegExp", *ecma_RegExp},
    #endif
    #ifdef CONFIG_EVM_ECMA_MATH
        {"Math", *ecma_Math},
    #endif
    #ifdef CONFIG_EVM_ECMA_OBJECT
        {"Object", *ecma_Object},
    #endif
    #ifdef CONFIG_EVM_ECMA_ARRAY
        {"Array", *ecma_Array},
    #endif
    #ifdef CONFIG_EVM_ECMA_NUMBER
        {"Number", *ecma_number_init(e)},
    #endif
    #ifdef CONFIG_EVM_ECMA_STRING
        {"String", *ecma_string_init(e)},
    #endif
    #ifdef CONFIG_EVM_ECMA_DATE
        {"Date", *ecma_date_init(e)},
    #endif
        {NULL, EVM_VAL_UNDEFINED}
    };
    return evm_native_add(e, natives);
}
