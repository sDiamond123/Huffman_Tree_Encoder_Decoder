These are basic utility files used to generate a Huffman tree and compress/decompress plaintext with Huffman codes. 

Also includes some compressed 3x5 bitmap charecters to use. [Uncompressed Bitmaps](https://github.com/sDiamond123/Huffman_Tree_Encoder_Decoder/blob/main/Light_Text_Engine/LTE_bitmap_alphabet.h) [Compressed Bitmaps](https://github.com/sDiamond123/Huffman_Tree_Encoder_Decoder/blob/main/Light_Text_Engine/LTE_glyphs.c)

In the included example, [this file](https://github.com/sDiamond123/Huffman_Tree_Encoder_Decoder/blob/main/Light_Text_Engine/test_txt.txt) was used to generate the Huffman tree ([found here](https://github.com/sDiamond123/Huffman_Tree_Encoder_Decoder/blob/main/Light_Text_Engine/LTE_huff_decoder.c)). This [text file](https://github.com/sDiamond123/Huffman_Tree_Encoder_Decoder/blob/main/Light_Text_Engine/test_2.txt) (~1600 charecters) was then compressed [here](https://github.com/sDiamond123/Huffman_Tree_Encoder_Decoder/blob/main/Light_Text_Engine/LTE_text.bin) (~1000 bytes) for a 3:2 compression ratio which is not great but better then nothing. 

This was written for storing and displaying text on harware with modest capability (The Gameboy Advance in specific).

An [example GBA Homebrew impmentation can be found here](https://github.com/sDiamond123/LTE_GBA_2/):

![Recording 2025-11-14 at 00 20 59](https://github.com/user-attachments/assets/23dddc51-a20d-486a-be80-d80f6e99b7e7)
