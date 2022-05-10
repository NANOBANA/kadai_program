#include <stdio.h>
#include <stdlib.h>

typedef struct value
{
  double volt;
  double time;
  struct value *next;
} Value;

//ノードの生成
Value* node_create(double volt, double time)
{
  Value *node;
  node = (Value *)malloc(sizeof(Value));
  node->volt = volt;
  node->time = time;
  node->next = NULL;
  return node;
}

//連結リストの生成
Value *list_create()
{
  Value *list, *pt;
  list = (Value *)malloc(sizeof(Value));
  FILE *fp = NULL;
  double t = 0;
  double v = 0;
  fp = fopen("jx21023_0506_10Hz.txt", "r");
  while (fscanf(fp, "%lf,%lf", &t, &v) != EOF)
    {
      *list = *node_create(v, t);
      list = list->next;
    }
  return list;
}

//ピーク値の探索
int *list_search_peak(Value *list)
{
  Value *p0, *p1, *p2;
  p0 = list;
  p1 = list->next;
  p2 = p1->next;

  while(p2 != NULL)
    {
      if(((p0->volt) < (p1->volt))&&((p1->volt) > (p2->volt)))
        printf("経過時間:%lf[s],ピーク電圧:%lf[V]\n", p1->time, p1->volt);
      else
        {
          p0 = p1;
          p1 = p2;
          p2 = p2->next;
        }
    }
  return 0;
}

//連結リストの開放
int list_free(Value *p0)
{
  Value *p1;
  while (p0 != NULL)
    {
      p1 = p0->next;
      free(p0);
      p0 = p1;
    }
  return 0;
}


int main()
{
  Value *list, *pt;
  list = list_create();
  printf("%lf,%lf\n", list->time, list->volt);
  list_search_peak(list);
  list_free(list);

  return 0;
}
