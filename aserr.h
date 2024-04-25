#ifndef ASERR_H
#define ASERR_H
  
#include <stdio.h>
#include <stdint.h>
#define ASERR_INLINE __attribute__((always_inline))


                  /** Deprecated **/
#define asm_macro_impl(type,raw_val,output) do{\
  type __intermediate##raw_val = raw_val;\
  asm volatile(\
    "movq %0, %%rax\t\n"\
    "=r": (output)\
    "r" : (__intermediate##raw_val)\
    :"%ebx" \
  );\
}while(0)

#define ERR_REG %%eax
#define ERR int32_t

ASERR_INLINE inline void set_rax(int64_t value);
ASERR_INLINE inline void set_rbx(int64_t value);

/** optimal 32 bit error code that will actually be very usefull **/

ASERR_INLINE inline void set_eax(int32_t value);
ASERR_INLINE inline void set_ebx(int32_t value);
ASERR_INLINE inline int32_t get_eax();
ASERR_INLINE inline int32_t get_ebx();
ASERR_INLINE inline int64_t get_rax();
ASERR_INLINE inline int64_t get_rbx();
ASERR_INLINE inline void aserr_push(ERR err);
ASERR_INLINE inline ERR aserr_pop();
/** Generic selection macro for pushing into the registers of varing data types **/

#define set_ax(val) do{\
  _Generic(val,\
    int32_t: set_eax(val),\
    int64_t: set_rax(val)\
  );  \
}while(0)

#define set_bx(val) do{\
  _Generic(val,\
    int32_t: set_ebx(val),\
    int64_t: set_rbx(val)\
  );\
}

#endif // ASSER_H


#ifdef ASERR_IMPLEMENTATION

ASERR_INLINE inline void set_rax(int64_t value) {
  asm volatile(
    "movq %0, %%rax\n\t"
    :
    : "r" (value)
    : "rax"
  );
}

ASERR_INLINE inline void set_rbx(int64_t value){
  asm volatile(
    "movq %0, %%rax\n\t"
    :
    : "r" (value)
  );
}

ASERR_INLINE inline void set_eax(int32_t value){
  asm volatile(
    "mov %0, %%eax\n\t"
    :
    : "r" (value)
  );
}

ASERR_INLINE inline void set_ebx(int32_t value){
  asm volatile(
    "mov %0, %%ebx\n\t"
    :
    :"r" (value)
    :"ebx"
  );
}

ASERR_INLINE inline int32_t get_eax(){
  int32_t res = {0};
  
  asm volatile(
    "mov %%eax, %0\n\t"
    : "=r" (res)
    : 
    : "eax"
  );

  return res;
}

ASERR_INLINE inline int32_t get_ebx(){
  int32_t res = {0};
  
  asm volatile(
    "mov %%ebx, %0\n\t"
    : "=r" (res)
    :
    : "ebx"
  );

  return res;
}

ASERR_INLINE inline int64_t get_rax(){
  int64_t res = {0};
  
  asm volatile(
    "movq %%rax, %0\n\t"
    : "=r" (res)
    :
    : "rax"
  );

  return res;
}

ASERR_INLINE inline int64_t get_rbx(){
  int64_t res = {0};

  asm volatile(
    "movq %%rbx, %0\n\t"
    : "=r" (res)
    :
    : "eax"
  );

  return res;
}

ASERR_INLINE inline void aserr_push(ERR err){
  asm volatile(
    "mov %0, %%ebx\n\t"
    : 
    : "r" (err)
    : "ebx"
  );
}

ASERR_INLINE inline ERR aserr_pop(){
  ERR result = {0};
  
  asm volatile(
    "mov %%ebx, %0\n\t"
    :"=r" (result)
    :
    : "ebx"
  );
  return result;
}

#endif 
