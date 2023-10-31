#include <firmware_apis.h>

void main()
{
    #define dff_size  (*(volatile uint32_t*)0x0)  
    dff_size = 0x200;
    #define iterator  (*(volatile uint32_t*)0x4)  // first address in the ram store the iterator 
    iterator = 0;
    for (iterator = 8; iterator < dff_size; iterator++ ){
        // set_debug_reg2(iterator);
        *((unsigned int *) 0x00000000 + iterator) = 0x55555555; 
    }
    for (iterator = 8; iterator < dff_size; iterator++ ){
        // set_debug_reg2(iterator);
        if (*((unsigned int *) 0x00000000 + iterator) !=  0x55555555){
            set_debug_reg2(iterator);
            set_debug_reg1(0x1E); 
            return;
        }
    }
    for (iterator = 8; iterator < dff_size; iterator++ ){
        // set_debug_reg2(iterator);
        *((unsigned int *) 0x00000000 + iterator) = 0xAAAAAAAA; 
    }
    for (iterator = 8; iterator < dff_size; iterator++ ){
      // set_debug_reg2(iterator);
        if (*((unsigned int *) 0x00000000 + iterator) != 0xAAAAAAAA){
            // set_debug_reg2(iterator);
            set_debug_reg1(0x1E); 
            return;
        }
    }
    set_debug_reg1(0x1B);
}