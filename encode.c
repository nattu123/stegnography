#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"

// Operation TYpe checking 
OperationType check_operation_type(char **argv)
{
    if(strcmp(argv[1],"-e")==0)         return e_encode;
    else if(strcmp(argv[1],"-d")==0)    return e_decode;
    else                                return e_unsupported;
}

Status read_and_validate_encode_args(int argc,char **argv,EncodeInfo *encodeinfo)
{
    if(argc>2)
    {
        if(strstr(argv[2],".")&&strcmp(strstr(argv[2],"."),".bmp")==0)
        {
            encodeinfo->src_image_fname=argv[2];
        }
        else 
        {
            printf("\nsource image should be in .bmp format\n");
            return e_success;
        }
    }
} 