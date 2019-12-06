#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// サンプリング周期
#define T_s 0.001  // 0.001s

// プラントモデル
#define T 0.1 // 時定数 0.1s
#define K 1 // DCゲイン 1

  /*
  一次遅れ系の伝達関数を双一次変換して変形したらこうなった
  Y[k] = (T_s + 2*T)^(-1) * (K*T_s*(U[k] + U[k-1]) - (T_s - 2*T)*Y[k-1])
  */

int main(void){
  double time = 0;
  double u_k0 = 0;
  double u_k1 = 0;
  double y_k0 = 0;
  double y_k1 = 0;
  double y_c = 0;
  double err = 0;

  FILE *fp_u, *fp_y;
  fp_u = fopen("./step_input1.csv", "r");
  fp_y = fopen("./step_output1.csv", "w");

  if(fp_u == NULL){
    printf("failue\n");
    return -1;
  }else{
    //printf("file opened\n");

    while(fscanf(fp_u, "%lf,%lf", &time, &u_k0) != EOF){
      // 離散時間系のシミュレーション(双一次変換)
      y_k0 = pow((T_s + 2*T), -1) * (K*T_s*(u_k0 + u_k1) - (T_s - 2*T)*y_k1);

      // 連続時間系のシミュレーション
      y_c = u_k0 * K * (1 - exp(-(time / T)));

      // (誤差) = (連続) - (双一次)
      err = y_c - y_k0;

      fprintf(fp_y, "%lf,%lf,%lf,%lf\n", time, y_k0, y_c, err);

      u_k1 = u_k0;
      y_k1 = y_k0;
    }

    fclose(fp_u);
    fclose(fp_y);
    return 0;
  }
}

