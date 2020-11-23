#include "hml_style.h"
#include "lvgl.h"
#include "hml_element/hml_base.h"
#include "hml_lvgl_utils.h"
#include "hml_module.h"

/* 设置display屏幕的样式*/
evm_val_t hml_lv_set_display_style(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    EVM_UNUSED(p);
    if( argc >= 1 && evm_is_object(v)){
        evm_val_t * body = evm_prop_get(e, v, "body", 0);
        if (body){
            evm_val_t * bg_img = evm_prop_get(e, body, "background-image", 0);
            if (bg_img && evm_is_string(bg_img)){
                char * appdir = lvgl_app_dir();
                char img[evm_string_len(bg_img) +  strlen(appdir) + 3];
                sprintf(img, "P:%s/%s", lvgl_app_dir() , "./logo.bin");
                if (strstr(img, ".bin")){
                    lv_disp_set_bg_image(lv_disp_get_default(), img);
                }
            }

            evm_val_t * background_color = evm_prop_get(e, body, "background-color", 0);
            if (background_color){
                lv_disp_set_bg_color(lv_disp_get_default(), lvgl_hml_style_get_color(background_color));
            }

            evm_val_t * opacity = evm_prop_get(e, body, "opacity", 0);
            if (opacity && evm_is_number(opacity)) {
                lv_disp_set_bg_opa(lv_disp_get_default(), evm_2_double(opacity));
            }
        }
    }
    return EVM_VAL_UNDEFINED;
}
evm_val_t  hml_obj_set_display(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_string(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        if (!strcmp(evm_2_string(v), "none")){
            lv_obj_set_hidden(obj, true);
        }else{
            lv_obj_set_hidden(obj, false);
        }
    }
    return EVM_VAL_UNDEFINED;
}


