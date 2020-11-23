#include "hml_text.h"
#include "lvgl.h"
#include "hml_base.h"
#include "../hml_lvgl_utils.h"
#include "../hml_module.h"

evm_val_t  hml_Text(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    lv_obj_t * obj = NULL;
    lv_obj_t * parent = lv_scr_act();
    if(argc == 1) parent = evm_hml_object_get_pointer(v);
    obj = (lv_obj_t*)lv_label_create(parent, NULL);
    if( !obj ) return EVM_VAL_UNDEFINED;
    evm_hml_object_set_pointer(p, obj);
    lvgl_hml_obj_add_style(obj, p);

    lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);

    lv_obj_set_event_cb(obj, lv_hml_event_handler);
    lv_obj_set_click(obj, true);
    lv_obj_set_parent_event(obj, true);
    return EVM_VAL_UNDEFINED;
}


evm_val_t  hml_Text_text(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_string(v) ){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_label_set_text(obj, evm_2_string(v));
    }else if ( argc >= 1 && evm_is_integer(v) ){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        char text[32];
        sprintf(text, "%ld", evm_2_integer(v));
        lv_label_set_text(obj, text);
    }
    return EVM_VAL_UNDEFINED;
}
