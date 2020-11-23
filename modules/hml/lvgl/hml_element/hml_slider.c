#include "hml_slider.h"
#include "lvgl.h"
#include "hml_base.h"
#include "../hml_lvgl_utils.h"
#include "../hml_module.h"

evm_val_t  hml_Slider(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    lv_obj_t * obj = NULL;
    lv_obj_t * parent = lv_scr_act();
    if(argc == 1){
        parent = evm_hml_object_get_pointer(v);
    }
    obj = (lv_obj_t*)lv_slider_create(parent, NULL);
    if( !obj ) return EVM_VAL_UNDEFINED;
    evm_hml_object_set_pointer(p, obj);
    lvgl_hml_obj_add_style(obj, p);
    lv_obj_set_event_cb(obj, lv_hml_event_handler);
    lv_obj_set_click(obj, true);

    evm_val_t * attributes = evm_prop_get(e, p, "attributes", 0);
    evm_val_t * min = evm_prop_get(e, attributes, "min", 0);
    evm_val_t * max = evm_prop_get(e, attributes, "max", 0);
    evm_val_t * value = evm_prop_get(e, attributes, "value", 0);

    lv_slider_set_range(obj, lv_slider_get_min_value(obj), 100);

    if (min && evm_is_number(min)){
        lv_slider_set_range(obj, evm_2_integer(min), lv_slider_get_max_value(obj));
    }
    if (max && evm_is_number(max)){
        lv_slider_set_range(obj, lv_slider_get_min_value(obj), evm_2_integer(max));
    }
    if (value && evm_is_number(value)){
        lv_slider_set_value(obj, evm_2_integer(value), LV_ANIM_ON);
    }

    if (min && evm_is_string(min)){
        lv_slider_set_range(obj, atoi(evm_2_string(min)), lv_slider_get_max_value(obj));
    }
    if (max && evm_is_string(max)){
        lv_slider_set_range(obj, lv_slider_get_min_value(obj), atoi(evm_2_string(max)));
    }
    if (value && evm_is_string(value)){
        lv_slider_set_value(obj, atoi(evm_2_string(value)), LV_ANIM_ON);
    }


    return EVM_VAL_UNDEFINED;
}
