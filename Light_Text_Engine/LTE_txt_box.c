#include "LTE_txt_box.h"

void get_page (unsigned int page_number,  FILE * storage, unsigned char * out, unsigned int * size, struct huff_branch * tree){
    unsigned int byte_number = TABLE_OF_CONTENTS[page_number];
    unsigned char byte_off = TABLE_OF_CONTENTS_OFFSET[page_number];
    fseek(storage, byte_number, SEEK_SET);
    unsigned char current_block = fgetc(storage);
    unsigned int read_pos= 0;
    unsigned int write_pos = 0;
    do{
        unsigned char current = HUFF_ROOT;
        while (current >= ALFA_SIZE){
            unsigned char choice = (current_block >> (7 - byte_off)) & 0x01;
            if (choice){
                current = tree[current].right;
            }
            else {
                current = tree[current].left;
            }
            byte_off++;
            if (byte_off > 7){
                current_block = fgetc(storage);
                read_pos++;
                byte_off = 0;
            }
        }
        //printf("%x,", current);
        out[write_pos] = current;
        write_pos++;
    }
    while (read_pos < TABLE_OF_CONTENTS[page_number + 1] - TABLE_OF_CONTENTS[page_number]);
    *size = write_pos;
}