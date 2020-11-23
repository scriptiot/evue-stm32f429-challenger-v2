#include "hml_picker_view.h"
#include "lvgl.h"
#include "hml_base.h"
#include "../hml_lvgl_utils.h"
#include "../hml_module.h"

evm_val_t  hml_PickerView(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    lv_obj_t * obj = NULL;
    lv_obj_t * parent = lv_scr_act();
    if(argc == 1){
        parent = evm_hml_object_get_pointer(v);
    }
    obj = (lv_obj_t*)lv_roller_create(parent, NULL);
    if( !obj ) return EVM_VAL_UNDEFINED;
    evm_hml_object_set_pointer(p, obj);
    lvgl_hml_obj_add_style(obj, p);
    lv_obj_set_event_cb(obj, lv_hml_event_handler);
    lv_obj_set_click(obj, true);

    evm_val_t * attributes = evm_prop_get(e, p, "attributes", 0);
    evm_val_t * type = evm_prop_get(e, attributes, "type", 0);
    evm_val_t * range = evm_prop_get(e, attributes, "range", 0);
    evm_val_t * selected = evm_prop_get(e, attributes, "selected", 0);

    if (selected && evm_is_string(selected)){
        lv_roller_set_selected(obj, atoi(evm_2_string(selected)), LV_ANIM_ON);
        int count = evm_list_len(range);
        int len = 0;
        for(int i=0; i < count; i++){
            len += evm_string_len(evm_list_get(get_global_e(), range, i));
        }
        char options[2*len -1 ];
        for(int i=0; i < count; i++){
            sprintf(options, "%s\n", evm_2_string( range + i));
        }
    }

    return EVM_VAL_UNDEFINED;
}
