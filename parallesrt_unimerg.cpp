#include <iostream>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

#define THREADS 200

struct arrs {
  int *a,b,c;
};


void *sort(void *y){
  arrs *x=(arrs*)y;
  int t,s=x->b,e=x->c;int *arr=x->a;
  for (size_t i = s; i <= e; i++) {
    for (size_t j = i+1; j <= e; j++) {
      if (arr[i]>arr[j]) {
        t=arr[j];arr[j]=arr[i];arr[i]=t;
      }
    }
  }
}
int qwerty,myLET,*haltroll;
inline int smallest(int them[THREADS],int *roll){
  int small,it=0;qwerty=0;
  for (qwerty;qwerty <= THREADS; qwerty++) {
    if ((roll[qwerty]<haltroll[qwerty])) {
      small=them[qwerty];it = qwerty;break;
    }
  }
  for ( qwerty; qwerty <= THREADS; qwerty++) {
    if ((small>them[qwerty])&&(roll[qwerty]<haltroll[qwerty])) {
      small=them[qwerty];it = qwerty;
    }
  }
  roll[it]++;
  return small;
}


void psort(int arr[],int l){
  int ar[(THREADS*2)+1],t;
  int leftover=l-(l%THREADS);
  for (size_t i = leftover; i < l; i++) {
    for (size_t j = i+1; j < l; j++) {
      if (arr[i]>arr[j]) {
        t=arr[i];arr[i]=arr[j];arr[j]=t;
      }
    }
  }
  if(l>=THREADS){
    pthread_t thread[THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  size_t i,j;
    int leT=l/THREADS;ar[0]=0;
    arrs send[THREADS*2];
    for (i = 0; i < (THREADS*2); i+=2) {
      ar[i+1]=(ar[i+2]=leT+ar[i])-1;
      send[i]={arr,ar[i],ar[i+1]};
      pthread_create(thread+(i/2),&attr,sort,(void*)(send+i));
    }int ptj,fails=0;
    for(i=0;i<THREADS;i++){
      ptj=pthread_join(thread[i], NULL);
      if(ptj==0){i--;fails++;}
      if(fails>100){return;}
    }
    haltroll=(int*)malloc((THREADS+1)*sizeof(int));
    int comps[THREADS+1],*roll;roll=(int*)malloc((THREADS+1)*sizeof(int));
    int *myarr=(int*)malloc(sizeof(int)*(leT*(THREADS+1)));
    size_t yi;roll[0]=0;haltroll[0]=leT;
    for (i = 1; i < THREADS; i++) {
      haltroll[i]=(roll[i]=roll[i-1]+leT)+leT;
    }haltroll[THREADS]=(l);roll[THREADS]=(THREADS*leT);
    myLET=leT;
    for (i = 0; i < (l); i++) {
      for (yi = 0; yi <= THREADS; yi++) {
        comps[yi]=arr[roll[yi]];
      }
      int thats=smallest(comps,roll);
      myarr[i]=thats;
    }
    free(roll);
    for (i = 0; i < (l); i++) {
      arr[i]=myarr[i];
    }
  }
}

int main(int argc, char const *argv[]) {
  int arry[458999];
  for (int i = 0; i < 458999; i++) {
    arry[i]=i%1234;
  }
  psort(arry,(sizeof(arry)/4));
  /*cout<<'\n';
  for (size_t i = 0; i < (sizeof(arry)/4); i++) {
    cout<<arry[i]<<",";
  }*/
  return 0;
}
