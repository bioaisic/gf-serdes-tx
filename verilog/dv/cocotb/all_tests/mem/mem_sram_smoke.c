#include <firmware_apis.h>

void main()
{
    enable_debug();
    #define dff_size  (*(volatile uint32_t*)0x0)  
    dff_size = 0x70;
    #define iterator  (*(volatile uint32_t*)0x4)  // first address in the ram store the iterator 
    iterator = 0;
    // word access
    for (iterator = 8; iterator < dff_size; iterator+=7 ){
        // set_debug_reg2(iterator);
        *((unsigned int *)  0x00000000+iterator) = 0x55555555; 
    }
    for (iterator = 8; iterator < dff_size; iterator+=7 ){
        // set_debug_reg2(iterator);
        if (*((unsigned int *)  0x00000000+iterator) !=  0x55555555){
            set_debug_reg2(iterator);
            set_debug_reg1(0x1E); 
            return;
        }
    }

    // half word
    dff_size = 0x210;
    for (iterator = 0x140; iterator < dff_size; iterator+=7 ){
      // set_debug_reg2(iterator);
      *((unsigned short *) 0x00000000+iterator) = 0xAAAA; 
    }
    for (iterator = 0x140; iterator < dff_size; iterator+=7 ){
      // set_debug_reg2(iterator);
        if (*((unsigned short *) 0x00000000+iterator) != 0xAAAA){
            // set_debug_reg2(iterator);
            set_debug_reg1(0x1E); 
            return;
        }
    }

    // byte 

    dff_size = 0x630;
    for (iterator = 0x560; iterator < dff_size; iterator+=7){
      // set_debug_reg2(iterator);
      *((unsigned char *) 0x00000000+iterator) = 0x55; 
    }
    for (iterator = 0x560; iterator < dff_size; iterator+=7){
      // set_debug_reg2(iterator);
        if (*((unsigned char *) 0x00000000+iterator) !=  0x55){
            set_debug_reg2(iterator);
            set_debug_reg1(0x1E); 
            return;
        }
    }

    
    set_debug_reg1(0x1B);
}