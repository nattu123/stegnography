#define _GNU_SOURCE
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

Status open_output_files(DecodeInfo *decode)
{
    if(decode->output_file_name == NULL)
    {
        printf("INFO: Output file name not given, setting the file name as 'stegout' \n");
        decode->output_file_name = "stegout";
        // strcat(decode->output_file_name,decode->secret_file_ext);
    }
    asprintf(&decode->output_file_name, "%s%s",decode->output_file_name,decode->secret_file_ext);
    printf("\n\n%s\n\n\n",decode->output_file_name);
    decode->fptr_output = fopen(decode->output_file_name,"wb");
    if(decode->fptr_output == NULL)
    {
        perror("fopen : ");
        fprintf(stderr,"cannot open file %s \n",decode->output_file_name);
        return e_failure;
    }
    return e_success ;
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
    else
    {
        printf("./lsb_steg: Decoding: ./lsb_steg -d <.bmpfile> [output file]");
        return e_failure;
    }
    
    if(argc == 4)
    {
        if(strstr(argv[3],"."))
        {
            printf("no  '.'  is allowed extension will be obtained from secret file");
            return e_failure;
        }
        else
        {
            decode->output_file_name = argv[3];
        }
    }
    else
    {
        decode->output_file_name = NULL;
    }
    return e_success;
}

Status do_decoding(DecodeInfo *decode)
{
    printf("## Decoding started \n");
    printf("INFO: Opening stego file \n");
    if(open_stego_file(decode)==e_success)
    {
        printf("INFO: Opened stego file ");
        fseek(decode->fptr_stego,54,SEEK_SET);
        printf("INFO: Decoding magic string\n");
        if(decode_magic_string(decode)==e_success)
        {
            printf("INFO: Magic string decoded \n");
            printf("INFO: Starting decode of file extension :\n" );
            if(decode_secret_ext_size(decode)==e_success)
            {
                printf("INFO: Extension decoded \n");
                printf("INFO: Starting decoding of secret file \n");
                if(decode_secret_ext(decode)==e_success)
                {
                    printf("INFO: Decoded secret file exxtension \n");
                    printf("INFO: Decoding secret file size \n");
                    if(decode_secret_file_size(decode)==e_success)
                    {
                        printf("INFO: Decoded ssecrte file size \n");
                        printf("INFO: Required data for decoding  obtained \n");
                        printf("INFO: Opening output file \n");
                        if(open_output_files(decode)==e_success)
                        {
                            printf("INFO: Opened op file  %s\n",decode->output_file_name);
                            printf("INFO: Decoding secret file\n");
                            if(decode_secret_file(decode)==e_success)
                            {
                                printf("INFO: Decoded secret file\n");
                                return e_success;
                            }
                        }
                    }
            
                }
                
            }
        
        }
        
        
    }
    return e_failure;
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
    unsigned int mask = 0x80000000;
    unsigned char ch[1];
    decode->secret_file_ext_size = 0;
    for(int i =0;i<sizeof(int)*MAX_IMAGE_BUFF_SIZE;i++)
    {
        fread(ch,1,1,decode->fptr_stego);
        if(ch[0]& 0x01)
        {
            decode->secret_file_ext_size = decode->secret_file_ext_size | mask;
        }
        mask >>=1 ;
    }
    return e_success;
}

Status decode_secret_ext(DecodeInfo *decode)
{
    for(int i=0;i<decode->secret_file_ext_size;i++)
    {
        fread(decode->image_data,sizeof(char),MAX_IMAGE_BUFF_SIZE,decode->fptr_stego);
        decode->secret_file_ext[i]=decode_from_lsb(decode->image_data);
    }
    return e_success;
}

Status decode_secret_file_size(DecodeInfo *decode)
{
    unsigned int mask = 0x80000000;
    unsigned char ch[1];
    decode->secret_file_size = 0;
    for(int i=0;i<MAX_IMAGE_BUFF_SIZE*sizeof(int);i++)
    {
        fread(ch,1,1,decode->fptr_stego);
        if(ch[0]& 0x01)
        {
            decode->secret_file_size = decode->secret_file_size |mask;
        }
        mask >>=1;
    }
    return e_success;
}

Status decode_secret_file(DecodeInfo *decode)
{
    printf("inside decode secret file \n\n\n");
    char ch;
    printf("\nsecret file size = %d\n",decode->secret_file_size);
    for(int i =0;i<decode->secret_file_size;i++)
    {
        fread(decode->image_data,sizeof(char),MAX_IMAGE_BUFF_SIZE,decode->fptr_stego);
        if(ferror(decode->fptr_stego))
        {
            printf("error reading the src image \n");
        }
        ch = decode_from_lsb(decode->image_data);
        fputc(ch,decode->fptr_output);
    }
    return e_success;
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
        mask >>=1;
    }
    return ch;
}