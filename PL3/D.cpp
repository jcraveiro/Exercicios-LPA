#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int input[502][502] = {{0}};
int matrix[502][502] = {{0}};
int numeroHoras = 0;
int numeroPessoas = 0;

int max(int a, int b) { return (a > b)? a : b; }

void dynamicKnapsack(){
  int maior = 0;
  for(int i = 0; i <= numeroHoras; i++)
    matrix[0][i] = 0;

  for (int i = 0; i <= numeroPessoas; i++)
    matrix[i][0] = 0;

  for(int i = 1; i <= numeroPessoas; i++){
    for(int h = 1; h <= numeroHoras; h++) {
      for(int k = 1; k <= h; k++){
        int aux = input[i - 1][k - 1] + matrix[i - 1][h - k];
        if(aux > maior){
          maior = aux;
        }
      }


      matrix[i][h] = max(maior, matrix[i - 1][h]);
      maior = 0;
    }
  }

}



int main() {
  int tempID, tempHoras, tempLevel;

  scanf("%d %d", &numeroHoras, &numeroPessoas);

  for(int i = 0; i < (numeroHoras * numeroPessoas); i++) {
    scanf("%d %d %d\n", &tempID, &tempHoras, &tempLevel);
    input[tempID-1][tempHoras-1] = tempLevel;
  }

  dynamicKnapsack();

  printf("%d\n", matrix[numeroPessoas][numeroHoras]);

  return 0;
}
