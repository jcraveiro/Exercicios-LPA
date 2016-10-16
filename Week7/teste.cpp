#include <stdio.h>
#include <stdlib.h>

int main()
{
  int n;
  int firepower;
  int n_neighbours;
  int array[3];

  scanf ("%d", &n);

  for (int i = 0; i < n; i++)
  {
    scanf("%d", &firepower);
    scanf("%d", &n_neighbours);
    printf("firepower = %d && n_neighbours = %d\n", firepower, n_neighbours);
    for (int j = 0; j < n_neighbours; j++)
    {
      scanf("%d",&array[j]);
    }
  }
  for (int i = 0; i < n_neighbours; i++) {
    printf("Array[%d] == %d\n", i, array[i]);
  }
  return 0;
}
