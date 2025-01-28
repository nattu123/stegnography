#include <stdio.h>
#include "types.h"
#include "encode.h"

int main(int argc,char **argv)
{
    if (argc ==5)
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
                fprintf(stderr,"failed in validation of encode args");
                return 1;
            }
        }
        else if(check_operation_type(argv) == e_decode)
        {

        }
        else 
        {
            printf("\n --------Invalid option--------- \n ");
            return 1;
        }

    }
}