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
        printf("output file name not given . setting the file name as 'stegout' \n");
        decode->output_file_name = "stegoout";
        printf("\n\n %s  %s \n\n\n",decode->output_file_name,decode->secret_file_ext);
        // strcat(decode->output_file_name,decode->secret_file_ext);
    }
    asprintf(&decode->output_file_name, "%s%s",decode->output_file_name,decode->secret_file_ext);
    decode->fptr_output = fopen(decode->output_file_name,"wb");
    if(decode->fptr_output = NULL)
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
    if(argc == 4)
    {
        if(strstr(argv[3],"."))
        {
            printf("no . is allowed extension will be obtained from secret file");
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
            if(decode_secret_ext_size(decode)==e_success)
            {
                printf("extension decoded \n");
                printf("starting decoding of secret file \n");
                if(decode_secret_ext(decode)==e_success)
                {
                    printf("decoded secret file exxtension \n");
                    printf("decodinng secret file size \n");
                    if(decode_secret_file_size(decode)==e_success)
                    {
                        printf("decoded ssecrte file size \n");
                        printf("required data for decoding  obtained \n");
                        printf("opening output file \n");
                        if(open_output_files(decode)==e_success)
                        {
                            printf("opened op file  %s\n",decode->output_file_name);
                            printf("decoding secret file ");
                            if(decode_secret_file(decode)==e_success)
                            {
                                printf("\ndecoded secret file\n");
                            }
                        }
                    }
            
                }
                
            }
        
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
    printf("\nsecret file siize = %d\n",decode->secret_file_size);
    for(int i =0;i<decode->secret_file_size;i++)
    {
        fread(decode->image_data,sizeof(char),MAX_IMAGE_BUFF_SIZE,decode->fptr_stego);
        if(ferror(decode->fptr_stego))
        {
            printf("\n\nesdfsgfsgsd\n\n");
        }
        printf("\n--%d--\n",ftell(decode->fptr_stego));
        ch = decode_from_lsb(decode->image_data);
        printf("%c",ch);
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
        mask >>=1 ;
    }
    return ch;
}