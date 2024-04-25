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

Error divide(int a,int b){
  if(b == 0){
    return New("Not allowed"); 
  }else{
    return (Error){};
  }
}

int main(){
  Error err = divide(4,0);
  printf("%s\n",err.message);
  return 0;
}
