#include <stdio.h>

/*
 *
 *
 *  
 *  PROPOSITION -> hide the stupid conplexity of asm volatile kind of 
 *  assembly shit and use macro to go crazy on building multiple return
 *  semantics
 *  --> first for only basic values which are copy semantics 
 *  --> then we will go crazy on making macros to have pointer value 
 *  --> semantics 
 *
 *
 *
 */

#if 0
int main() {
    int a = 5;
    int b = 7;
    int result;

    asm volatile (
        "add %2, %1\n\t"   // Add operand 1 (b) to operand 0 (a)
        : "=r" (result)    // Output: result will contain the sum
        : "r" (a), "r" (b) // Inputs: a and b are the values to be added
    );

    printf("Result: %d\n", result); // Print the result
    return 0;
}
#endif

/***
 *
 *        "=r" means writtable valur 
 *        "r"  means readable or input value
 *        "r+" means both readable and writtable value in inline assembly
 *
 */

int ret_val(){
  int value = 12;
  asm volatile (
    "mov %0, %%ebx\n\t"
    :
    :"r" (value)
    );

  return 20;
}

#if 1
int main() {
  int x = 10;
  int y = 0;

//  asm volatile (
//    "add %1, %0\n\t"
//    : "=r" (y)
//    : "r" (x)
//  );
  
  y = ret_val();
  
  asm volatile (
    "mov %%ebx, %0\n\t"
    : "=r" (x)
  );
  
  printf("%d %d\n",x,y);
  return 0;
}
#endif
