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

Status open_encode_file(EncodeInfo *encinfo)
{
    static int opencount =0;
    if(opencount == 0)
    {
        opencount++;
        // source image file 
        encinfo->fptr_src_img =fopen(encinfo->src_image_fname,"r");
        // error handling 
        if(encinfo->fptr_src_img==NULL)
        {
            perror("fopen");
            fprintf(stderr,"error unablle to open file %s\n",encinfo->src_image_fname);
            return e_failure;
        }
        else
        {
            printf("\n Opened the file %s\n",encinfo->src_image_fname);
        }
        // SECRET FILE 
        encinfo->fptr_secret = fopen(encinfo->secret_fname,"r");
        if(encinfo->fptr_secret==NULL)
        {
            perror("fopen");
            fprintf(stderr,"error unablle to open file %s\n",encinfo->secret_fname);
            return e_failure;
        }
        else
        {
            printf("opened %s\n",encinfo->secret_fname);
        }
    }
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
        
        char *p = strstr(argv[3],".");
        if(p) strcpy(encodeinfo->ext_secret_file,p);
        if(strcmp(encodeinfo->ext_secret_file,".txt")==0)
        {   
            encodeinfo->secret_fname = argv[3];
        }
        else
        {
            printf("The secret file shoul be in .txt format ");
            return e_failure;
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
    return e_success;

} 

Status do_encoding(EncodeInfo *encodeinfo)
{
    printf("Opening input file ");
    if(open_encode_file(encodeinfo)==e_success)
    {

    }
    
}