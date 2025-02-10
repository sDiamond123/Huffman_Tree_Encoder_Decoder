#include "LTE_glyphs.h"

#ifndef HUFF_SIZE
#define HUFF_SIZE   127 // size of a huffman tree
#define HUFF_ROOT   HUFF_SIZE - 1

//huffman tree
extern const unsigned char HUFF_TREE[HUFF_SIZE];

struct huff_branch{
    char left;
    char right;
    char parent;
};
#endif

struct huff_branch * make_huff_tree();
void huff_decode (unsigned char * decode_me, unsigned char * out, unsigned int * start_block, unsigned char * start_offset, unsigned int * current_location, struct huff_branch * huff_tree);
void huff_encode (unsigned char * encode_me, unsigned char * out, unsigned int * start_offset, unsigned char *bit_offset, struct huff_branch * huff_tree);