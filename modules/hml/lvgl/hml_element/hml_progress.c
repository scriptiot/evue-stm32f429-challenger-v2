#include "hml_progress.h"
#include "lvgl.h"
#include "hml_base.h"
#include "../hml_lvgl_utils.h"
#include "../hml_module.h"

evm_val_t hml_Progress(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    lv_obj_t * obj = NULL;
    lv_obj_t * parent = lv_scr_act();
    if(argc == 1){
        parent = evm_hml_object_get_pointer(v);
    }
    bool isHorizontal = false;
    evm_val_t * attributes = evm_prop_get(e, p, "attributes", 0);
    evm_val_t * type = evm_prop_get(e, attributes, "type", 0);
    if (type && evm_is_string(type)){
        if (!strcmp(evm_2_string(type), "horizontal")){
            obj = (lv_obj_t*)lv_bar_create(parent, NULL);
            isHorizontal = true;
        }else{
            obj = (lv_obj_t*)lv_arc_create(parent, NULL);
        }
    }else{
        obj = (lv_obj_t*)lv_arc_create(parent, NULL);
    }

    if( !obj ) return EVM_VAL_UNDEFINED;
    evm_hml_object_set_pointer(p, obj);
    lvgl_hml_obj_add_style(obj, p);
    lv_obj_set_event_cb(obj, lv_hml_event_handler);
    lv_obj_set_click(obj, true);

    evm_val_t * percent = evm_prop_get(e, attributes, "percent", 0);
    if (!isHorizontal){
        lv_arc_set_adjustable(obj, true);
        lv_arc_set_bg_angles(obj, 0, 360);
        lv_arc_set_angles(obj, 270, 90);

        if (percent && evm_is_number(percent)){
            lv_arc_set_angles(obj, 0, 360 * evm_2_integer(percent) / 100);
        }

        if (percent && evm_is_string(percent)){
            lv_arc_set_angles(obj, 0, 360 * atoi(evm_2_string(percent)) / 100);
        }
    }else{
        lv_bar_set_range(obj, 0, 100);
        if (percent && evm_is_number(percent)){
            lv_bar_set_value(obj, evm_2_integer(percent), LV_ANIM_ON);
        }

        if (percent && evm_is_string(percent)){
            lv_bar_set_value(obj, atoi(evm_2_string(percent)), LV_ANIM_ON);
        }
    }

    return EVM_VAL_UNDEFINED;
}
