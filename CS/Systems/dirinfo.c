#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>

int main(int argc, char *argv[]){
  DIR *f;
  char *p;
  if(argc - 1){
    p=argv[1];
  }else{
    p=".";
  }
  f = opendir(p);
  struct stat sb;
  struct dirent *q;
  int s = 0;
  while(q = readdir(f)){
    char path[256];
    strcpy(path,p);
    strcat(path,"/");
    strcat(path,q->d_name);
    stat(path,&sb);
    s += (int)sb.st_size;
  }
  rewinddir(f);
  printf("File Statistics: %s\n",p);
  printf("Directory Size: %d\n",s);
  printf("\nDirectories:\n");
  while(q = readdir(f)){
    if(q->d_type==0||q->d_type==4){
      printf("%s\n",q->d_name);
    }
  }
  rewinddir(f);
  printf("\nRegular Files:\n");
  while(q = readdir(f)){
    if(q->d_type==8){
      printf("%s\n",q->d_name);
    }
  }
  closedir(f);
  return 0;
}
