#include "hml_image.h"
#include "lvgl.h"
#include "hml_base.h"
#include "../hml_lvgl_utils.h"
#include "../hml_module.h"

evm_val_t  hml_Image(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    lv_obj_t * obj = NULL;
    lv_obj_t * parent = lv_scr_act();
    if(argc == 1){
        parent = evm_hml_object_get_pointer(v);
    }
    obj = (lv_obj_t*)lv_img_create(parent, NULL);
    if( !obj ) return EVM_VAL_UNDEFINED;
    evm_hml_object_set_pointer(p, obj);
    lvgl_hml_obj_add_style(obj, p);
    lv_obj_set_event_cb(obj, lv_hml_event_handler);
    lv_obj_set_click(obj, true);
    lv_obj_set_parent_event(obj, true);
    lv_img_set_auto_size(obj, true);

    evm_val_t * attributes = evm_prop_get(e, p, "attributes", 0);
    evm_val_t * src = evm_prop_get(e, attributes, "src", 0);

    if (src && evm_is_string(src)){
        char * appdir = lvgl_app_dir();
        char img[evm_string_len(src) +  strlen(appdir) + 3];
        const char * filename = evm_2_string(src);
        sprintf(img, "P:/%s", filename);
        if (strstr(img, ".bin") || strstr(img, ".png")){
            lv_img_set_src(obj, img);
        }
    }
    return EVM_VAL_UNDEFINED;
}
