#include <stdio.h>
#include "LTE_glyphs.h"
#include "LTE_bool.h"
#include "LTE_huff_decoder.h"
#include "LTE_comp_text.h"

#ifndef LTE_TEXT_FILE
#define LTE_TEXT_FILE "LTE_txt.bin"
#endif


struct text_box{
    unsigned char * text;
    unsigned char x_pos;
    unsigned char y_pos;
    // box dimensions (in charecters)
    unsigned char width;
    unsigned char height;
    // where we currently are in the txt
    unsigned char x_focus;
    unsigned char y_focus;
    // text color (r,g,b)
    unsigned char font_r;
    unsigned char font_g;
    unsigned char font_b;
    // background color (r,g,b)
    unsigned char back_r;
    unsigned char back_b;
    unsigned char back_g;
};

void get_page (unsigned int page_number,  FILE * storage, unsigned char * out, unsigned int * size, struct huff_branch * tree);