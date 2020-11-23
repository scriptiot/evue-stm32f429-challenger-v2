#include "hml_base.h"
#include "lvgl.h"
#include "../hml_module.h"
#include "../hml_module.h"

static evm_t * global_e;

evm_t * get_global_e(){
    return global_e;
}

void set_global_e(evm_t * e){
    global_e = e;
}

char * lvgl_app_dir(){
    lv_obj_user_data_t data = lv_obj_get_user_data(lv_scr_act());
    if (data) {
       return (char * )lv_obj_get_user_data(lv_scr_act());
    }
    return ".";
}

bool lvgl_is_obj_type(lv_obj_t * obj, const char* type_name)
{
    lv_obj_type_t type;

    lv_obj_get_type(obj, &type);
    uint8_t cnt;
    for(cnt = 0; cnt < LV_MAX_ANCESTOR_NUM; cnt++) {
        if(type.type[cnt] == NULL) break;
        if(!strcmp(type.type[cnt], type_name)) return true;
    }
    return false;
}

void lvgl_hml_run_callback(evm_t * e, lv_obj_t * obj, evm_val_t  viewmodel, const char * name, int argc, evm_val_t * args){
    EVM_UNUSED(obj);
    evm_val_t * m_clicked_fn = evm_prop_get(e, &viewmodel, name, 0);
    if( m_clicked_fn != NULL){
        evm_run_callback(e, m_clicked_fn, &viewmodel, args, argc);
    }
}


void lv_hml_event_handler(lv_obj_t * obj, lv_event_t event)
{
    evm_t * e = get_global_e();
    evm_val_t * hml = lvgl_get_hml_obj(obj);
    evm_val_t * attributes = evm_prop_get(e, hml, "attributes", 0);
    evm_val_t * click = evm_prop_get(e, attributes, "onclick", 0);
    evm_val_t * press = evm_prop_get(e, attributes, "onpress", 0);
    evm_val_t * release = evm_prop_get(e, attributes, "onrelease", 0);
    evm_val_t * longpress = evm_prop_get(e, attributes, "onlongpress", 0);

    hml_object_t *  hml_ext_data = (hml_object_t *)evm_object_get_ext_data(hml);
    evm_val_t viewmodel = hml_ext_data->viewmodel;

    evm_val_t  args[3];
    args[0] = *hml;
    lv_point_t globalClickPoint;
    lv_indev_get_point(lv_indev_get_act(), &globalClickPoint);
    lv_coord_t x = globalClickPoint.x;
    x -= obj->coords.x1;
    lv_coord_t y = globalClickPoint.y;
    y -= obj->coords.y1;
    args[1] = evm_mk_number(x);
    args[2] = evm_mk_number(y);


    if (click && evm_is_string(click) && event == LV_EVENT_CLICKED){
        lvgl_hml_run_callback(e, obj, viewmodel, evm_2_string(click), 3, args);
    }else if (press && evm_is_string(press) && event == LV_EVENT_PRESSED){
        lvgl_hml_run_callback(e, obj, viewmodel, evm_2_string(press), 3, args);
    }else if (release && evm_is_string(release) && event == LV_EVENT_RELEASED){
        lvgl_hml_run_callback(e, obj, viewmodel, evm_2_string(release), 3, args);
    }else if (longpress && evm_is_string(longpress) && event == LV_EVENT_LONG_PRESSED){
        lvgl_hml_run_callback(e, obj, viewmodel, evm_2_string(longpress), 3, args);
    }
}
