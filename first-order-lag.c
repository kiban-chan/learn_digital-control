#include <stdio.h>
#include <stdlib.h>

// サンプリング周期
#define T_s 0.01  // 0.01s

// プラントモデル
#define T 0.5 // 時定数 0.5s
#define K 1 // DCゲイン 1

  /*
  伝達関数を双一次変換して変形したらこうなった
  Y[k] = (T_s + 2*T)^(-1) * (K*T_s*(U[k] + U[k-1]) - (T_s - 2*T)*Y[k-1])
  */

int main(void){
  double time = 0;
  double u_k0 = 0;
  double u_k1 = 0;
  double y_k0 = 0;
  double y_k1 = 0;

  FILE *fp;
  fp = fopen("./step_input1.csv", "r");

  if(fp == NULL){
    printf("failue\n");
    return -1;
  }else{
    printf("file opened\n");

    while(fscanf(fp, "%lf,%lf", &time, &u_k0) != EOF){
    

      printf("%f\t%f\n", time, u_k0);

      //y_k0 = (T_s + 2*T)^(-1) * (K*T_s*(u_k0 + u_k1) - (T_s - 2*T)*y_k1);
      //u_k1 = u_k0;
      //y_k1 = y_k0;
    }

    fclose(fp);
    return 0;
  }

}
