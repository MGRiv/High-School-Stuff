#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int nums[10];

int randgen(){
  int temp[1];
  int f = open("/dev/random",O_RDONLY);
  read(f,&temp[0],4);
  close(f);
  return temp[0];
}

int main(){
  int i;
  printf("Random Numbers:\n");
  for(i = 0; i < 10; i++){
    int temp = randgen();
    nums[i]=temp;
    printf("random %d: %d\n",i,temp);
  }
  int q = open("file",O_CREAT|O_WRONLY);
  printf("Writing to file\n");
  for(i = 0; i < 10; i++){
    write(q,&nums[i],4);
  }
  close(q);
  int r = open("file",O_RDONLY);
  int nums2[10];
  
  printf("Reading from file\n");
  read(r,nums2,40);
  close(r);
  for(i = 0;i < 10; i++){
    printf("random %d: %d\n",i,nums2[i]);
  }
  return 0;
}
