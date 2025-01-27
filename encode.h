#ifndef ENCODE_H 
#define ENCODE_H
#include "types.h" // user defined variables are in this header file 

typedef struct
{
    char *src_image_fname;
    FILE *fptr_src_img;
    uint image_capacity;
    uint bits_per_pixel;
}EncodeInfo;    

OperationType check_operation_type(char **argv); // to check whether to encode or decode
Status read_and_validate_encode_args(int argc,char **argv,EncodeInfo *encodeinfo); 
#endif