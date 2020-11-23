#include "hml_list.h"
#include "lvgl.h"
#include "hml_base.h"
#include "../hml_lvgl_utils.h"
#include "../hml_module.h"


evm_val_t  hml_List(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    lv_obj_t * obj = NULL;
    lv_obj_t * parent = lv_scr_act();
    if(argc == 1){
        parent = evm_hml_object_get_pointer(v);
    }
    obj = (lv_obj_t*)lv_page_create(parent, NULL);
    if( !obj ) return EVM_VAL_UNDEFINED;
    evm_hml_object_set_pointer(p, obj);
    lvgl_hml_obj_add_style(obj, p);
    lv_obj_set_event_cb(obj, lv_hml_event_handler);

    lv_page_set_scrollable_fit2(obj, LV_FIT_PARENT, LV_FIT_TIGHT);
    lv_page_set_scrl_layout(obj, LV_LAYOUT_CENTER);
    lv_page_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_DRAG);
    lv_page_set_edge_flash(obj, true);
    return EVM_VAL_UNDEFINED;
}
