#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

int n_homeworks;
int current_day;
int max_overdue;
vector<pair<int,int> > pair_vector;

bool pairCompare(const pair<int, int>& firstElem, const pair<int, int>& secondElem)
{
  return firstElem.second < secondElem.second;
}

void greedy()
{
  int overdue_days;
  for (int i = 0; i < n_homeworks; i++)
  {
    current_day += pair_vector[i].first;
    if (current_day > pair_vector[i].second)
    {
      overdue_days = current_day - pair_vector[i].second;
      if (overdue_days >= max_overdue)
      {
        max_overdue = overdue_days;
      }
    }
  }
}

int main()
{
  int duration;
  int deadline;


  while(scanf("%d", &n_homeworks) == 1)
  {
    max_overdue = 0;
    pair_vector.clear();
    
    for (int i = 0; i < n_homeworks; i++)
    {
      scanf("%d %d", &duration, &deadline);
      pair_vector.push_back( make_pair(duration, deadline));
    }
    scanf("%d", &current_day);

    sort(pair_vector.begin(), pair_vector.end(), pairCompare);

    greedy();

    printf("%d\n", max_overdue);
  }

  return 0;
}
