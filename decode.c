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
        fseek(decode->fptr_stego,54,SEEK_SET);
        printf("decoding magic string\n");
        if(decode_magic_string(decode)==e_success)
        {
            printf("magic string decoded \n");
            printf("starting decode of file extension :\n" );
            
        
        }
        
        
    }
}

Status decode_magic_string(DecodeInfo *decode)
{
    int i=0;
    for(i=0;i<2;i++)
    {
        fread(decode->image_data,sizeof(char),MAX_IMAGE_BUFF_SIZE,decode->fptr_stego);
        decode->magic_string[i] = decode_from_lsb(decode->image_data);
    }
    decode->magic_string[i]= '\0';

    if(strcmp(decode->magic_string,MAGIC_STRING)==0) return e_success;
    else return e_failure;
}

Status decode_secret_ext_size(DecodeInfo *decode)
{
    
}

unsigned char decode_from_lsb(char *image)
{
    unsigned int mask =  0x80;
    unsigned char ch;
    for(int i=0;i<MAX_IMAGE_BUFF_SIZE;i++)
    {
        if( image[i] & 0x01)    
        {
            ch = ch | mask;
        }
        else
        {
            ch = ch & (~mask);
        }
        mask >>=1 ;
    }
    return ch;
}