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

    // output image name 
    char *output_file_name;
    FILE *fptr_output;

}DecodeInfo;

Status read_and_validate_decode_args(int argc,char **argv,DecodeInfo *decode);
Status do_decoding(DecodeInfo *decode);
Status open_stego_file(DecodeInfo *decode);

#endif 