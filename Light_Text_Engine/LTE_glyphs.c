#include "LTE_glyphs.h"
#include <stdio.h>

/*
The bitmap itself
*/
const unsigned char GLYPHS [109] = {
0x57,0xdb,0xae,0xb9,0xc9,0x1e,0xb6,0xef,0x3c,0xfe,0x79,0x1c,0xb5,0x5b,0xed,0xe9,0x2e,0x49,
0x3a,0xdd,0x6c,0x92,0x7b,0xfd,0xbb,0xdb,0x7d,0xb7,0xeb,0xa4,0x57,0xd7,0xae,0xb5,0xce,0x77,
0x49,0x2b,0x6d,0xf6,0xda,0xad,0xfe,0xda,0xad,0xb5,0x25,0xca,0x9c,0x0,0x24,0x90,0x4e,0x50,
0x40,0xc,0x82,0x19,0x20,0x0,0xa0,0x0,0x0,0x2,0x44,0x49,0x2a,0x42,0x92,0x31,0x25,0xa,0x88,
0xc4,0x54,0x8,0x20,0xb2,0x5f,0x15,0x3e,0x38,0xeb,0x79,0x3e,0x63,0x94,0xd5,0x72,0xd2,0x55,
0x54,0xab,0x29,0x5b,0x50,0xaa,0x80,0xba,0x0,0x70,0x7,0x1c,0x5,0x40,0xff,0xff,0x55, 0x54
};


/*
Decodes a compressed glyph from storage
 */
void get_glyph (unsigned char id, unsigned char * out){
    if (id >= GLYPH_COUNT){
        id = 56; // Just black out unreadable letters
    }
    unsigned short true_index = id * GLYPH_SIZE;
    // get which sub block we are in and then get it form alphabet
    unsigned short block_index = true_index >> 3;
    unsigned char current = GLYPHS[block_index];
   
    // get starting offset
    unsigned short bit_offset = true_index & 0x07;
    // get rid of offset
    current <<= bit_offset;
    // get the letter bitmap
    for (int i = 0; i < GLYPH_SIZE; i++){
        out[i] = (current & 0x80)>>7;
        current <<= 1;
        bit_offset ++;
        if (bit_offset == 8){
            bit_offset = 0;
            block_index++;
            current = GLYPHS[block_index];
        }
    }
}

/*
Convert a single letter to a glyph
*/
unsigned char make_glyph (char plain_text){

    switch(plain_text){
        //a-z
        case 'a' ... 'z':
            return plain_text - 'a';
        case 'A' ... 'Z':
            return plain_text - 'A';
        //0-9
        case '1' ... '9':
            return plain_text - 8;
        case '0':
            return 50;
        // punctuation
        case '.':
            return 26;
        case '!':
            return 27;
        case '?':
            return 28;
        case ',':
            return 29;
        case ';':
            return 30;
        case '\'':
            return 31;
        case '"':
            return 32;
        case ' ':
            return 33;
        case '\\':
            return 34;
        case '/':
            return 35;
        case '(':
            return 36;
        case ')':
            return 37;
        case '<':
            return 38;
        case '>':
            return 39;
        case ':':
            return 40;
        //math
        case '*':
            return 51;
        case '+':
            return 52;
        case '-':
            return 53;
        case '=':
            return 54;
        case '^':
            return 55;
        //misc
        case '&':
            return 56;
        case '#':
            return 57;
        //command codes
        case '$':
            return 58;
        case '[':
            return 59;
        case ']':
            return 60;
        case '\n':
            return 61;
        case '@':
            return 62;
        case '\0':
            return 63;
        // invalid
        default:
            return 57;   
    }
}

/*
Get length of null terminating str
*/
unsigned short lte_str_len (char * text){
    unsigned short n = 0;
    char current = text[n];
    while (current){
        n++;
        current = text[n];
    }
    return n;
}

/*
Convert ASCII to LTE glyph encoding
*/
unsigned char *glyphify (char * text_in, unsigned short * size){
    unsigned short str_len = lte_str_len(text_in);
    unsigned char * glyph_out = malloc(str_len + 1);
    unsigned char pause = FALSE; // don't convert chars when we hit a [ till we hit a ]
    unsigned char delay = 0; // don't convert chars when we hit a goto
    for (unsigned short i = 0; i <= str_len; i++){
        char c = text_in[i];
        if (delay > 0 || pause){
            if (delay){
                delay--;
            }
            if (pause && c == ']'){
                pause = FALSE;
                glyph_out[i] = make_glyph(c);
            }
            else {
                glyph_out[i] = c;
            } 
        }
        else{
            if (c == '['){
                pause = TRUE;
            }
            else if (c == '@'){
                delay = GOTO_DELAY;
            }
            glyph_out[i] = make_glyph(c);
        }
    }
    *size = str_len;
    return glyph_out;
}
