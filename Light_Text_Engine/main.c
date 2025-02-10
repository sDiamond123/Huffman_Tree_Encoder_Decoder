#include "LTE_huff_tree.h"
#include "LTE_huff_decoder.h"
#include "LTE_txt_box.h"
#include <stdio.h>


int main (int argc, char* argv[]){
    
    /*unsigned int * w = get_weights_from_file(argv[1]);
    for (int i = 0; i < 64; i++){
        //printf("\n%d:%d", i, w[i]);
    }
    printf("\n");
    unsigned char * k = generateStorageTree(w);
    for (int i = 0; i < 126; i++){
        printf("%d,", k[i]);
    }*/
    /*
    struct huff_branch * d = make_huff_tree();
    unsigned int size = 3200;
    unsigned char* encoded = huff_encode_file(argv[1],d, &size);
    unsigned int size_2 = 3200;
    huff_encode_and_write (argv[1], argv[2], argv[3], d,&size_2);
    unsigned char * decoded = malloc(3200);
    printf("\n");
    unsigned int current_in = 0;
    unsigned char current_in_off = 0;
    unsigned int current_write = 0;
    int j = 0;
    for (unsigned int i = 0; i < size; i++){
        printf("DECODED:\n");
        
        huff_decode(encoded, decoded, &current_in, &current_in_off, &current_write, d);
        unsigned char c;
        do{
            c = decoded[j];
            printf("%d,", c);
            j++;
        } while (c < EOF_GLYPH);
        printf("\n");
    }
    free(decoded);
    free (encoded);
    */
   
    struct huff_branch * d = make_huff_tree();
    unsigned int size_2 = 3200;
    huff_encode_and_write (argv[1], argv[2], argv[3], d,&size_2);
    unsigned char * decoded = malloc(3200);
    free(decoded);
    FILE * open = fopen(argv[3], "rb");
    unsigned char * text = calloc(3200, 1); 
    for (unsigned int i = 0; i < PAGE_COUNT; i++){
           printf("\n\n");
           unsigned int size = 0;
           get_page (i,  open, text, &size, d);
           for (unsigned int j = 0; j < size; j++){
                printf("%d,", text[j]);
           }
           
    }
    printf("\n");
    fclose(open);
    free(text);
    free(d);
    //free(k);
    //free(w);
    return 0;
}