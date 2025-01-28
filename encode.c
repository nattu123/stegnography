#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"

// Operation TYpe checking 
OperationType  check_operation_type(char **argv)
{
    if(strcmp(argv[1],"-e")==0)         return e_encode;
    else if(strcmp(argv[1],"-d")==0)    return e_decode;
    else                                return e_unsupported;
}

Status read_and_validate_encode_args(int argc,char **argv,EncodeInfo *encodeinfo)
{
    
        if(strstr(argv[2],".") && strcmp(strstr(argv[2],"."),".bmp")==0)
        {
            encodeinfo->src_image_fname=argv[2];
        }
        else 
        {
            printf("\nsource image should be in .bmp format\n");
            return e_failure;
        }

        strcpy(encodeinfo->ext_secret_file,strstr(argv[3],"."));
        if(strcmp(encodeinfo->ext_secret_file,".txt")==0)
        {   
            encodeinfo->secret_fname = argv[3];
        }
        else
        {
            printf("The secret file shoul be in .txt format ");
        }
    
        if(strstr(argv[4],".") && strcmp(strstr(argv[4],"."),".bmp")==0)
        {
            encodeinfo->stego_fname =argv[4];
        }
        else 
        {
            printf("\n Output image should be in .bmp format\n");
            return e_failure;
        }

} 