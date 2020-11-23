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

#ifdef CONFIG_EVM_ECMA_OBJECT
#include "ecma.h"

evm_val_t *ecma_Object;

#ifdef CONFIG_EVM_ECMA_ARRAY
extern evm_val_t ecma_array(evm_t * e, evm_val_t * p, int argc, evm_val_t * v);
extern void ecma_array_attrs_apply(evm_t * e, evm_val_t * o);
#endif

void fsort(char*c[],int n)
{
    int k,j;
    char *temp;
    for(k=1;k<n;k++)
        for(j=0;j<n-k;j++)
            if(strcmp(c[j],c[j+1])>0){
                temp=c[j];
                c[j]=c[j+1];
                c[j+1]=temp;
            }
}

evm_val_t object_prototype_hasOwnProperty(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    (void)e;
    (void)p;
    (void)argc;
    (void)v;
    if(argc == 0) ARG_LENGTH_ERR;
    if (argc >=1 && evm_is_string(v) && evm_is_object(p)){
        evm_val_t * value = evm_prop_get(e, p, evm_2_string(v), 0);
        if (value){
            return EVM_VAL_TRUE;
        }else{
            return EVM_VAL_FALSE;
        }
    }else if (argc >=1 && evm_is_string(v) && evm_is_list(p)){
        int len = evm_list_len(p);
        int index = atoi(evm_2_string(v));
        if (index >= 0 && index < len){
            return EVM_VAL_TRUE;
        }else{
            return EVM_VAL_FALSE;
        }
    }else if (argc >=1 && evm_is_string(v) && evm_is_string(p)){
        int len = evm_string_len(p);
        int index = atoi(evm_2_string(v));
        if (index >= 0 && index < len){
            return EVM_VAL_TRUE;
        }else{
            return EVM_VAL_FALSE;
        }
    }
    return EVM_VAL_FALSE;
}


evm_val_t object_prototype_isPrototypeOf(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    if (argc >=1 && evm_is_object(v)){
        evm_val_t * value = evm_attr_get_by_index(e, p, 0);
        if (value){
            if (*v == *value){
                return EVM_VAL_TRUE;
            }else{
                return EVM_VAL_FALSE;
            }
        }else{
            return EVM_VAL_FALSE;
        }
    }
    return EVM_VAL_FALSE;
}

evm_val_t object_prototype_toString(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(e);EVM_UNUSED(argc);EVM_UNUSED(v);
    if (evm_is_object(p)){
        return evm_mk_foreign_string((intptr_t)"object");
    }
    return evm_mk_foreign_string((intptr_t)"undefined");
}

evm_val_t object_prototype_valueOf(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(e);EVM_UNUSED(argc);EVM_UNUSED(p);
    if(argc > 0) return *v;
    return EVM_VAL_UNDEFINED;
}

void ecma_object_attrs_set(evm_t * e, evm_val_t * o, evm_val_t * object, evm_val_t * prototype){
    evm_attr_set_key_value(e, o, 0, ecma_hash___proto__, *prototype);
    evm_attr_set_key_value(e, o, 1, ecma_hash_constructor, *object);
    evm_attr_set_key_value(e, o, 2, ecma_hash_hasOwnProperty, evm_mk_native((intptr_t)object_prototype_hasOwnProperty));
    evm_attr_set_key_value(e, o, 3, ecma_hash_isPrototypeOf, evm_mk_native((intptr_t)object_prototype_isPrototypeOf));
    evm_attr_set_key_value(e, o, 4, ecma_hash_toString, evm_mk_native((intptr_t)object_prototype_toString));
    evm_attr_set_key_value(e, o, 5, ecma_hash_valueOf, evm_mk_native((intptr_t)object_prototype_valueOf));
}

void ecma_object_attrs_apply(evm_t * e, evm_val_t * o, evm_val_t * prototype){
    if( evm_attr_create(e, o, 8) == ec_ok ){
        ecma_object_attrs_set(e, o, ecma_Object, prototype);
        evm_set_parent(o, prototype);
    }
}

evm_val_t *index_2_string(evm_t * e, int index){
    char buf[64];
    sprintf(buf, "%d", index);
    int slen = strlen(buf);
    evm_val_t * so = evm_heap_string_create(e, buf, slen + 1);
    return so;
}

