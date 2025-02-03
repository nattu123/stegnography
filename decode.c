#include "common.h"
#include "decode.h"
#include "types.h"
#include <stdio.h>
#include <string.h>

Status open_stego_file(DecodeInfo *decode)
{
    decode->fptr_stego = fopen(decode->stego_image_name,"rb");
    if(decode->fptr_stego== NULL)
    {
        perror("fopen ");
        return e_failure;
    }
    return e_success;
}

Status read_and_validate_decode_args(int argc,char **argv,DecodeInfo *decode)
{
    if(argc >=3)
    {
        char *ext;

        if(ext = strstr(argv[2],"."))
        {
            if(strcmp(ext,".bmp")==0)
            {
                decode->stego_image_name = argv[2];
            }
            else
            {
                printf("source image not .bmp file \n");

                return e_failure ;
            }
        }
    }
    if(argc == 4)
    {
        char *ext;
        if(ext = strstr(argv[3],"."))
        {
            decode->output_file_name = argv[3];
        }
        else
        {
            printf("enter a valid extension \n");
            return e_failure;
        }
    }
    return e_success;
}

Status do_decoding(DecodeInfo *decode)
{
    printf("## Deocding started \n");
    printf("Opening stego file \n");
    if(open_stego_file(decode)==e_success)
    {
        printf("opened stego file ");
        
    }
}