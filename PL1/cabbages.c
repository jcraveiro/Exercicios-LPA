#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int known_scores_x[5];
int known_scores_y[5];
int memoization_array[1000][1000];
int size = 0;
unsigned long long int counter = 1;
unsigned long long int counter_temp = 0;
int aux = 0;
int aux_call = 0;
void shell_sort (int *a, int *b, int n)
{
  int h, i, j, t, y;
  for (h = n; h /= 2;)
  {
    for (i = h; i < n; i++)
    {
      t = a[i];
      y = b[i];

      for (j = i; j >= h && t < a[j - h]; j -= h)
      {
        a[j] = a[j - h];
        b[j] = b[j-h];
      }
      a[j] = t;
      b[j] = y;
    }
  }
}

int check_consistency(int *a, int *b)
{
  int i;

  for (i = 0; i < size-1; i++)
  {
    if (a[i] > a[i+1])
    {
      return -1;
    }

    if (b[i] > b[i+1])
    {
      return -1;
    }
  }
  return 0;
}

int recursive_counter(int x, int y)
{
  aux_call++;
  if (memoization_array[x][y] != 0)
  {
    return counter_temp += memoization_array[x][y];
  }

  if (x == known_scores_x[aux] || y == known_scores_y[aux])
  {
    memoization_array[x][y] = 1;
    counter_temp++;
    return counter_temp;
  }

  if (memoization_array[x+1][y] == 0)
  {
    recursive_counter(x+1, y);
  }
  else
  {
    counter_temp += memoization_array[x+1][y];
  }

  if (memoization_array[x][y+1] == 0)
  {
    recursive_counter(x, y+1);
  }
  else
  {
    counter_temp += memoization_array[x][y+1];
  }

  if (memoization_array[x][y] == 0)
  {
    memoization_array[x][y] = (memoization_array[x+1][y] + memoization_array[x][y+1]);
  }
  return 0;
}


int main()
{
  int n_case_tests = 0;
  int i;
  int j;
  int k;


  scanf("%d", &n_case_tests);

  for (i = 0; i < n_case_tests; i++)
  {
    counter = 1;
    counter_temp = 0;
    aux = 0;

    scanf("%d", &size);
    for (j = 0; j < size; j++)
    {
      scanf("%d %d", &known_scores_x[j], &known_scores_y[j]);
    }

    shell_sort(known_scores_x,known_scores_y, size);

    if (check_consistency(known_scores_x,known_scores_y) == -1)
    {
      printf("-1\n");
    }
    else
    {
      memset(memoization_array, 0, sizeof(memoization_array[0][0]) * 1000 * 1000);
      recursive_counter(0,0);
      counter *= counter_temp;
      counter_temp = 0;
      aux++;

      for (k = 1; k < size; k++)
      {
        memset(memoization_array, 0, sizeof(memoization_array[0][0]) * 1000 * 1000);
        recursive_counter(known_scores_x[k-1], known_scores_y[k-1]);
        counter *= counter_temp;
        counter_temp = 0;
        aux++;
      }
      printf("%llu\n", counter);
    }
  }

  return 0;
}
