#ifndef ENCODE_H 
#define ENCODE_H
#include "types.h" // user defined variables are in this header file 
#include "common.h" // common for encode and decode

typedef struct
{
    // INPUT FILE INFO 
    char *src_image_fname;
    FILE *fptr_src_img;
    uint image_capacity;
    uint bits_per_pixel;

    //SECRET FILE INFO 
    char *secret_fname;
    char ext_secret_file[max_file_suffix];
}EncodeInfo;    

OperationType check_operation_type(char **argv); // to check whether to encode or decode
Status read_and_validate_encode_args(int argc,char **argv,EncodeInfo *encodeinfo); 
#endif