#include <stdio.h>
#include <stdlib.h>

int main(void) {

  for(int i = 0; i < 20; i++){
    printf("%i\n", rand() % 10);
  }
  return 0;
}