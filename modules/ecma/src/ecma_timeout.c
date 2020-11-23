#include "ecma.h"

#define ECMA_TIMEOUT_PERIOD 0
#define ECMA_TIMEOUT_ONSHOT 1


typedef struct ecma_timeout_t {
    int id;
    int period;
    int oneshot;
    int count;
}ecma_timeout_t;

static ecma_timeout_t ecma_timeouts[CONFIG_EVM_ECMA_TIMEOUT_SIZE];
static evm_val_t * ecma_timeout_ref_list;

int ecma_timout_add(evm_t * e, int period, int oneshot, evm_val_t * ref){
    for(uint32_t i = 0; i < CONFIG_EVM_ECMA_TIMEOUT_SIZE; i++){
        evm_val_t * v = evm_list_get(e, ecma_timeout_ref_list, i);
        if( evm_is_undefined(v) ){
            evm_list_set(e, ecma_timeout_ref_list, i, *ref);

            ecma_timeouts[i].id = i;
            ecma_timeouts[i].period = period;
            ecma_timeouts[i].oneshot = oneshot;
            ecma_timeouts[i].count = 0;
            return i;
        }
    }
    return -1;
}

int ecma_timeout_remove(evm_t * e, int id){
    if( id >= CONFIG_EVM_ECMA_TIMEOUT_SIZE || id < 0) return ec_index;
    evm_list_set(e, ecma_timeout_ref_list, id, EVM_VAL_UNDEFINED);
    ecma_timeouts[id].id = -1;
    return ec_ok;
}

static evm_val_t ecma_timeout_setInterval(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(e);EVM_UNUSED(p);
    if( argc > 1 && evm_is_number(v + 1) && evm_is_script(v) ){
        int id = ecma_timout_add(e, evm_2_integer(v + 1), ECMA_TIMEOUT_PERIOD, v);
        return evm_mk_number(id);
    }
    return EVM_VAL_UNDEFINED;
}

static evm_val_t ecma_timeout_clearInterval(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(e);EVM_UNUSED(p);
    if( argc > 0 && evm_is_number(v) ){
        int id = evm_2_integer(v);
        ecma_timeout_remove(e, id);
    }
    return EVM_VAL_UNDEFINED;
}

static evm_val_t ecma_timeout_setTimeout(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(e);EVM_UNUSED(p);
    if( argc > 1 && evm_is_number(v + 1) && evm_is_script(v) ){
        int id = ecma_timout_add(e, evm_2_integer(v + 1), ECMA_TIMEOUT_ONSHOT, v);
        return evm_mk_number(id);
    }
    return EVM_VAL_UNDEFINED;
}

static evm_val_t ecma_timeout_clearTimeout(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    EVM_UNUSED(e);EVM_UNUSED(p);
    if( argc > 0 && evm_is_number(v) ){
        int id = evm_2_integer(v);
        ecma_timeout_remove(e, id);
    }
    return EVM_VAL_UNDEFINED;
}

void ecma_timeout_poll(evm_t * e){
    int len = evm_list_len(ecma_timeout_ref_list);
    for(int i = 0; i < len; i++){
        evm_val_t * ref = evm_list_get(e, ecma_timeout_ref_list, i);
        if( evm_is_script(ref) && ecma_timeouts[i].id != -1){
			
            if( ecma_timeouts[i].count >= ecma_timeouts[i].period ){
                ecma_timeouts[i].count = 0;
                evm_run_callback(e, ref, &e->scope, NULL, 0);
                if( ecma_timeouts[i].oneshot == ECMA_TIMEOUT_ONSHOT ){
                    ecma_timeouts[i].id = -1;
                    evm_list_set(e, ecma_timeout_ref_list,i, EVM_VAL_UNDEFINED);
                }
            }
			ecma_timeouts[i].count += 10;
        }
    }
}

int ecma_timeout_init(evm_t * e){
    ecma_timeout_ref_list = evm_list_create(e, GC_LIST, CONFIG_EVM_ECMA_TIMEOUT_SIZE);
    for(int i = 0; i < CONFIG_EVM_ECMA_TIMEOUT_SIZE; i++) evm_list_set(e, ecma_timeout_ref_list, i, EVM_VAL_UNDEFINED);
    evm_builtin_t natives[] = {
        {"setInterval", evm_mk_native( (intptr_t)ecma_timeout_setInterval )},
        {"clearInterval", evm_mk_native( (intptr_t)ecma_timeout_clearInterval )},
        {"setTimeout", evm_mk_native( (intptr_t)ecma_timeout_setTimeout )},
        {"clearTimeout", evm_mk_native( (intptr_t)ecma_timeout_clearTimeout )},
        {NULL, EVM_VAL_UNDEFINED}
    };
    return evm_native_add(e, natives);
}
