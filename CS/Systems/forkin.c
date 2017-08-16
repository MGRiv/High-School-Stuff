#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

int randgen(){
  int temp[1];
  int f = open("/dev/random",O_RDONLY);
  read(f,&temp[0],4);
  close(f);
  if(temp[0] < 0){
    return -1 * temp[0];
  }else{
    return temp[0];
  }
}

int main(){
  printf("Forking...\n\n");
  int r1 = 5 + randgen()%15;
  int r2 = 5 + randgen()%15;
  int r = r1 + r2;
  int pid1 = fork();
  int pid2;
  int status;
  if(pid1 == 0){
    printf("Child 1 Sleeping...\n");
    sleep(r1);
    printf("Sleep Time: %d\n",r1);
  }else{
    wait(&status);
    printf("Child 1 @ PID %d: Done\n\n",pid1);
    pid2 = fork();
    if(pid2 == 0){
      printf("Child 2 Sleeping...\n");
      sleep(r2);
      printf("Sleep Time: %d\n",r2);
    }else{
      wait(&status);
      printf("Child 2 @ PID %d: Done\n\n",pid2);
    }
  }
  if(pid1 > 0 && pid2 > 0){
    printf("Parent @ PID %d: Done\n",getpid());
    printf("Total Sleep Time: %d\n",r);
  }
  return 0;
}
