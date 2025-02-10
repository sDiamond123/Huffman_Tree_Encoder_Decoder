#include "LTE_huff_decoder.h"
#include <stdio.h>
/*
The huffman itself
117,104,111,109,120,106,105,112,116,85,95,109,107,114,118,105,89,114,
115,119,108,98,104,93,103,72,100,64,88,102,80,64,65,123,65,66,92,92,66,
67,83,96,86,88,86,83,84,81,77,80,89,67,68,84,72,68,69,101,69,70,70,102,
71,71,73,73,74,74,75,75,76,76,77,78,78,79,79,81,82,82,85,87,87,90,90,91,
91,93,94,94,95,96,97,97,98,99,99,100,101,103,106,107,108,110,110,111,112,
113,113,115,116,117,118,119,120,121,121,122,122,123,124,124,125,125,126,126,
0


*/
const unsigned char HUFF_TREE [HUFF_SIZE] = {
116,102,104,108,120,101,104,113,111,81,99,111,105,114,
118,103,64,114,113,115,108,99,103,64,109,81,110,65,90,
100,65,66,66,122,67,67,68,68,69,69,70,70,71,71,72,72,
73,73,74,74,75,75,76,76,77,77,78,98,78,79,79,112,80,80,
82,82,83,83,84,84,85,85,86,86,87,87,88,88,89,89,90,91,
91,92,92,93,93,94,94,95,95,96,96,97,97,98,100,101,102,
105,106,106,107,107,109,110,112,115,116,117,117,118,119,
119,120,121,121,122,123,123,124,124,125,125,126,126,0
};

struct huff_branch *  make_huff_tree(){
    struct huff_branch * total = calloc(HUFF_SIZE, sizeof(struct huff_branch));
    char * seen = calloc(HUFF_SIZE, 1);
    for (int i = 0; i < HUFF_ROOT; i++){
        total[i].parent = HUFF_TREE[i];
        struct huff_branch parent = total[HUFF_TREE[i]];
        if (parent.left){
            total[HUFF_TREE[i]].right = i;
        }
        else {
            total[HUFF_TREE[i]].left = i;
        }
    }
    free(seen);
    return total;
}

void huff_decode (unsigned char * decode_me, unsigned char * out, unsigned int * start_block, unsigned char * start_offset, unsigned int * current_location, struct huff_branch * huff_tree){
    unsigned char current;
    unsigned char current_block_offset = *start_offset;
    unsigned int  current_block_index = *start_block;
    unsigned char current_block = decode_me [current_block_index];
    unsigned int write_index = *current_location;
    do{
        current = HUFF_ROOT;
        while (current >= ALFA_SIZE){
            unsigned char choice = (current_block >> (7 - current_block_offset)) & 0x01;
            if (choice){
                current = huff_tree[current].right;
            }
            else {
                current = huff_tree[current].left;
            }
            current_block_offset++;
            if (current_block_offset > 7){
                current_block_offset = 0;
                current_block_index++;
                current_block = decode_me [current_block_index];
            }
        }
        out[write_index] = current;
        write_index++;
    }while (current != EOF_GLYPH);
    *start_block = current_block_index;
    *start_offset = current_block_offset;
    *current_location = write_index;
}

void huff_encode (unsigned char * encode_me, unsigned char * out, unsigned int * start_offset, unsigned char *bit_offset, struct huff_branch * huff_tree){
    unsigned char current;
    unsigned int write_index = *start_offset;
    unsigned char write_block = out[write_index];
    unsigned char write_offset = *bit_offset;
    unsigned char read_index = 0;
    do{
        current = encode_me[read_index];
        unsigned char encode = current;
        unsigned int holding_block = 0;
        char block_len = 0;
        while (encode < HUFF_ROOT){
            unsigned char prev = encode;
            encode = huff_tree[encode].parent;
            unsigned int choice = 0; // by default think its left
            if (huff_tree[encode].right == prev){
                // its right
                choice = 1;
            }
            choice <<= (block_len);
            //printf(" %d (%d vs %d)",choice, huff_tree[encode].left, huff_tree[encode].right);
            holding_block |= choice;
            block_len++;
        }
        for (int i = 0; i < block_len; i++){
            unsigned int singleton = holding_block;
            singleton >>= block_len -i - 1;
            singleton &= 0x01;
            unsigned char block = (unsigned char) singleton;
            block <<= (7 - write_offset);
            
            write_block |=  block;
            
            write_offset++;
            if (write_offset > 7){
                write_offset = 0;
                out[write_index] = write_block;
                write_index++;
                write_block = 0;
            }
        }

        read_index++;
    }while (current < EOF_GLYPH);
    out[write_index] = write_block;
    * start_offset = write_index;
    * bit_offset = write_offset;
}