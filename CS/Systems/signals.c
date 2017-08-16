#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

static void sighandler(int signo){
  if(signo == SIGUSR1){
    int pid1 = fork();
    int status;
    if(pid1 == 0){
      printf("Update who\n");
      int q = open("dootdo.txt",O_CREAT|O_WRONLY|O_APPEND,0666);
      dup2(q,STDOUT_FILENO);
      char *f[2];
      f[0] = "who";
      f[1] = 0;
      execvp(f[0],f);
    }else{
      wait(&status);
    }
  }else if(signo == SIGUSR2){
    int pid1 = fork();
    int status;
    if(pid1 == 0){
      printf("Update ps\n");
      int q = open("manamana.txt",O_CREAT|O_WRONLY|O_APPEND,0666);
      dup2(q,STDOUT_FILENO);
      char *f[2];
      f[0] = "ps";
      f[1] = 0;
      execvp(f[0],f);
    }else{
      wait(&status);
    }
  }else if(signo == SIGINT){
    printf("Print contents\n");
    int f1 = open("dootdo.txt",O_RDONLY,0666);
    int f2 = open("manamana.txt",O_RDONLY,0666);
    char temp1[5000];
    char temp2[5000];
    int i1 = read(f1,temp1,sizeof(temp1));
    int i2 = read(f2,temp2,sizeof(temp2));
    if(i1 == -1){
      printf("Error %d: %s\n",errno,strerror(errno));
    }
    if(i2 == -1){
      printf("Error %d: %s\n",errno,strerror(errno));
    }
    printf("Who: %s\n",temp1);
    printf("PS: %s\n",temp2);
    exit(0);
  }else{
    exit(0);
  }
}

int main(){
  int pid = getpid();
  signal(SIGUSR1,sighandler);
  signal(SIGUSR2,sighandler);
  signal(SIGINT,sighandler);
  while(1){
    kill(pid,SIGUSR1);
    kill(pid,SIGUSR2);
    kill(pid,SIGINT);
  }
  return 0;
}
