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
                        
            }
        }
    }

}