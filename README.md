EVERY BMP FILE IS MADE UP OF 3 SECTIONS - 
                                          
                                          1. BMP HEADDER
                                          2. INFO HEADER
                                          3. RGB DATA 
AT LAST THERE IS "EOF" 

HEADER :
  BMP HEADER(14 BYTES): 
  
        * IT CONSISTS OF 54 BYTES
        * FIRST 2 BYTES IS IMAGE SIGNATURE FOR EVERY BMP FILE IT IS 424D IN HEXA OR 'BM' IN CHARACTERS
        * NEXT 4 BYTES IS FOR STORNG THE FILE SIZE
        * NEXT 4 BYTES ARE RESERVED FOR FUTURE USE
        * NEXT 4 BYTES IS CALLED FILE OFFSET TO Raster DATA WHICH INDICATES FROM WHERE THHE RGB DATA STARTS

  INFO HEADER:
  
        * IT COMES RIGHT AFTER BMP HEADER
        * NEXT 4 BYTES GIVES THE SIZE OF INFO HEADER


  RGB DATA :
  
       * AFTER 54 BYTES OF HEADER THE RGB DATA COMES
       * EACH PIXEL IS MADE UP OF RED GREEN AND BLUE EACH COLOUR VARYING FROM 0x0 TO 0xFF THAT FOR ONE COLOR 1 BYTE SO EACH PIXEL HAS 3 BYTE
       
       


    

                                        
