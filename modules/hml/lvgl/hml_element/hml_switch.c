#include "hml_switch.h"
#include "lvgl.h"
#include "hml_base.h"
#include "../hml_lvgl_utils.h"
#include "../hml_module.h"

evm_val_t  hml_Switch(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    lv_obj_t * obj = NULL;
    lv_obj_t * parent = lv_scr_act();
    if(argc == 1){
        parent = evm_hml_object_get_pointer(v);
    }
    obj = (lv_obj_t*)lv_switch_create(parent, NULL);
    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
    if( !obj ) return EVM_VAL_UNDEFINED;
    evm_hml_object_set_pointer(p, obj);
    lvgl_hml_obj_add_style(obj, p);
    lv_obj_set_event_cb(obj, lv_hml_event_handler);
    lv_obj_set_click(obj, true);

    evm_val_t * attributes = evm_prop_get(e, p, "attributes", 0);
    evm_val_t * checked = evm_prop_get(e, attributes, "checked", 0);
    if (checked && evm_is_string(checked)){
        if (!strcmp(evm_2_string(checked), "true")){
            lv_switch_on(obj, LV_ANIM_ON);
        }else{
            lv_switch_off(obj, LV_ANIM_OFF);
        }
    }
    return EVM_VAL_UNDEFINED;
}
