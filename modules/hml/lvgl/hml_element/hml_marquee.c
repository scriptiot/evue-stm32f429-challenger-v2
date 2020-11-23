#include "hml_marquee.h"
#include "lvgl.h"
#include "hml_base.h"
#include "../hml_lvgl_utils.h"
#include "../hml_module.h"
#include "lvgl/widgets/lv_marquee.h"

evm_val_t  hml_Marquee(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    lv_obj_t * obj = NULL;
    lv_obj_t * parent = lv_scr_act();
    if(argc == 1){
        parent = evm_hml_object_get_pointer(v);
    }
    obj = (lv_obj_t*)lv_marquee_create(parent, NULL);
    if( !obj ) return EVM_VAL_UNDEFINED;
    evm_hml_object_set_pointer(p, obj);
    lvgl_hml_obj_add_style(obj, p);
    lv_obj_set_event_cb(obj, lv_hml_event_handler);
    lv_obj_set_click(obj, true);

    lv_marquee_set_long_mode(obj, LV_LABEL_LONG_SROLL_CIRC);     /*Circular scroll*/

    evm_val_t * attributes = evm_prop_get(e, p, "attributes", 0);
    evm_val_t * scrollamount = evm_prop_get(e, attributes, "scrollamount", 0);
    if (scrollamount && evm_is_string(scrollamount)){
        lv_marquee_set_anim_speed(obj, atoi(evm_2_string(scrollamount)));
    }

    if (scrollamount && evm_is_integer(scrollamount)){
        lv_marquee_set_anim_speed(obj, evm_2_integer(scrollamount));
    }

    evm_val_t * value = evm_prop_get(e, p, "value", 0);
    if (value && evm_is_string(value)){
        lv_marquee_set_text(obj, evm_2_string(value));
    }

    lv_point_t size = lv_marquee_get_text_size(obj);
    lv_obj_set_size(obj, size.x, size.y);

    return EVM_VAL_UNDEFINED;
}
