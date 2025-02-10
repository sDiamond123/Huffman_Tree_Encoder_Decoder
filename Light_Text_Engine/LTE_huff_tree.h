#include <stdlib.h>
#include <stdio.h>
#include "LTE_glyphs.h"
#include "LTE_bool.h"
#include "LTE_huff_decoder.h"

#define BAD_PTR  -1

unsigned char * generateStorageTree(unsigned int * weights);
unsigned int * get_weights_from_file(char * file_name);
unsigned char * huff_encode_file (char * file_name, struct huff_branch * huff_tree, unsigned int * size);
void huff_encode_and_write (char * file_name, char * file_out, char * bin_out, struct huff_branch * huff_tree, unsigned int * size);