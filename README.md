These are basic utility files used to generate a Huffman tree and compress/decompress plaintext with Huffman codes. 

Also includes some compressed bitmap charecters to use.

In the included example, [this file](https://github.com/sDiamond123/Huffman_Tree_Encoder_Decoder/blob/main/Light_Text_Engine/test_txt.txt) was used to generate the Huffman tree ([found here](https://github.com/sDiamond123/Huffman_Tree_Encoder_Decoder/blob/main/Light_Text_Engine/LTE_huff_decoder.c)). This [text file](https://github.com/sDiamond123/Huffman_Tree_Encoder_Decoder/blob/main/Light_Text_Engine/test_2.txt) (~1500 charecters) was then compressed [here](https://github.com/sDiamond123/Huffman_Tree_Encoder_Decoder/blob/main/Light_Text_Engine/LTE_text.bin) (~1000 bytes) for a 3:2 compression ratio which is not great but better then nothing. 

An [example impmentation](https://github.com/sDiamond123/LTE_GBA_2/):

![Recording 2025-11-13 at 22 59 20](https://github.com/user-attachments/assets/d26bacea-8d4d-4c7c-a968-aceb72aafcb4)
