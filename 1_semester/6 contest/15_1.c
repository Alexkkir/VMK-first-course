#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record {
  long long ip;
  char addr[101];
} record;

int main(void) {
  FILE *input = fopen("input.txt", "r");
  FILE *output = fopen("output.txt", "w");

  record* memory = (record*) malloc(100000 * sizeof(record));
  int n_sites, n_requests;
  fscanf(input, "%d", &n_sites);
  // scanf("%d", &n_sites);
  for (int i = 0; i < n_sites; i++) {
    // scanf("%s%d", memory[i].addr, &memory[i].ip);
    fscanf(input, "%s%lld", memory[i].addr, &memory[i].ip);
  }

  char addr_temp[101];
  // scanf("%d", &n_requests);
  fscanf(input, "%d", &n_requests);
  for (int i = 0; i < n_requests; i++) {
    fscanf(input, "%s", addr_temp);
    // scanf("%s", addr_temp);
    int ind;
    for (ind = 0; ind < n_sites && strcmp(memory[ind].addr, addr_temp); ind++);
    if (ind != n_sites) {
      // printf("%d\n", memory[ind].ip);
      fprintf(output, "%lld\n", memory[ind].ip);
    }
    else {
      fprintf(output, "-1\n");
      //printf("-1\n");
    }
  }
  fclose(input);
  fclose(output);
}
