#include "LTE_huff_tree.h"

unsigned char * generateStorageTree(unsigned int * weights){
    unsigned char * tree = malloc(HUFF_SIZE);
    unsigned int * build_weights = calloc(HUFF_SIZE, sizeof(int));
    // first 32 bytes are the 32 chars 
    //preload first 32 char weights
    for (unsigned short i = 0; i < ALFA_SIZE; i++){
        build_weights[i] = weights [i];
        if (weights[i] ==0){
            build_weights[i] = 1;
        }
    }
    // build tree
    unsigned short build_size = ALFA_SIZE;
    while (TRUE){
        short min = -1;
        short second_min = -1;
        for (unsigned short i = 0; i < build_size; i++){
            if (build_weights[i] > 0){
                if (min == -1 ||build_weights[min] > build_weights [i]){
                second_min = min;
                min = i;
                }
                else if (second_min == -1 || build_weights[second_min] > build_weights [i]){
                    second_min = i;
                }
            }
        }
        if (min == -1 || second_min == -1){
            break;
        }
        // add joint vertex
        //printf("%d(%d) + %d(%d) into %d (%d)\n", min, build_weights[min], second_min, build_weights[second_min], build_size, build_weights[min]+build_weights[second_min]);
        build_weights[build_size] = build_weights[min] + build_weights[second_min];
        tree[min] = build_size; // add parent to tree
        tree[second_min] = build_size;
        build_weights[min] = 0;
        build_weights[second_min] = 0;
        build_size ++; // added one more weight
    }
    free(build_weights);
    return tree;
};

unsigned int * get_weights_from_file(char * file_name){
    FILE* in = fopen(file_name, "r");
    unsigned int * w = calloc(ALFA_SIZE, sizeof(int));
    char ch;
    while(TRUE) {
      ch = fgetc (in);
      if (ch == EOF)
         break;
      w[make_glyph(ch)]++;
   }
   fclose(in);
   return w;
}

/*
unsigned char * huff_encode_file(char * file_name, struct huff_branch * huff_tree){
    FILE* in = fopen(file_name, "r");
    unsigned char * out = malloc(1600);
    char * ch = calloc(2, 1);\
    unsigned char * ch_u = calloc(2, 1);
    unsigned int start_ind = 0;
    unsigned char start_off = 0;
    while(TRUE) {
      ch[0] = fgetc (in);
      if (ch[0] == EOF)
         break;
      ch_u[0]= make_glyph(ch[0]);
      huff_encode(ch_u, out, &start_ind, & start_off, huff_tree);
   }
   free(ch);
   fclose(in);
   return out;
}*/



unsigned char * huff_encode_file (char * file_name, struct huff_branch * huff_tree, unsigned int * size){
   
   FILE *fp;
   unsigned char * out = calloc(*size, 1);
   char *string =  malloc (*size);
   fp = fopen (file_name, "r");
   unsigned char start_off = 0;
   unsigned int start_offset = 0;
   int lines = 0;
   while (!feof(fp)) {
      fgets(string, 1600, fp);
      lines++;
      printf ("\n%s", string) ;
      unsigned short s;
      unsigned char * glyphed = glyphify(string, &s);
      printf("\n");
      for (int i = 0; i < s + 1; i++){
        printf("%d,", glyphed[i]);
      }
      printf("\n");
      huff_encode(glyphed, out, &start_offset, & start_off, huff_tree);
     
      free(glyphed);
   }
    printf("\nENCODED:");
      for (unsigned int i = 0; i <=start_offset; i++){
        printf("%x,", out[i]);
      }
   free(string);
   fclose (fp);
   printf("\nCompressed to %d bytes\n", start_offset);
   *size = lines;
   return out;
}

void huff_encode_and_write (char * file_name, char * file_out, char * bin_out, struct huff_branch * huff_tree, unsigned int * size){
   FILE *fp;
   FILE * f_out;
   FILE * b_out;
   unsigned char * out = calloc(*size, 1);
   char *string =  malloc (*size);
   unsigned char * track_off = malloc(*size);
   unsigned int * track_ind  = malloc(*size);
   fp = fopen (file_name, "r");
   f_out = fopen(file_out, "w");
   b_out = fopen(bin_out, "wb");
   unsigned char start_off = 0;
   unsigned int start_offset = 0;
   char new_page = TRUE;
   int lines = 0;
   int page_count = 0;
   while (!feof(fp)) {
      fgets(string, 1600, fp);
      if ( new_page){
        new_page = FALSE;
        track_off[page_count] = start_off;
        track_ind[page_count] = start_offset;
        page_count++;
      }
      if (string[0] == '\n' && string[1] == '\0'){
        new_page = TRUE;
      }
    lines++;
    unsigned short s;
    unsigned char * glyphed = glyphify(string, &s);
    huff_encode(glyphed, out, &start_offset, & start_off, huff_tree);     
    free(glyphed);
      
   }
    track_ind[page_count] = start_offset;
    fprintf (f_out, "const unsigned int PAGE_COUNT = %d;\n\n", page_count);
   fprintf(f_out,"const unsigned int TABLE_OF_CONTENTS [%d] = {", (page_count+1));
    for (int i = 0; i <page_count+1; i++){
        fprintf(f_out,"%d", track_ind[i]);
        if (i < page_count){
            fprintf(f_out,", ");
            if (i%20 == 19){
                fprintf(f_out,"\n\t\t");
            }
        }
        else{
            fprintf(f_out,"};\n\n");
        }
    }

    fprintf(f_out,"const unsigned TABLE_OF_CONTENTS_OFFSET [%d] = {", page_count);
    for (int i = 0; i <page_count; i++){
        fprintf(f_out,"%d", track_off[i]);
        if (i < page_count - 1){
            fprintf(f_out,", ");
            if (i%20 == 19){
                fprintf(f_out,"\n\t\t");
            }
        }
        else{
            fprintf(f_out,"};\n\n");
        }
    }

   for (unsigned int i = 0; i <=start_offset; i++){
        fprintf(b_out,"%c", out[i]);
    }
   free(string);
   free(out);
   free(track_ind);
   free(track_off);
   fclose (fp);
   fclose(b_out);
   fclose(f_out);
   printf("\nCompressed to %d lines (%d pages) to %d bytes\n", lines, page_count, start_offset);
}