#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int n_hours = 0;
int native_speakers = 0;

int proficiency_matrix[500][500];
int knapsack_matrix[501][501];

int max(int a, int b)
{
  return (a > b) ? a : b;
}

void knapsack()
{
  int i;
  int j;
  int k;
  int value;
  int cur_max = 0;

  memset(knapsack_matrix, 0, sizeof(knapsack_matrix[0][0]) * 501 * 501);
  
  for (i = 1; i <= native_speakers; i++)
  {
    for (j = 1; j <= n_hours; j++)
    {
      for (k = 1; k <= j; k++)
      {
        value = proficiency_matrix[i - 1][k - 1] + knapsack_matrix[i - 1][j - k];
        printf(" proficiency_matrix[i - 1][k - 1] == %d &&  knapsack_matrix[i - 1][j - k] == %d\n", proficiency_matrix[i - 1][k - 1],  knapsack_matrix[i - 1][j - k]);
        if (value > cur_max)
        {
          cur_max = value;
        }
      }

      printf("CUR MAX == %d && knapsack_matrix[i - 1][j] == %d\n",cur_max, knapsack_matrix[i - 1][j]);
      knapsack_matrix[i][j] = max(cur_max, knapsack_matrix[i - 1][j]);
      cur_max = 0;
    }
  }
}


int main()
{
  int i;
  int id;
  int hours;
  int proficiency;
  
  scanf("%d %d", &n_hours, &native_speakers);

  for (i = 0; i < n_hours * native_speakers; i++)
  {
    scanf("%d %d %d", &id, &hours, &proficiency);
    proficiency_matrix[id-1][hours-1] = proficiency;
  }

  printf("------------------------------------------------------------------------\n");

  for (int i = 0; i < native_speakers; i++)
  {
    for (int j = 0; j < n_hours; j++)
    {
      printf("%d ", proficiency_matrix[i][j]);
    }
    printf("\n");
  }
  

  knapsack();

  printf("%d\n", knapsack_matrix[native_speakers][n_hours]);

  printf("------------------------------------------------------------------------\n");

  for (int i = 0; i <= native_speakers; i++)
  {
    for (int j = 0; j <= n_hours; j++)
    {
      printf("%d ", knapsack_matrix[i][j]);
    }
    printf("\n");
  }
  
  return 0;
}
