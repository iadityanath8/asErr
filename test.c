#include <stdio.h>
#define ASERR_IMPLEMENTATION
#include "../asErr/aserr.h"
#define TEST_ON  1
#define TEST_OFF 0


/*
 *                        PROPOSITION AND NOTES 
 *
 *   
 *    PROPOSITION -> hide the stupid conplexity of asm volatile kind of 
 *    assembly shit and use macro to go crazy on building multiple return
 *    semantics.
 *  
 *    --> first for only basic values which are copy semantics 
 *    --> then we will go crazy on making macros to have pointer value 
 *    --> semantics 
 *    
 *    PROPOSITION -> Now Only for GNU Linux x86_64 
 *    --> Design Decision == Error Codes Like wrapped into enums (Kinda errno but returning stuff)
 *    --> Design Decision == Return NULL like go to have an error checking thing 
 *  
 *    NOTE -> 1->  () means dereference of a intermediate or a register both
 *            2->  mov for regular 32 bit moving of value in a register 
 *            3->  movq for moving quadwords or 64 bit value in a 64 bit register
 *            4->  Withing the usage of a pointer we can also use any mov or movq but not in case of normal values 
 *            5->  Would be a simple header only library with stb like header struture it does not need a separate src
 *                 include file for making it dynamic or statically linked it will just have few function and macro for 
 *                 error controlling and handling so it will not be too big so it will be just as normal header only library
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
      : "r" (value)
      );

  return 20;
}

typedef struct{
  int x,y;
}Point;

#if TEST_OFF

int main(){
  Point a = {1,2};
  Point* ptr = &a;

  Point* new_ptr = {0};

  asm volatile(
      "movq %0, %%rax\n\t"
      : "=r" (new_ptr)
      :"r" (ptr)
      );
  init_lib(); 
  printf("%d\n",new_ptr->x);
}

#endif



#if TEST_OFF

int main(){
  int value = 12;
  int* ptr = NULL;

  int* pppre = (int*)0x123456;// = {0};
  asm volatile(
      "movq %0, %%rbx\n\t"
      : 
      : "r" (ptr)
      );

  asm volatile(
      "movq %%rbx, %0"
      : "=r" (pppre)
      );

  printf("%ls\n",pppre);
  return 0;
}

#endif

#if TEST_OFF
int main() {
  int value = 10;
  int *ptr = &value;
  int result;

  asm volatile (
      "movl (%1), %0\n\t"  // Move the value pointed to by ptr into result
      : "=r" (result)  // Output operand
      : "r" (ptr)  // Input operand
      );

  printf("Dereferenced value: %d\n", result);

  return 0;
}
#endif

#if TEST_ON
int main(){
  set_ax(12);
  int a = {0};

  a = get_eax(); 
  printf("%d\n",a);
  return 0;
}

#endif

#if TEST_OFF
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
