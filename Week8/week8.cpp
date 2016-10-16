#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>

#define MAX 800

using std::min;

int n;
int adjacency[MAX][MAX];
int ticks;
int val[MAX];
int low[MAX];
int parent[MAX];
int articulations[MAX];
int articulations_counter;


void dfs(int v)
{
  ticks++;
  val[v] = ticks;
  low[v] = val[v];


  for (int i = 0; i < n; i++)
  {
    if (adjacency[v][i] != -1)
    {
      int u = i;
      if (val[u] == -1)
      {
        parent[u] = v;
        dfs(u);

        low[v] = min(low[v], low[u]);
        if(val[v] == 1 && val[u] != 2)
        {
          printf("V = %d\n", v);
          articulations[articulations_counter] = v;
          articulations_counter++;
        }
        if (val[v] != 1 && low[u] >= val[v])
        {
          printf("V = %d\n", v);
          articulations[articulations_counter] = v;
          articulations_counter++;
        }
      }
      else if (u != parent[v])
      {
        low[v] = min(low[v], val[u]);
      }
    }
  }
}

int max_traffic()
{
  int max = 0;
  int temp;
  int node;

  for (int i = 0; i < articulations_counter; i++)
  {
    temp = 0;
    node = articulations[i];
    for (int j = 0; j < n; j++)
    {
      if (adjacency[node][j] != -1)
      {
        temp += adjacency[node][j];
      }
    }
    if (temp > max)
    {
      max = temp;
    }
  }
  return max;
}

int main()
{
  int n_neighbours;

  while(scanf ("%d", &n) == 1)
  {
    memset(adjacency, -1, sizeof(adjacency[0][0]) * MAX * MAX);

    for (int i = 0; i < n; i++)
    {
      scanf("%d", &n_neighbours);

      for (int j = 0; j < n_neighbours; j++)
      {
        int id;
        int load;

        scanf("%d %d", &id, &load);
        adjacency[i][id - 1] = load;
      }
    }


    memset(val, 0, sizeof(int) * MAX);
    memset(low, 0, sizeof(int) * MAX);
    memset(parent, 0, sizeof(int) * MAX);
    memset(articulations, 0, sizeof(int) * MAX);
    articulations_counter = 0;
    ticks = 0;

    for(int i = 0;i<n;i++)
  	{
  		val[i] = -1;
  	}

    for(int i = 0;i<n;i++)
  	{

  		dfs(i);
  	}

    if (articulations_counter == 0)
    {
      printf("Well designed city!\n");
    }
    else
    {
      printf("%d\n", max_traffic());
    }
  }
  return 0;
}
