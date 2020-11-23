#ifndef QML_LVGL_UTILS_H
#define QML_LVGL_UTILS_H

#include <lvgl.h>
#include "hml_module.h"

/**
 * @brief lv_obj_t自定义的用户数据结构体
 * @param style, 样式对象
 * @param hml_obj, hml对象
 */
typedef struct user_data{
    lv_style_t * style;
    evm_val_t  * hml_obj;
} lvgl_userdata;

/**
 * @brief 动画color的数据结构体
 * @param from, 起始颜色对象
 * @param to, 结束颜色对象
 */
typedef struct animation_color_data{
    lv_color_t * from;
    lv_color_t * to;
} lvgl_animationcolor_userdata;

/**
 * @brief lvgl对象添加样式style对象，存储到userdata中
 * @param obj, lvgl ui 对象
 * @param hml, lvgl ui 对象对应的hml对象
 */
lv_style_t * lvgl_hml_obj_add_style(lv_obj_t * obj, evm_val_t * hml);

/**
 * @brief 获取lvgl对象的样式style对象
 * @param obj, lvgl ui 对象
 * @return lvgl ui 对象的style对象
 */
lv_style_t * lvgl_hml_obj_get_style(lv_obj_t * obj);

/**
 * @brief 获取lvgl对象的样式hml对象
 * @param obj, lvgl ui 对象
 * @return lvgl ui 对象对应的hml对象
 */
evm_val_t * lvgl_get_hml_obj(lv_obj_t * obj);

/**
 * @brief 根据数值返回lvgl的透明度枚举值
 * @param opacity, 数值10、20、30...100
 * @return lv_opa_t, lvgl的透明度枚举值
 */
lv_opa_t lvgl_hml_style_get_opa(int opacity);

/**
 * @brief 根据字符串red或#FF0000 返回lvgl的color对象
 * @param v, evm字符串对象或者是整形对象
 * @return lvgl的颜色对象lv_color_t
 */
lv_color_t lvgl_hml_style_get_color(evm_val_t * v);

/**
 * @brief 根据字体数字大小返回lvgl的font对象
 * @param font_size, 字体数字大小
 * @return lvgl的字体对象lv_font_t指针
 */
lv_font_t *lvgl_hml_style_get_font_size(int font_size);


char * lvgl_hml_get_symbol(evm_t * e, evm_val_t * v);
lv_chart_type_t lvgl_hml_get_ChartType(evm_t * e, evm_val_t * v);

#endif
