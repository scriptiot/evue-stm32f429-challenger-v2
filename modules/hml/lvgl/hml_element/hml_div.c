#include "hml_div.h"
#include "lvgl.h"
#include "hml_base.h"
#include "../hml_lvgl_utils.h"
#include "../hml_module.h"


evm_val_t  hml_Div(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    lv_obj_t * obj = NULL;
    lv_obj_t * parent = lv_scr_act();
    if(argc == 1){
        parent = evm_hml_object_get_pointer(v);
    }
    obj = (lv_obj_t*)lv_cont_create(parent, NULL);
    if( !obj ) return EVM_VAL_UNDEFINED;
    evm_hml_object_set_pointer(p, obj);
    lvgl_hml_obj_add_style(obj, p);

    lv_obj_set_click(obj, true);
    lv_obj_set_parent_event(obj, true);

    lv_obj_set_event_cb(obj, lv_hml_event_handler);
    if (lvgl_is_obj_type(parent, "lv_tileview")){
        lv_tileview_add_element(parent, obj);
//        lv_obj_set_drag(obj, true);
//        lv_obj_set_gesture_parent(obj, true);
//        evm_val_t * attributes = evm_prop_get(e, v, "attributes", 0);
//        evm_val_t * vertical = evm_prop_get(e, attributes, "vertical", 0);
////        if (vertical){
////            if (!strcmp(evm_2_string(vertical), "true")){
//////                lv_obj_set_size();
////            }else{
//////                lv_obj_set_size();
////            }
////        }

    }
    return EVM_VAL_UNDEFINED;
}
