#include "LTE_bitmap_alphabet.h"
unsigned char * condense (unsigned char * expanded, unsigned short size, unsigned short * new_size){
    unsigned char * condensed = malloc(size);
    unsigned short rw_index = 0;
    unsigned short working_index = 0;
    unsigned char pause = FALSE; // don't convert chars when we hit a [ till we hit a ]
    unsigned char delay = 0; // don't convert chars when we hit a goto
    for (int i = 0; i < size; i ++){
        unsigned char c = expanded [i];
        if (delay > 0 || pause){
            if (delay){
                delay--;
            }
            if (pause && c == ']'){
                pause = FALSE;
            }
            else {
                //copy first 2 bits in
                for (char j=0; j < 2;j++){
                    unsigned char wc = (c>>(7-j)) & 0x01;
                    condensed[rw_index] |= wc << (7-working_index);
                    working_index++;
                    if (working_index == 8){
                        working_index = 0;
                        rw_index++;
                    }
                }
            } 
        }
        else{
            if (c == '['){
                pause = TRUE;
            }
            else if (c == '@'){
                delay = GOTO_DELAY;
            }
        }
        //copy back 6 bits in
        c<<=2;
        for (char j =0; j <CHAR_BITS; j++){
            unsigned char wc = (c>>(7-j)) & 0x01;
            condensed[rw_index] |= wc << (7-working_index);
            working_index++;
            if (working_index == 8){
                working_index = 0;
                rw_index++;
            }
        }
    }
    *new_size = rw_index;
    return realloc(condensed, rw_index);
};

void print_condensed_alpha(){
    unsigned char working = 0x0;
	
	int current = 7;
	int track = 0;
	int resets = 0;
    for (int i = 0; i < 58 * 15; i++ ){
		//printf("%d,", alphabet[i]);
		working |= alphabet[i] << current;
		current --;
		glyph[track] = alphabet[i];
		if (current == -1){
			current = 7;
			printf("0x%x,", working);
			working = 0x0;
			resets ++;
		}
		track++;
		if (track == 15){
			//printf("\n");
			//print_glyph(glyph);
			track = 0;
		}
	}
	printf("0x%x,", working);
	printf("\n%d", resets);
}