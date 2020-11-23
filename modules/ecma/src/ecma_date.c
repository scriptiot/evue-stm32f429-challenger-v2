#include "ecma.h"
#include <time.h>

evm_val_t * date_object;

time_t date_time;
struct tm * pdate_time;
struct timeval tms;

evm_val_t ecma_date_getDay(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    (void)e;
    (void)p;
    (void)argc;
    (void)v;
    return evm_mk_number(pdate_time->tm_mday);
}

evm_val_t ecma_date_getMonth(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    (void)e;
    (void)p;
    (void)argc;
    (void)v;
    return evm_mk_number(pdate_time->tm_mon);
}

evm_val_t ecma_date_getHours(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    (void)e;
    (void)p;
    (void)argc;
    (void)v;
    return evm_mk_number(pdate_time->tm_hour);
}

evm_val_t ecma_date_getMinutes(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    (void)e;
    (void)p;
    (void)argc;
    (void)v;
    return evm_mk_number(pdate_time->tm_min);
}

evm_val_t ecma_date_getSeconds(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    (void)e;
    (void)p;
    (void)argc;
    (void)v;
    return evm_mk_number(pdate_time->tm_sec);
}

evm_val_t ecma_date_getMilliseconds(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    (void)e;
    (void)p;
    (void)argc;
    (void)v;
    return evm_mk_number(tms.tv_usec/1000);
}

evm_val_t ecma_date(evm_t * e, evm_val_t * p, int argc, evm_val_t * v){
    (void)e;
    (void)p;
    (void)argc;
    (void)v;
    time(&date_time);
    pdate_time = localtime(&date_time);
    gettimeofday(&tms,NULL);
    return *date_object;
}


evm_val_t * ecma_date_init(evm_t * e){
    date_object = evm_object_create(e, GC_DICT, 6, 0);
    evm_prop_set(e, date_object, 0, "getMonth", evm_mk_native((intptr_t)ecma_date_getMonth));
    evm_prop_set(e, date_object, 1, "getDay", evm_mk_native((intptr_t)ecma_date_getDay));
    evm_prop_set(e, date_object, 2, "getHours", evm_mk_native((intptr_t)ecma_date_getHours));
    evm_prop_set(e, date_object, 3, "getMinutes", evm_mk_native((intptr_t)ecma_date_getMinutes));
    evm_prop_set(e, date_object, 4, "getSeconds", evm_mk_native((intptr_t)ecma_date_getSeconds));
    evm_prop_set(e, date_object, 5, "getMilliseconds", evm_mk_native((intptr_t)ecma_date_getMilliseconds));
    evm_val_t * o = evm_native_function_create(e, (evm_native_fn)ecma_date, 1);
    evm_attr_set(e, o, 0, "prototype", *ecma_object_prototype);
    return o;
}
