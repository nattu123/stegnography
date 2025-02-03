#ifndef DECODE_H
#define DECODE_H 
#include "types.h" 
#include "common.h" 

typedef struct
{
    // stego image info 
    char *stego_image_name;

    // output image name 
    char *output_image_name;

}DecodeInfo;

Status read_and_validate_decode_args(int argc,char **argv,DecodeInfo *decode);

#endif 