#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n_jobs;
int n_processors;

int processors[15];

int processor_times[15][30];

int time;
int best_time;

int get_biggest_time()
{
  int biggest_time = 0;
  int i;

  for (i = 0; i < n_processors; i++)
  {
    if (processors[i] > biggest_time)
    {
      biggest_time = processors[i];
    }
  }

  return biggest_time;
}

int initial_average_time()
{
  int i;
  int j;
  int lowest;

  for (i = 0; i < n_jobs; i++)
  {
    lowest = 0;
    for (j = 0; j < n_processors; j++)
    {
      if (processor_times[j][i] < processor_times[lowest][i])
      {
        lowest = j;
      }
    }
    processors[lowest] += processor_times[lowest][i];
  }

  return get_biggest_time();

}

void backtrack(int job)
{
  int i;
  int temp;

  time = get_biggest_time();

  if (time >= best_time)
  {
    return;
  }

  if (job == n_jobs - 1)
  {
    best_time = time;
    return;
  }


  for (i = 0; i < n_processors; i++)
  {
    temp = processor_times[i][job + 1];
    if(processors[i] + processor_times[i][job + 1] < best_time)
    {
      processors[i] += temp;
      backtrack(job + 1);
      processors[i] -= temp;
    }
  }

  return;

}

int main()
{
  int i;
  int j;
  int k;
  int temp;

  scanf("%d", &n_jobs);
  scanf("%d", &n_processors);
  
  for (i = 0; i < n_processors; i++)
  {
    for (j = 0; j < n_jobs; j++)
    {
      scanf("%d", &processor_times[i][j]);
    }
  }

  best_time = initial_average_time();

  memset(processors, 0, sizeof(int) * 15);
  
  for (k = 0; k < n_processors; k++)
  {
    temp = processor_times[k][0];
    processors[k] += temp;
    backtrack(0);
    processors[k] -= temp;
  }

  printf("%d\n", best_time);

  return 0;
}
