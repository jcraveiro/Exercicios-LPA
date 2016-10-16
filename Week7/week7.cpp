#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

#define MAX 5000

using std::queue;

int n;
int adjacency[MAX][MAX];
int firepower[MAX];
int localpower[MAX];
int visited[MAX];
int distance[MAX];
int is_enemy[MAX];
int exist_enemies;

void set_local_power()
{
  int temp_fire;
  int temp_local;

  for (int i = 0; i < n; i++)
  {
    temp_fire = firepower[i];
    temp_local = temp_fire;

    for (int j = 0; j < n; j++)
    {
      if (adjacency[i][j] == 1)
      {
        temp_local += firepower[j];
      }
    }
    localpower[i] = temp_local;
  }
}
void bfs()
{
  queue<int> bfsqueue;

  memset(visited, 0, sizeof(int) * n);
  memset(distance, -1, sizeof(int) * n);

  distance[0] = 0;
  visited[0] = 1;

  bfsqueue.push(0);

  while(!bfsqueue.empty())
  {
    int u =bfsqueue.front();
    bfsqueue.pop();


    for (int j = 0; j < n; j++)
    {
      int v = 0;

      if (adjacency[u][j] == 1)
      {
        v = j;
      }
      if(!visited[v])
      {
        visited[v]=1;
        distance[v]=distance[u]+1;
        bfsqueue.push(v);
      }
    }
  }
}

int get_distance()
{
  int temp_max_local;
  int max_local_index;

  max_local_index = 1000;
  for (int i = 1; i < n; i++)
  {
    if (localpower[i] < temp_max_local)
    {
      if (is_enemy[i] == 1)
      {
        if (visited[i] == 1)
        {
          temp_max_local = localpower[i];
          max_local_index = i;
        }
      }
    }
    else if (localpower[i] == temp_max_local)
    {
      if (is_enemy[i] == 1)
      {
        if (visited[i] == 1)
        {
          if (distance[i] < distance[max_local_index])
          {
            temp_max_local = localpower[i];
            max_local_index = i;
          }
        }
      }
    }
  }

  if (temp_max_local > 0)
  {
    return -6000;
  }

  return distance[max_local_index];
}

int main()
{
  int n_neighbours;
  int temp_distance;

  while(scanf ("%d", &n) == 1)
  {
    exist_enemies = 0;
    memset(is_enemy, 0, sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
      scanf("%d", &firepower[i]);

      if (firepower[i] < 0)
      {
        exist_enemies = 1;
        is_enemy[i] = 1;
      }
      else
      {
        is_enemy[i] = 0;
      }
      scanf("%d", &n_neighbours);

      for (int j = 0; j < n_neighbours; j++)
      {
        int temp;
        scanf("%d", &temp);
        adjacency[i][temp - 1] = 1;
      }
    }
    if (exist_enemies == 0)
    {
      printf("No threats!\n");
    }
    else
    {
      set_local_power();
      bfs();
      temp_distance = get_distance();
      if (temp_distance == -6000)
      {
        printf("No threats!\n");
      }
      else if(temp_distance == 0)
      {
        printf("No threats!\n");
      }
      else
      {
        printf("%d\n", temp_distance);
      }
    }
  }

  return 0;
}
