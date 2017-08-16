#include <stdio.h>

int mystrlen(char *s){
  int size = 0;
  while(*s++)size++;
  return size;
}

char *mystrcpy(char *d,char *s){
  int i = mystrlen(s);
  while(*s){
    *d = *s;
    *d++;
    *s++;
  }
  return d - i;
}

char *mystrncat(char *d,char *s,size_t n){
  int l = mystrlen(d) + n;
  d += mystrlen(d);
  while(n > 0){
    *d = *s;
    *d++;
    *s++;
    n--;
  }
  *d = '\0';
  return d - l;
}

int mystrcmp(const char *s1,const char *s2){
  while(*s1 != '\0' && *s2 != '\0'){
    if(*s1 > *s2){
      return 1;
    }
    if(*s1 < *s2){
      return -1;
    }
    *s1++;
    *s2++;
  }
  if(*s1 == '\0' && *s2 == '\0'){
    return 0;
  }else if(*s1 == '\0'){
    return 1;
  }else{
    return -1;
  }
}

char *mystrchr(const char *s,int c){
  while(*s && *s != c){
    *s++;
  }
  if(*s == c){
    return s;
  }else{
    return NULL;
  }
}

char *mystrstr(const char *hay,const char *needle){
  while(*hay){
    if(*hay == *needle){
      int n = mystrlen(needle);
      int c = 0;
      while(c < n){
	if(*(hay + c) != *(needle + c)){
	  break;
	}
	c++;
      }
      if(c == n){
	return hay;
      }
    }
    *hay++;
  }
  return NULL;
}

int main(){
  char s1[] = "Cheesecake";
  char s2[] = "Carrot";
  char s4[] = "Quagmire";
  char s3[] = "Quaill";
  char s5[] = "Heretic";
  char s6[] = "Longitudinal";
  char s7[] = "git";
  printf("Length of Cheesecake: %d\n",mystrlen(s1));
  printf("Copy Carrot to Cheesecake: %s\n",mystrcpy(s1,s2));
  printf("Cat Car to Carrotcake: %s\n",mystrncat(s1,s2,3));
  printf("Compare Quagmire to Quaill: %d\n",mystrcmp(s3,s4));
  printf("Find 'r' in Heretic: %s\n",mystrchr(s5,'r'));
  printf("Find 'git' in Longitudinal: %s\n",mystrstr(s6,s7));
  return 0;
}
