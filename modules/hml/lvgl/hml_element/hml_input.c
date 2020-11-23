#include "hml_input.h"
#include "lvgl.h"
#include "hml_base.h"
#include "../hml_lvgl_utils.h"
#include "../hml_module.h"

evm_val_t  hml_Input(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    lv_obj_t * obj = NULL;
    lv_obj_t * parent = lv_scr_act();
    if(argc == 1){
        parent = evm_hml_object_get_pointer(v);
    }

    evm_val_t * attributes = evm_prop_get(e, p, "attributes", 0);
    evm_val_t * type = evm_prop_get(e, attributes, "type", 0);
    evm_val_t * value = evm_prop_get(e, attributes, "value", 0);
    evm_val_t * checked = evm_prop_get(e, attributes, "checked", 0);

    if (type && evm_is_string(type)  && !strcmp(evm_2_string(type), "button")){
        obj = (lv_obj_t*)lv_btn_create(parent, NULL);
        if (value && evm_is_string(value)){
            lv_obj_t * label = lv_label_create(obj, NULL);
            lv_label_set_text(label, evm_2_string(value));
        }
        if (checked && evm_is_string(checked)){
            lv_btn_set_checkable(obj, true);
            if (!strcmp(evm_2_string(checked), "true")){
                lv_btn_set_state(obj, LV_BTN_STATE_CHECKED_RELEASED);
            }else{
                lv_btn_set_state(obj, LV_BTN_STATE_RELEASED);
            }
        }

    }else if (type && evm_is_string(type)  && !strcmp(evm_2_string(type), "checkbox")){
        obj = (lv_obj_t*)lv_checkbox_create(parent, NULL);
        if (value && evm_is_string(value)){
            lv_checkbox_set_text(obj, evm_2_string(value));
        }
        if (checked && evm_is_string(checked)){
            lv_btn_set_checkable(obj, true);
            if (!strcmp(evm_2_string(checked), "true")){
                lv_checkbox_set_state(obj, LV_BTN_STATE_CHECKED_RELEASED);
            }else{
                lv_checkbox_set_state(obj, LV_BTN_STATE_RELEASED);
            }
        }
    }else if (type&& evm_is_string(type)  && !strcmp(evm_2_string(type), "radio")){
        obj = (lv_obj_t*)lv_checkbox_create(parent, NULL);
    }
    if( !obj ) return EVM_VAL_UNDEFINED;
    evm_hml_object_set_pointer(p, obj);
    lvgl_hml_obj_add_style(obj, p);
    lv_obj_set_event_cb(obj, lv_hml_event_handler);
    lv_obj_set_click(obj, true);

    return EVM_VAL_UNDEFINED;
}
