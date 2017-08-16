#import <stdio.h>

int mul35(){
  int sum = 0;
  int c = 1;
  while(c < 1000){
    if((c%3 == 0)||(c%5 == 0)){
      sum += c;
    }
    c++;
  }
  return sum;
}

int fibeven(){
  int s1 = 1;
  int s2 = 2;
  int sum = 2;
  while((s1 + s2)<4000000){
    if((s1 + s2)%2 == 0){
      sum += (s1 + s2);
    }
    int c = s2;
    s2 += s1;
    s1 = c;
  }
  return sum;
}

int main(){
  int s = mul35();
  int f = fibeven();
  printf("Problem 1: %d",s);
  printf("Problem 2: %d",f);
  return 0;
}
