#ifndef DECODE_H
#define DECODE_H 
#include "types.h" 
#include "common.h" 
#include<stdio.h>

typedef struct
{
    // stego image info 
    char *stego_image_name;
    FILE *fptr_stego;
    char image_data[MAX_IMAGE_BUFF_SIZE];

    // output image  
    char *output_file_name;
    FILE *fptr_output;
    char magic_string[3];

}DecodeInfo;

Status read_and_validate_decode_args(int argc,char **argv,DecodeInfo *decode);
Status do_decoding(DecodeInfo *decode);
Status open_stego_file(DecodeInfo *decode);
Status decode_magic_string(DecodeInfo *decode);
unsigned char decode_from_lsb(char *image);
Status decode_secret_ext_size(DecodeInfo *decode);


#endif 