evm_val_t ecma_object_new(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(p);
    evm_val_t * o;
    if( argc == 0){
        o = evm_object_create(e, GC_DICT, 0, 0);
        ecma_object_attrs_apply(e, o, ecma_object_prototype);
        return *o;
    } else if(evm_2_intptr(v) ){
        return *v;
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t ecma_object_create(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(p);
    evm_val_t * o = NULL;
    if( argc == 1 && evm_is_null(v)){
        o = evm_object_create(e, GC_DICT, 0, 0);
        ecma_object_attrs_apply(e, o, v);
        evm_attr_set_key_value(e, o,  0, ecma_hash___proto__, evm_mk_null());
        return *o;
    } else if(argc == 1 && evm_is_object(v) ){
        o = evm_object_create(e, GC_DICT, 0, 0);
        ecma_object_attrs_apply(e, o, v);
        return *o;
    }
#ifdef CONFIG_EVM_ECMA_ARRAY
    else if(argc == 1 && evm_is_list(v) ){
        o = evm_object_duplicate(e, evm_type(v), v);
        ecma_array_attrs_apply(e, o);
        return *o;
    }
#endif
    return EVM_VAL_UNDEFINED;
}

evm_val_t ecma_object_keyvalues(evm_t * e, evm_val_t * p, int argc, evm_val_t * v, int func){
    EVM_UNUSED(e);EVM_UNUSED(p);EVM_UNUSED(argc);EVM_UNUSED(v);EVM_UNUSED(func);
    if(argc == 0) return EVM_VAL_UNDEFINED;
#ifdef CONFIG_EVM_ECMA_ARRAY
    if (evm_is_list(v)){
        int len = evm_list_len(v);

        if (func == 3) len = len + 1;

        evm_val_t * o = evm_list_create(e, GC_LIST, len);

        switch (func) {
        case 0: {
            for(int i = 0; i < len; i++){
                evm_prop_set_value_by_index(e, o, i, *index_2_string(e, i));
            }
        } break;
        case 1: {
            evm_val_t * obj = v;
            for(int i = 0; i < len; i++){
                evm_prop_set_value_by_index(e, o, i, *evm_prop_get_by_index(e, obj, i));
            }
        } break;

        case 2: {
            for(int i = 0; i < len; i++){
                evm_val_t * kv = evm_list_create(e, GC_LIST, 2);
                evm_prop_set_value_by_index(e, kv, 0, *index_2_string(e, i));
                evm_prop_set_value_by_index(e, kv, 1, *evm_prop_get_by_index(e, v, i));
                ecma_array_attrs_apply(e, kv);
                evm_prop_set_value_by_index(e, o, i, *kv);
            }
        } break;

        case 3: {
            for(int i = 0; i < len - 1; i++){
                evm_prop_set_value_by_index(e, o, i, *index_2_string(e, i));
            }
            evm_prop_set_value_by_index(e, o, len - 1, evm_mk_foreign_string((intptr_t)"length"));
        } break;
        default:
            break;
        }

        ecma_array_attrs_apply(e, o);
        return  *o;
    }else if (evm_is_object(v)){
        evm_val_t * obj = v;
        if( evm_prop_len(obj) == 0)
            return ecma_array(e, p, 0, v);

        int len = evm_prop_len(obj);
        char* keys[len];

        int enumerableIndex = 0;
        for(int i = 0; i < len; i++){
            int key = evm_prop_get_key_by_index(e, obj, i);
            char * buf = evm_string_get(e, key);
            keys[enumerableIndex] = buf;
            enumerableIndex++;
        }

        if (func != 3) {
            fsort(keys, enumerableIndex);
        }

        evm_val_t * o = evm_list_create(e, GC_LIST, enumerableIndex);

        switch (func) {
            case 0:
            case 3: {
                for(int i=0; i < enumerableIndex; i++){
                    int slen = strlen(keys[i]);
                    evm_val_t * so = evm_heap_string_create(e, keys[i], slen + 1);
                    evm_prop_set_value_by_index(e, o, i, *so);
                }
            } break;
            case 1: {
                for(int i = 0; i < enumerableIndex; i++){
                    char* key = keys[i];
                    evm_prop_set_value_by_index(e, o, i, *evm_prop_get(e, obj, key, 0));
                }
            } break;
        #ifdef CONFIG_EVM_ECMA_ARRAY
            case 2: {
                for(int i = 0; i < enumerableIndex; i++){
                    char* key = keys[i];
                    int slen = strlen(key);
                    evm_val_t *kv = evm_list_create(e, GC_LIST, 2);
                    evm_val_t *so = evm_heap_string_create(e, key, slen + 1);
                    evm_prop_set_value_by_index(e, kv, 0, *so);
                    evm_prop_set_value_by_index(e, kv, 1, *evm_prop_get(e, obj, key, 0));
                    ecma_array_attrs_apply(e, kv);
                    evm_prop_set_value_by_index(e, o, i, *kv);
                }
            } break;
        #endif
            default:
                break;
        }
        ecma_array_attrs_apply(e, o);
        return *o;
    }else if (evm_is_string(v)){
        int len = strlen(evm_2_string(v));

        if (func == 3) len = len + 1;

        evm_val_t * o = evm_list_create(e, GC_LIST,len);
        switch (func) {
            case 0: {
                for(int i = 0; i < len; i++){
                    evm_prop_set_value_by_index(e, o, i, *index_2_string(e, i));
                }
            } break;
            case 1: {
                char * s = (char*)evm_2_string(v);
                for(int i = 0; i < len; i++){
                    evm_val_t *t = evm_heap_string_create(e, s+i, 1);
                    evm_prop_set_value_by_index(e, o, i, *t);
                }
            } break;
            case 2: {
                char * s = (char*)evm_2_string(v);
                for(int i = 0; i < len; i++){
                    evm_val_t *kv = evm_list_create(e, GC_LIST, 2);
                    evm_prop_set_value_by_index(e, kv, 0, *index_2_string(e, i));
                    evm_val_t *t = evm_heap_string_create(e, s+i, 1);
                    evm_prop_set_value_by_index(e, kv, 1, *t);
                    ecma_array_attrs_apply(e, kv);
                    evm_prop_set_value_by_index(e, o, i, *kv);
                }
            } break;
            case 3: {
                for(int i = 0; i < len - 1; i++){
                    evm_prop_set_value_by_index(e, o, i, *index_2_string(e, i));
                }
                evm_prop_set_value_by_index(e, o, len - 1, evm_mk_foreign_string((intptr_t)"length"));
            } break;
            default:
                break;
        }
        ecma_array_attrs_apply(e, o);
        return *o;
    }else{
        return ecma_array(e, p, 0, v);
    }

    return ecma_array(e, p, 0, v);
#endif
    return EVM_VAL_UNDEFINED;
}


evm_val_t ecma_object_keys(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    return ecma_object_keyvalues(e, p, argc, v, 0);
}


evm_val_t ecma_object_values(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    return ecma_object_keyvalues(e, p, argc, v, 1);
}


evm_val_t ecma_object_entries(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    evm_val_t vval= ecma_object_keyvalues(e, p, argc, v, 2);
    return vval;
}


evm_val_t ecma_object_getPrototypeOf(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    (void)e;
    (void)p;
    (void)argc;
    (void)v;
    if(argc == 0) ARG_LENGTH_ERR;
    if (argc >=1 && evm_is_object(v)){
        return * evm_attr_get_by_index(e, v, 0);
    }

    return EVM_VAL_UNDEFINED;
}

evm_val_t ecma_object_getOwnPropertyNames(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    return ecma_object_keyvalues(e, p, argc, v, 3);
}

extern uint16_t EVM_HASH_SETTER;
extern uint16_t EVM_HASH_GETTER;

evm_val_t ecma_object_defineProperty(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    if( argc > 2 && evm_is_object(v) && evm_is_string(v + 1) && evm_is_object(v + 2)){
        evm_val_t * prop = evm_prop_get(e, v, evm_2_string(v + 1), 0);
        if( prop ){
            evm_val_t * key_value = evm_prop_get(e, v + 2, "value", 0);
            if( key_value ){
                *prop = *key_value;
            }

            key_value = evm_prop_get(e, v + 2, "set", 0);
            if( key_value ){
                evm_val_t * setter = evm_attr_get(e, v, ".set");
                if( !setter ){
                    evm_val_t * o = evm_object_create(e, GC_DICT, 1, 0);
                    evm_prop_set(e, o, 0, evm_2_string(v + 1), *key_value);
                    evm_attr_append(e, v, ".set", *o);
                } else {
                    evm_prop_append(e, setter, (char*)evm_2_string(v + 1), key_value);
                }
            }

            key_value = evm_prop_get(e, v + 2, "get", 0);
            if( key_value ){
                evm_val_t * setter = evm_attr_get(e, v, ".get");
                if( !setter ){
                    evm_val_t * o = evm_object_create(e, GC_DICT, 1, 0);
                    evm_prop_set(e, o, 0, evm_2_string(v + 1), *key_value);
                    evm_attr_append(e, v, ".get", *o);
                } else {
                    evm_prop_append(e, setter, (char*)evm_2_string(v + 1), key_value);
                }
            }
        }
    }
	return EVM_VAL_UNDEFINED;
}

evm_val_t ecma_object_forEach(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(e);EVM_UNUSED(argc);EVM_UNUSED(p);
    if(argc > 0) return *v;
    return EVM_VAL_UNDEFINED;
}

evm_val_t * ecma_object_init(evm_t * e){
    evm_val_t * o = evm_native_function_create(e, (evm_native_fn)ecma_object_new, ECMA_OBJECT_ATTR_SIZE);
    evm_attr_set_key_value(e, o, 0, ecma_hash_prototype, *ecma_object_prototype);
    evm_attr_set_key_value(e, o, 1, ecma_hash_create, evm_mk_native((intptr_t)ecma_object_create));
    evm_attr_set_key_value(e, o, 2, ecma_hash_keys, evm_mk_native((intptr_t)ecma_object_keys));
    evm_attr_set_key_value(e, o, 3, ecma_hash_values, evm_mk_native((intptr_t)ecma_object_values));
    evm_attr_set_key_value(e, o, 4, ecma_hash_entries, evm_mk_native((intptr_t)ecma_object_entries));
    evm_attr_set_key_value(e, o, 5, ecma_hash_getPrototypeOf, evm_mk_native((intptr_t)ecma_object_getPrototypeOf));
    evm_attr_set_key_value(e, o, 6, ecma_hash_getOwnPropertyNames, evm_mk_native((intptr_t)ecma_object_getOwnPropertyNames));
    evm_attr_set_key_value(e, o, 7, ecma_hash_defineProperty, evm_mk_native((intptr_t)ecma_object_defineProperty));
    evm_attr_set_key_value(e, o, 8, ecma_hash___proto__, *ecma_function_prototype);
    evm_set_parent(o, ecma_function_prototype);
    return o;
}
#endif
