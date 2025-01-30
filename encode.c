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

long get_secret_file_size(FILE *fptr)
{
  long size;
  fseek(fptr,0,SEEK_END);
  size = ftell(fptr);
  rewind(fptr);
  return size;

}

Status open_encode_file(EncodeInfo *encinfo)
{
    static int opencount =0;
    if(opencount==0)
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
    else 
    {
        // for stego image file 
        encinfo->fptr_stego = fopen(encinfo->stego_fname,"w");
        // Error handling 
        if(encinfo->fptr_stego==NULL)
        {
            perror("fopen : ");
            fprintf(stderr,"cannot open file %s\n",encinfo->stego_fname);
            return e_failure;
        }
        else
        {
            printf("opened output file \n");
        }
    }
    return e_success;
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
    printf("Opening input file \n");
    if(open_encode_file(encodeinfo)==e_success)
    {
        printf("## Encoding started \n");
        printf(" Getting the file size of secret file : \n ");
        encodeinfo->size_secret_file = get_secret_file_size(encodeinfo->fptr_secret);
        if(encodeinfo->size_secret_file)
        {
            printf("INFO : File not empty \n");
            printf("INFO : Checking for capacity of %s, to handle %s\n",encodeinfo->src_image_fname,encodeinfo->secret_fname);
            encodeinfo->image_capacity =  get_image_size_for_bmp(encodeinfo->fptr_src_img);
            if(check_capacity(encodeinfo)==e_success)
            {
                printf("Capacity of %s is enough to store %s",encodeinfo->src_image_fname,encodeinfo->secret_fname);
                printf(" opening output file : \n");
                if(open_encode_file(encodeinfo)==e_failure)
                {
                    fprintf(stderr,"Error in opening output file \n");
                    return e_failure;
                }

                /// copying image header 
                printf("INFO : copying imahge header \n");
                if(copy_bmp_header(encodeinfo->fptr_src_img,encodeinfo->fptr_stego))
                {
                    printf("INFO : COPIED BMP HEADDER \n");
                    printf("Encoding secret File extension");
                    if(encode_secret_file_extn(encodeinfo)==e_success)
                    {
                        printf("Encoded secret file extension ");
                    }

                }

                
            }
        }
    }
    return e_success;
    
}

Status check_capacity(EncodeInfo *encInfo)
{
    if(encInfo->image_capacity>(14+encInfo->size_secret_file)*8)
    {
        return e_success;
    }
    return e_failure;
}

uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);
    rewind(fptr_image);

    // Return image capacity
    return width * height * 3;
}

Status copy_bmp_header(FILE *fptr_src_image,FILE *fptr_stego)
{
    char buffer[54];
    fread(buffer,1,54,fptr_src_image);
    fwrite(buffer,1,54,fptr_stego);
}

Status encode_secret_file_extn(EncodeInfo *encodeinfo)
{

}