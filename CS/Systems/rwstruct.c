#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

struct thing{char x;int a;};

int randgen(){
  int temp[1];
  int f = open("/dev/random",O_RDONLY);
  read(f,&temp[0],4);
  close(f);
  return temp[0];
}

int main(){
  int i;
  printf("Writing to file\n");
  struct thing l[10];
  for(i = 0;i<10;i++){
    struct thing q;
    q.a=randgen();
    q.x=i;
    l[i] = q;
  }
  for(i = 0;i<10;i++){
    printf("Test Structvalue %d: %d\n",i,l[i].a);
  }
  int f = open("file",O_CREAT|O_TRUNC|O_RDWR);
  write(f,&l,sizeof(struct thing) * 10);
  if (errno<0){
    printf("%s",strerror(errno));
  }
  printf("Reading from file\n");
  struct thing la[10];
  lseek(f,sizeof(struct thing) * -10,SEEK_CUR);
  read(f,&la,sizeof(struct thing) * 10);
  if (errno<0){
    printf("%s",strerror(errno));
  }
  for(i = 0;i<10;i++){
    printf("Structvalue %d: %d\n",i,la[i].a);
  }
  int p;
  printf("Taking user input to view value:\n");
  scanf("%d",&p);
  lseek(f,sizeof(struct thing)*p,SEEK_SET);
  struct thing temp;
  read(f,&temp,sizeof(temp));
  printf("Structvalue %d: %d\n",p,temp.a);
  
  printf("Taking user input to modify value\n");
  scanf("%d",&p);
  lseek(f,sizeof(struct thing)*p,SEEK_SET);
  read(f,&temp,sizeof(temp));
  temp.a=randgen();
  lseek(f,sizeof(struct thing)*p,SEEK_SET);
  write(f,&temp,sizeof(temp));
  lseek(f,0,SEEK_SET);
  read(f,&la,sizeof(l));
  for(i = 0;i<10;i++){
    printf("Structvalue %d: %d\n",i,la[i].a);
  }
  close(f);
  return 0;
}