evm_val_t  hml_obj_set_x(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_number(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_obj_set_x(obj, evm_2_integer(v));
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_y(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_number(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_obj_set_y(obj, evm_2_integer(v));
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_pos(evm_t * e, evm_val_t *p, int argc, evm_val_t * x, evm_val_t * y){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_number(x) && evm_is_number(y)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_obj_set_pos(obj, evm_2_integer(x), evm_2_integer(y));
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_width(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_number(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_obj_set_width(obj, evm_2_integer(v));
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_size(evm_t * e, evm_val_t *p, int argc, evm_val_t * width, evm_val_t * height){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_number(width) && evm_is_number(height)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_obj_set_size(obj, evm_2_integer(width), evm_2_integer(height));
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_height(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_number(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_obj_set_height(obj, evm_2_integer(v));
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_alignitems(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_string(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        if (!strcmp(evm_2_string(v), "center")){
            lv_cont_set_layout(obj, LV_LAYOUT_ROW_MID);
        }else if (!strcmp(evm_2_string(v), "flex-start")){
            lv_cont_set_layout(obj, LV_LAYOUT_ROW_TOP);
        }else if (!strcmp(evm_2_string(v), "flex-end")){
            lv_cont_set_layout(obj, LV_LAYOUT_ROW_BOTTOM);
        }
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_flexdirection(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_string(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        if (!strcmp(evm_2_string(v), "row")){
            lv_cont_set_layout(obj, LV_LAYOUT_ROW_MID);
        }else if (!strcmp(evm_2_string(v), "column")){
            lv_cont_set_layout(obj, LV_LAYOUT_COLUMN_MID);
        }
    }
    return EVM_VAL_UNDEFINED;
}
evm_val_t  hml_obj_set_backgroundcolor(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && (evm_is_string(v) || evm_is_number(v)) ){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_color_t color = lvgl_hml_style_get_color(v);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        if (lvgl_is_obj_type(obj, "lv_label")){
            lv_style_set_bg_opa(style, LV_STATE_DEFAULT, LV_OPA_COVER);
        }
        lv_style_set_bg_color(style, LV_STATE_DEFAULT, color);
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_gradient_color(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 2 && evm_is_string(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_color_t color = lvgl_hml_style_get_color(v);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_bg_grad_color(style, LV_STATE_DEFAULT, color);
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}


evm_val_t  hml_obj_set_gradient_dir(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_string(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        if (!strcmp(evm_2_string(v), "horizontal")){
            lv_style_set_bg_grad_dir(style, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
        }else{
            lv_style_set_bg_grad_dir(style, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
        }
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_gradient_main_stop(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_bg_main_stop(style, LV_STATE_DEFAULT, evm_2_integer(v));
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_gradient_grad_stop(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_bg_grad_stop(style, LV_STATE_DEFAULT, evm_2_integer(v));
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}


evm_val_t  hml_obj_set_opacity(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_number(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        int opacity = 100 * evm_2_double(v);
        if (lvgl_is_obj_type(obj, "lv_label")){
            lv_style_set_text_opa(style, LV_STATE_DEFAULT, lvgl_hml_style_get_opa(opacity));
        }else if (lvgl_is_obj_type(obj, "lv_img")){
            lv_style_set_image_opa(style, LV_STATE_DEFAULT, lvgl_hml_style_get_opa(opacity));
        }else{
            lv_style_set_bg_opa(style, LV_STATE_DEFAULT, lvgl_hml_style_get_opa(opacity));
        }
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}


evm_val_t  hml_obj_set_bordercolor(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_string(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_color_t color = lvgl_hml_style_get_color(v);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_border_color(style, LV_STATE_DEFAULT, color);
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_borderwidth(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_border_width(style, LV_STATE_DEFAULT, evm_2_integer(v));
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_borderradius(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_radius(style, LV_STATE_DEFAULT, evm_2_integer(v));
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_margin(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_margin_all(style, LV_STATE_DEFAULT, evm_2_integer(v));
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_margin_left(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_margin_left(style, LV_STATE_DEFAULT, evm_2_integer(v));
    }
    return EVM_VAL_UNDEFINED;
}
evm_val_t  hml_obj_set_margin_top(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_margin_top(style, LV_STATE_DEFAULT, evm_2_integer(v));
    }
    return EVM_VAL_UNDEFINED;
}
evm_val_t  hml_obj_set_margin_right(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_margin_right(style, LV_STATE_DEFAULT, evm_2_integer(v));
    }
    return EVM_VAL_UNDEFINED;
}
evm_val_t  hml_obj_set_margin_bottom(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_margin_bottom(style, LV_STATE_DEFAULT, evm_2_integer(v));
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_padding(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_pad_all(style, LV_STATE_DEFAULT, evm_2_integer(v));
        lv_style_set_pad_inner(style, LV_STATE_DEFAULT, 0);
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}
evm_val_t  hml_obj_set_padding_left(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_pad_left(style, LV_STATE_DEFAULT, evm_2_integer(v));
        lv_style_set_pad_inner(style, LV_STATE_DEFAULT, 0);
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}
evm_val_t  hml_obj_set_padding_top(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_pad_top(style, LV_STATE_DEFAULT, evm_2_integer(v));
        lv_style_set_pad_inner(style, LV_STATE_DEFAULT, 0);
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}
evm_val_t  hml_obj_set_padding_right(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_pad_right(style, LV_STATE_DEFAULT, evm_2_integer(v));
        lv_style_set_pad_inner(style, LV_STATE_DEFAULT, 0);
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}
evm_val_t  hml_obj_set_padding_bottom(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        lv_style_set_pad_bottom(style, LV_STATE_DEFAULT, evm_2_integer(v));
        lv_style_set_pad_inner(style, LV_STATE_DEFAULT, 0);
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_text_color(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_string(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        evm_val_t * hml = lvgl_get_hml_obj(obj);
        evm_val_t * name = evm_prop_get(get_global_e(), hml, "name", 0);
        const char * bname = evm_2_string(name);
        lv_color_t color = lvgl_hml_style_get_color(v);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);

        if (!strcmp(bname, "progress")){
            lv_style_t style_indic;
            lv_style_init(&style_indic);
            lv_style_set_bg_color(&style_indic, LV_STATE_DEFAULT, color);
            lv_style_list_t * list = lv_obj_get_style_list(obj, LV_BAR_PART_INDIC);
            _lv_style_list_add_style(list, &style_indic);
        }else{
            lv_style_set_text_color(style, LV_STATE_DEFAULT, color);
            lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
        }
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_text_align(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_string(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        if (lvgl_is_obj_type(obj, "lv_label")){
            if (!strcmp(evm_2_string(v), "left")){
                lv_label_set_align(obj, LV_LABEL_ALIGN_LEFT);
            }else if (!strcmp(evm_2_string(v), "center")){
                lv_label_set_align(obj, LV_LABEL_ALIGN_CENTER);
            }else if (!strcmp(evm_2_string(v), "right")){
                lv_label_set_align(obj, LV_LABEL_ALIGN_RIGHT);
            }else{
                lv_label_set_align(obj, LV_LABEL_ALIGN_AUTO);
            }
        }
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_text_font_size(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        int font_size = evm_2_integer(v);
        lv_style_set_text_font(style, LV_STATE_DEFAULT, lvgl_hml_style_get_font_size(font_size));
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_text_letter_space(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_style_t * style = lvgl_hml_obj_get_style(obj);
        int letter_space = evm_2_integer(v);
        lv_style_set_text_letter_space(style, LV_STATE_DEFAULT, letter_space);
        lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    }
    return EVM_VAL_UNDEFINED;
}

LV_FONT_DECLARE(HYQiHei_65S)
LV_FONT_DECLARE(simsun_30)
LV_FONT_DECLARE(simsun_20)
evm_val_t  hml_obj_set_text_font_family(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 2 && evm_is_string(v) && evm_is_integer(v+1)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);

//        if (!strcmp(evm_2_string(v), "HYQiHei-65S")){
//            lv_style_set_text_font(lvgl_hml_obj_get_style(obj), LV_OBJ_PART_MAIN, &HYQiHei_65S);
//        }else if (!strcmp(evm_2_string(v), "simsun") && evm_2_integer(v+1) == 20){
//            lv_style_set_text_font(lvgl_hml_obj_get_style(obj), LV_OBJ_PART_MAIN, &simsun_20);
//        }else if (!strcmp(evm_2_string(v), "simsun") && evm_2_integer(v+1) == 30){
//            lv_style_set_text_font(lvgl_hml_obj_get_style(obj), LV_OBJ_PART_MAIN, &simsun_30);
//        }
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_text_overflow(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_string(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        if (lvgl_is_obj_type(obj, "lv_label")){
            if (!strcmp(evm_2_string(v), "clip")){
                lv_label_set_long_mode(obj, LV_LABEL_LONG_CROP);
            }else if (!strcmp(evm_2_string(v), "ellipsis")){
                lv_label_set_long_mode(obj, LV_LABEL_LONG_DOT);
            }else if (!strcmp(evm_2_string(v), "longexpand")){
                lv_label_set_long_mode(obj, LV_LABEL_LONG_EXPAND);
            }else if (!strcmp(evm_2_string(v), "longbreak")){
                lv_label_set_long_mode(obj, LV_LABEL_LONG_BREAK);
            }else if (!strcmp(evm_2_string(v), "scroll")){
                lv_label_set_long_mode(obj, LV_LABEL_LONG_SROLL);
                lv_label_set_anim_speed(obj, 40);
            }else if (!strcmp(evm_2_string(v), "scrollcircle")){
                lv_label_set_long_mode(obj, LV_LABEL_LONG_SROLL_CIRC);
                lv_label_set_anim_speed(obj, 40);
            }
        }
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_text_animation_speed(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 1 && evm_is_integer(v)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        if (lvgl_is_obj_type(obj, "lv_label")){
            lv_label_set_anim_speed(obj, evm_2_integer(v));
        }
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_fade_in(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 2 && evm_is_number(v) && evm_is_number(v+1)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_obj_fade_in(obj, evm_2_integer(v), evm_2_integer(v+1));
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_fade_out(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 2 && evm_is_number(v) && evm_is_number(v+1)){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_obj_fade_out(obj, evm_2_integer(v), evm_2_integer(v+1));
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t lv_obj_set_bg_color(lv_obj_t * obj, lv_anim_value_t v)
{
//    lv_style_t * style = lvgl_hml_obj_get_style(obj);
    lvgl_animationcolor_userdata * userdata = (lvgl_animationcolor_userdata *)(obj->ext_attr);
    lv_color_t from = *userdata->from;
    lv_color_t to = *userdata->to;
//    double value = (from.full - to.full) * v / 255;
//    evm_val_t color_v = evm_mk_number(value);
//    lv_color_t c = lvgl_hml_style_get_color(get_global_e(), &color_v);
    lv_color_t c1 = lv_color_mix(from, to, v);
    lv_obj_set_style_local_bg_color(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, c1);
//    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, style);
    return EVM_VAL_UNDEFINED;
}

evm_val_t  hml_obj_set_animation(evm_t * e, evm_val_t *p, int argc, evm_val_t * v){
    EVM_UNUSED(e);
    if( argc >= 9){
        lv_obj_t * obj = (lv_obj_t*)evm_hml_object_get_pointer(p);
        lv_anim_t a;
//        lv_anim_t * b = &a;

        int delay = evm_2_integer(v+1);
        int duration = evm_2_integer(v+2);
        int iteration_count = evm_2_integer(v+3);
        const char * timing_function = evm_2_string(v+4);
        const char * fill_mode = evm_2_string(v+5);
        const char * property = evm_2_string(v+6);
        lv_anim_value_t from, to;
        if (!strcmp(property, "background-color")){
            lv_color_t _from = lvgl_hml_style_get_color(v+7);
            lv_color_t _to = lvgl_hml_style_get_color(v+8);
            lvgl_animationcolor_userdata * userdata = evm_malloc(sizeof(lvgl_animationcolor_userdata));
            userdata->from = &_from;
            userdata->to = &_to;
            obj->ext_attr  = userdata;
            from = 0;
            to = 255;
        }else{
            if (evm_is_number(v+7) && evm_is_number(v+8)){
                from = (lv_anim_value_t)evm_2_integer(v+7);
                to = (lv_anim_value_t)evm_2_integer(v+8);
            }else{
                return EVM_VAL_UNDEFINED;
            }        }

        lv_anim_path_t path;
        lv_anim_path_init(&path);
        if (!strcmp(timing_function, "linear")){
            lv_anim_path_set_cb(&path, lv_anim_path_linear);
        }else if (!strcmp(timing_function, "ease-in")){
            lv_anim_path_set_cb(&path, lv_anim_path_ease_in);
        }else if (!strcmp(timing_function, "ease-out")){
            lv_anim_path_set_cb(&path, lv_anim_path_ease_out);
        }else if (!strcmp(timing_function, "ease-in-out")){
            lv_anim_path_set_cb(&path, lv_anim_path_ease_in_out);
        }else if (!strcmp(timing_function, "overshoot")){
            lv_anim_path_set_cb(&path, lv_anim_path_overshoot);
        }else if (!strcmp(timing_function, "bounce")){
            lv_anim_path_set_cb(&path, lv_anim_path_bounce);
        }else if (!strcmp(timing_function, "step")){
            lv_anim_path_set_cb(&path, lv_anim_path_step);
        }else{
            path = lv_anim_path_def;
        }

        if (!strcmp(property, "background-color")){
            path = lv_anim_path_def;
        }

        lv_anim_init(&a);
        lv_anim_set_var(&a, obj);
        lv_anim_set_time(&a, duration);
        lv_anim_set_delay(&a, delay);
        if (!strcmp(property, "x")){
            lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_x);
        }else if (!strcmp(property, "y")){
            lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
        }else if (!strcmp(property, "width")){
            lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_width);
        }else if (!strcmp(property, "height")){
            lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_height);
        }else if (lvgl_is_obj_type(obj, "lv_img") && !strcmp(property, "zoom")){
            lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_img_set_zoom);
        }else if (lvgl_is_obj_type(obj, "lv_img") && !strcmp(property, "angle")){
            lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_img_set_angle);
            lv_img_set_pivot(obj, 200, 200);
        }else if (!strcmp(property, "background-color")){
            lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_bg_color);
        }

        if (lvgl_is_obj_type(obj, "lv_img") && !strcmp(property, "zoom")){
            lv_anim_set_values(&a, LV_IMG_ZOOM_NONE, to);
        }else{
            lv_anim_set_values(&a, from, to);
        }

        lv_anim_set_path(&a, &path);
        lv_anim_set_repeat_count(&a, iteration_count);
        lv_anim_start(&a);
    }
    return EVM_VAL_UNDEFINED;
}

evm_val_t hml_lv_set_style(evm_t * e, evm_val_t *hml_obj, int argc, evm_val_t * css_obj){
    EVM_UNUSED(e);
    EVM_UNUSED(argc);

    evm_val_t * fontsize = evm_prop_get(e, css_obj, "font-size", 0);

    if (fontsize) {
        hml_obj_set_text_font_size(e, hml_obj, 1, fontsize);
    }

    evm_val_t * font_family = evm_prop_get(e, css_obj, "font-family", 0);

    if (!fontsize){
        evm_val_t size = evm_mk_number(30);
        fontsize = &size;
    }

    if (font_family && fontsize) {
        evm_val_t  args[2];
        args[0] = *font_family;
        args[1] = *fontsize;
        hml_obj_set_text_font_family(e, hml_obj, 2, args);
    }

    evm_val_t * fade_in_time = evm_prop_get(e, css_obj, "fade-in-time", 0);
    evm_val_t * fade_in_delay = evm_prop_get(e, css_obj, "fade-in-delay", 0);
    if (!fade_in_delay){
        evm_val_t delay = evm_mk_number(0);
        fade_in_delay = &delay;
    }
    if (fade_in_time && evm_is_integer(fade_in_time)) {
        evm_val_t  args[2];
        args[0] = *fade_in_time;
        args[1] = *fade_in_delay;
        hml_obj_set_fade_in(e, hml_obj, 2, args);
    }

    evm_val_t * fade_out_time = evm_prop_get(e, css_obj, "fade-out-time", 0);
    evm_val_t * fade_out_delay = evm_prop_get(e, css_obj, "fade-in-delay", 0);
    if (!fade_out_delay){
        evm_val_t delay = evm_mk_number(0);
        fade_out_delay = &delay;
    }
    if (fade_out_time && evm_is_integer(fade_out_time)) {
        evm_val_t  args[2];
        args[0] = *fade_out_time;
        args[1] = *fade_out_delay;
        hml_obj_set_fade_out(e, hml_obj, 1, args);
    }


    evm_val_t * gradient_color = evm_prop_get(e, css_obj, "gradient-color", 0);
    if (gradient_color) {
        hml_obj_set_gradient_color(e, hml_obj, 1, gradient_color);
    }

    evm_val_t * gradient_dir = evm_prop_get(e, css_obj, "gradient-dir", 0);
    if (gradient_dir) {
        hml_obj_set_gradient_dir(e, hml_obj, 1, gradient_dir);
    }

    evm_val_t * gradient_main_stop = evm_prop_get(e, css_obj, "gradient-main-stop", 0);
    if (gradient_main_stop) {
        hml_obj_set_gradient_main_stop(e, hml_obj, 1, gradient_main_stop);
    }

    evm_val_t * gradient_grad_stop = evm_prop_get(e, css_obj, "gradient-grad-stop", 0);
    if (gradient_grad_stop) {
        hml_obj_set_gradient_grad_stop(e, hml_obj, 1, gradient_grad_stop);
    }

    evm_val_t * animation_name = evm_prop_get(e, css_obj, "animation-name", 0);
    if (animation_name && evm_is_string(animation_name)){
        evm_val_t * animation_delay = evm_prop_get(e, css_obj, "animation-delay", 0);
        if (!animation_delay){
            evm_val_t delay = evm_mk_number(0);
            animation_delay = &delay;
        }

        evm_val_t * animation_duration = evm_prop_get(e, css_obj, "animation-duration", 0);
        if (!animation_duration){
            evm_val_t duration = evm_mk_number(0);
            animation_duration = &duration;
        }

        evm_val_t * animation_iteration_count = evm_prop_get(e, css_obj, "animation-iteration-count", 0);
        if (!animation_iteration_count){
            evm_val_t count = evm_mk_number(0);
            animation_iteration_count = &count;
        }

        evm_val_t * animation_timing_function = evm_prop_get(e, css_obj, "animation-timing-function", 0);
        if (!animation_timing_function){
            evm_val_t * function = evm_string_pool_get(get_global_e(), evm_str_insert(get_global_e(), "linear", 0));
            animation_timing_function = function;
        }

        evm_val_t * animation_fill_mode = evm_prop_get(e, css_obj, "animation-fill-mode", 0);
        if (!animation_fill_mode){
            evm_val_t * mode = evm_string_pool_get(get_global_e(), evm_str_insert(get_global_e(), "none", 0));
            animation_fill_mode = mode;
        }

        evm_val_t * animation_property = evm_prop_get(e, css_obj, "animation-property", 0);
        if (!animation_property){
            evm_val_t * property = evm_string_pool_get(get_global_e(), evm_str_insert(get_global_e(), "y", 0));
            animation_property = property;
        }

        evm_val_t * animation_property_from = evm_prop_get(e, css_obj, "animation-property-from", 0);
        if (!animation_property_from){
            evm_val_t property_from = evm_mk_number(0);
            animation_property_from = &property_from;
        }

        evm_val_t * animation_property_to = evm_prop_get(e, css_obj, "animation-property-to", 0);
        if (!animation_property_to){
            evm_val_t property_to = evm_mk_number(0);
            animation_property_to = &property_to;
        }

        evm_val_t  args[9];
        args[0] = *animation_name;
        args[1] = *animation_delay;
        args[2] = *animation_duration;
        args[3] = *animation_iteration_count;
        args[4] = *animation_timing_function;
        args[5] = *animation_fill_mode;
        args[6] = *animation_property;
        args[7] = *animation_property_from;
        args[8] = *animation_property_to;

        hml_obj_set_animation(e, hml_obj, 9, args);
    }

    return EVM_VAL_UNDEFINED;
}
