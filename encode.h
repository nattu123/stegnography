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
    FILE *fptr_secret;
    long size_secret_file;

    //OUTPUT FILE INFO 
    char *stego_fname;
    FILE *fptr_stego;


}EncodeInfo;    

OperationType check_operation_type(char **argv); // to check whether to encode or decode
Status read_and_validate_encode_args(int argc,char **argv,EncodeInfo *encodeinfo); 
Status do_encoding(EncodeInfo *encodeinfo);
long get_secret_file_size(FILE *fptr);
Status check_capacity(EncodeInfo *encInfo); // check capacity
uint get_image_size_for_bmp(FILE *fptr_image); // image size of the bmp
Status copy_bmp_header(FILE *fptr_src_image,FILE *fptr_stego);

#endif