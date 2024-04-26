#include <stdio.h>
#include <stdlib.h>


#define ERROR_INHERIT  const char* message;\
  ERR code;\
  void(*log)(Error* err,const char* msg);\

typedef struct Error Error;

typedef enum{
  ERR_HACKED,
  ERR_DIVIDE_BY_ZERO
}ERR;

struct Error{
  const char* message;
  ERR code;
  void(*log)(Error* err,const char* msg);
};

void Default_Logger(Error* err, const char* msg){ 
  fprintf(stderr,"FAILED MESSAGE: %s with error code %d\n",msg,err->code);
  exit(EXIT_FAILURE);
}

Error New(const char* msg){
  return (Error){
    .message = msg
  };
}

void divide(int a, int b) {
    Error err = {.message = "Message is in here\n", .code = 2, .log = Default_Logger};
    int t = 23;

    asm volatile(
        "mov %0,  %%eax\n\t"   // Move err.code into %eax
        "movq %1, %%rdx\n\t"   // Move t into %edx
        "movq %2, %%rcx\n\t"
        :
        : "r" (err.code), "r" (err.message), "r" (err.log)
        : "eax", "rdx"        // Specify clobbered registers
    );
}


// void move_struct(Error* err) {
//     asm volatile (
//         "push %0\n\t"   // Push message onto the stack
//         "push %1\n\t"   // Push code onto the stack
//         "push %2\n\t"   // Push log function pointer onto the stack
//         "add $24, %%rsp\n\t" // Adjust the stack pointer to balance the pushes
//         :
//         : "r" (err->message), "r" (err->code), "r" (err->log)
//         : "memory"      // Inform compiler about memory changes
//     );
// }


int main(){
  divide(12,12);
  int code = {0};
  char* code2 = {0};
  void(*fn)(Error* err,const char*p);

  Error e;
  asm volatile(
    "mov %%eax, %0\n\t"
    // "mov %%edx, %1\n\t"
    : "=r" (e.code)
  );

  asm volatile(
    "mov %%rdx, %0"
    : "=r" (e.message)
  );

  asm volatile(
    "mov %%rcx, %0"
    : "=r" (e.log)
  );

  e.log(&e,"MEOW");
  // printf("%s\n",e.message);
  return 0;
}
