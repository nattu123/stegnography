#include <stdio.h>
#include "types.h"
#include "encode.h"
#include "decode.h"

int main(int argc,char **argv)
{
    if (argc <=5)
    {
        if(check_operation_type(argv) == e_encode)
        {
            EncodeInfo encodeinfo;
            if(read_and_validate_encode_args(argc,argv,&encodeinfo)==e_success)
            {
                if(do_encoding(&encodeinfo)==e_failure)
                {
                    fprintf(stderr,"Error in Encoding\n");
                    return 1;
                }
                fclose(encodeinfo.fptr_src_img);
                fclose(encodeinfo.fptr_secret);
                fclose(encodeinfo.fptr_stego);
                printf("Encoding completed \n");
            }
            else 
            {
                fprintf(stderr,"failed in validation of encode args\n");
                return 1;
            }
        }
        else if(check_operation_type(argv) == e_decode)
        {
            DecodeInfo decode;
            if(read_and_validate_decode_args(argc,argv,&decode)== e_success)
            {
                printf("Validation of decode args succesfull \n");
                if(do_decoding(&decode)==e_success)
                {
                    printf("decoding finished output is stroed in %s\n",decode.output_file_name);
                    
                }
            }   
        }
        else 
        {
            printf("\n --------Invalid option--------- \n ");
            return 1;
        }
    }
}