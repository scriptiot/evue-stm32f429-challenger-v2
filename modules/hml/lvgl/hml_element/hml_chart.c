#include "hml_chart.h"
#include "lvgl.h"
#include "hml_base.h"
#include "../hml_lvgl_utils.h"
#include "../hml_module.h"

evm_val_t  hml_Chart(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
   EVM_UNUSED(e);
   lv_obj_t * obj = NULL;
   lv_obj_t * parent = lv_scr_act();
   if(argc == 1){
       parent = evm_hml_object_get_pointer(v);
   }
   obj = (lv_obj_t*)lv_chart_create(parent, NULL);
   if( !obj ) return EVM_VAL_UNDEFINED;
   evm_hml_object_set_pointer(p, obj);
   lvgl_hml_obj_add_style(obj, p);
   lv_obj_set_event_cb(obj, lv_hml_event_handler);
   lv_obj_set_click(obj, true);

   lv_obj_set_size(obj, 200, 150);
   lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
   lv_chart_set_type(obj, LV_CHART_TYPE_LINE);   /*Show lines and points too*/

   /*Add a faded are effect*/
   lv_obj_set_style_local_bg_opa(obj, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, LV_OPA_50); /*Max. opa.*/
   lv_obj_set_style_local_bg_grad_dir(obj, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
   lv_obj_set_style_local_bg_main_stop(obj, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 255);    /*Max opa on the top*/
   lv_obj_set_style_local_bg_grad_stop(obj, LV_CHART_PART_SERIES, LV_STATE_DEFAULT, 0);      /*Transparent on the bottom*/


   /*Add two data series*/
   lv_chart_series_t * ser1 = lv_chart_add_series(obj, LV_COLOR_RED);
   lv_chart_series_t * ser2 = lv_chart_add_series(obj, LV_COLOR_GREEN);

   /*Set the next points on 'ser1'*/
   lv_chart_set_next(obj, ser1, 31);
   lv_chart_set_next(obj, ser1, 66);
   lv_chart_set_next(obj, ser1, 10);
   lv_chart_set_next(obj, ser1, 89);
   lv_chart_set_next(obj, ser1, 63);
   lv_chart_set_next(obj, ser1, 56);
   lv_chart_set_next(obj, ser1, 32);
   lv_chart_set_next(obj, ser1, 35);
   lv_chart_set_next(obj, ser1, 57);
   lv_chart_set_next(obj, ser1, 85);

   /*Directly set points on 'ser2'*/
   ser2->points[0] = 92;
   ser2->points[1] = 71;
   ser2->points[2] = 61;
   ser2->points[3] = 15;
   ser2->points[4] = 21;
   ser2->points[5] = 35;
   ser2->points[6] = 35;
   ser2->points[7] = 58;
   ser2->points[8] = 31;
   ser2->points[9] = 53;

   lv_chart_refresh(obj); /*Required after direct set*/

   return EVM_VAL_UNDEFINED;
}
