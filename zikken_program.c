#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *fp = NULL;
  double time = 0; //経過時間
  double volt = 0;
  double currentvolt = 0; //現在の電圧
  double currentgrad = 0; //現在の傾き
  double pregrad = 0; //直前の傾き
  double prevolt = 0; //直前の電圧
  fp = fopen("jx21023_0506_10Hz.txt", "r");

  while(fscanf(fp, "%lf,%lf", &time, &volt) != EOF)
    {
      currentvolt = volt;
      //printf("%lf\n", pregrad); for debug
      currentgrad = currentvolt - prevolt; //現在の傾きの差分を出す
      if((currentgrad < 0) && (pregrad > 0))
        {
          printf("経過時間:%lf[s],ピーク電圧%lf[V]\n", time, currentvolt);
        }//傾きが正から負へ変わるときに極大となる

      prevolt = currentvolt;
      pregrad = currentgrad;

    }
}
