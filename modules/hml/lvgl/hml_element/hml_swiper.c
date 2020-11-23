#include "hml_swiper.h"
#include "lvgl.h"
#include "hml_base.h"
#include "../hml_lvgl_utils.h"
#include "../hml_module.h"


static void lv_hml_swiper_event_handler(lv_obj_t * obj, lv_event_t event)
{
    evm_t * e = get_global_e();
    evm_val_t * hml = lvgl_get_hml_obj(obj);
    evm_val_t * attributes = evm_prop_get(e, hml, "attributes", 0);
    evm_val_t * change = evm_prop_get(e, attributes, "onchange", 0);
    evm_val_t * swipe = evm_prop_get(e, attributes, "onswipe", 0);

    hml_object_t *  hml_ext_data = (hml_object_t *)evm_object_get_ext_data(hml);
    evm_val_t viewmodel = hml_ext_data->viewmodel;

    if(change && evm_is_string(change) && event == LV_EVENT_VALUE_CHANGED) {
        lv_coord_t x, y, index = 0;
        lv_tileview_get_tile_act(obj, &x, &y);
        if (lv_page_get_scrl_layout(obj) == LV_LAYOUT_ROW_MID){
            index = x;
        }else if (lv_page_get_scrl_layout(obj) == LV_LAYOUT_COLUMN_MID){
            index = y;
        }
        evm_val_t  changeargs[2];
        changeargs[0] = *hml;
        changeargs[1] = evm_mk_number(index);
        lvgl_hml_run_callback(e, obj, viewmodel, evm_2_string(change), 2, changeargs);
    }else if (swipe && evm_is_string(swipe) && event == LV_EVENT_PRESSING){
        lv_gesture_dir_t  dircetion  = lv_indev_get_gesture_dir(lv_indev_get_act());
        evm_val_t  dircetion_args[2];
        dircetion_args[0] = *hml;
        if (dircetion == LV_GESTURE_DIR_LEFT){
            int key = evm_str_insert(e, "left", 0);
            dircetion_args[1] = *evm_string_pool_get(e, key);
        }else if (dircetion == LV_GESTURE_DIR_TOP){
            int key = evm_str_insert(e, "top", 0);
            dircetion_args[1] = *evm_string_pool_get(e, key);
        }else if (dircetion == LV_GESTURE_DIR_RIGHT){
            int key = evm_str_insert(e, "right", 0);
            dircetion_args[1] = *evm_string_pool_get(e, key);
        }else if (dircetion == LV_GESTURE_DIR_BOTTOM){
            int key = evm_str_insert(e, "bottom", 0);
            dircetion_args[1] = *evm_string_pool_get(e, key);
        }

        lvgl_hml_run_callback(e, obj, viewmodel, evm_2_string(swipe), 2, dircetion_args);
    }

    lv_hml_event_handler(obj, event);
}

evm_val_t  hml_Swiper(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    lv_obj_t * obj = NULL;
    lv_obj_t * parent = lv_scr_act();
    if(argc == 1){
        parent = evm_hml_object_get_pointer(v);
    }
    obj = (lv_obj_t*)lv_tileview_create(parent, NULL);
    if( !obj ) return EVM_VAL_UNDEFINED;
    evm_hml_object_set_pointer(p, obj);
    lvgl_hml_obj_add_style(obj, p);
    lv_obj_set_event_cb(obj, lv_hml_swiper_event_handler);

    lv_tileview_set_edge_flash(obj, true);

    evm_val_t * attributes = evm_prop_get(e, p, "attributes", 0);
    evm_val_t * vertical = evm_prop_get(e, attributes, "vertical", 0);
    bool isVertical = false;
    if (vertical){

        if (evm_2_boolean(vertical)){
            isVertical = true;
        }else{
            isVertical = false;
        }
    }
    evm_val_t * elements = evm_prop_get(e, p, "elements", 0);
    int count = evm_prop_len(elements) + 1;
    static lv_point_t valid_pos[48];
    if (isVertical){
        lv_page_set_scrl_layout(obj, LV_LAYOUT_COLUMN_MID);
        for (int i=0; i < count; i++){
            lv_point_t pageIndex;
            pageIndex.x = 0;
            pageIndex.y = i;
            valid_pos[i] = pageIndex;
        }
    }else{
        lv_page_set_scrl_layout(obj, LV_LAYOUT_ROW_MID);
        for (int i=0; i < count; i++){
            lv_point_t pageIndex;
            pageIndex.x = i;
            pageIndex.y = 0;
            valid_pos[i] = pageIndex;
        }
    }

    lv_tileview_set_valid_positions(obj, valid_pos, count);
    lv_page_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_DRAG);

    evm_val_t * index = evm_prop_get(e, attributes, "index", 0);
    if (index && evm_is_string(index)){
        lv_point_t activeIndex;
        if (isVertical){
            activeIndex.x = 0;
            activeIndex.y = atoi(evm_2_string(index));
        }else{
            activeIndex.x = atoi(evm_2_string(index));
            activeIndex.y = 0;
        }
        lv_tileview_set_tile_act(obj, activeIndex.x, activeIndex.y, LV_ANIM_ON);
    }
    if (index && evm_is_integer(index)){
        lv_point_t activeIndex;
        if (isVertical){
            activeIndex.x = 0;
            activeIndex.y = evm_2_integer(index);
        }else{
            activeIndex.x = evm_2_integer(index);
            activeIndex.y = 0;
        }
        lv_tileview_set_tile_act(obj, activeIndex.x, activeIndex.y, LV_ANIM_ON);
    }
    return EVM_VAL_UNDEFINED;
}
