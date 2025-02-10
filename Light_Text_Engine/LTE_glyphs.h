#include <stdlib.h>
#include "LTE_bool.h"
/*
Compressed bitmap glyphs for Light Text Engine

An encoding scheme with acompanying 3x5 bitmap representation
Encoding scheme (only 0-57 have visual representations, 58-63 are control codes):
0-25 capital A-Z:
    (in alphabetical order)

26 - 40 basic punctuation:
    26 - .
    27 - !
    28 - ?
    29 - ,
    30 - ;
    31 - '
    32 - "
    33 - [SPACE or EMPTY]
    34 - \
    35 - /
    36 - (
    37 - )
    38 - <
    39 - >
    40 - :

41 - 50 numbers:
    41 - 1
    42 - 2
    43-  3
    44 - 4
    45 - 5
    46 - 6
    47 - 7
    48 - 8
    49 - 9
    50 - 0

51 - 55 math:
    51 - [TIMES]
    52 - +
    53 - - 
    54 - =
    55 - ^

56 - 57 misc. bit maps:
    56 - [FILLED]
    57 - [CHECKER_BOARD]

58 - 63 control codes:
    58 - NEW_PAGE
    59 - BEGIN_STATE
    60 - END_STATE
    61 - NEW_LINE
    62 - GOTO
    63 - EOF or NULL_TERMINATOR

Usage of special control c
*/

#ifndef ALFA_SIZE 
#define ALFA_SIZE       64 // we have a 2^6 = 64 char useable alphabit
#define GLYPH_COUNT     58 // number of actual glyphs ()
#define GLYPH_W         3  // glyphs are 3 pixels wide
#define GLYPH_H         5  //glyphs are 5 pixels tall
#define GLYPH_SIZE      15 // each 3x5 glyph is 15 bytes in expanded form
#define CHAR_BITS       6  // each letter takes up only 6 bits 
#define GOTO_DELAY      4  // 4 bytes dialouge ptr
#define EOF_GLYPH       63
#define NEW_LINE_GLYPH  61


//compressed bitmap
extern const char GlYPHS[109];
#endif


void get_glyph (unsigned char id, unsigned char * out);
unsigned char * glyphify (char * text_in, unsigned short * size);
unsigned char make_glyph (char plain_text);
unsigned char * condense (unsigned char * expanded, unsigned short size, unsigned short * new_size);