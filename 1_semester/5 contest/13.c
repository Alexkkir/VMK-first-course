#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_INT 2147483647
#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define INSIDE(i, j) (0 <= i && i <= n && 0 <= j && j <= m)

int **Height, **Delta_height;
int n, m, s_x, s_y, f_x, f_y;


void print(){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", Delta_height[i][j]);
    }
    printf("\n");
  }
}

void set_val(int x, int y) {
  int arr_left = 0, arr_down = 0, arr_right = 0, arr_top = 0;
  int digits[4];
  arr_right = (x < s_x);
  arr_down =  (y > s_y);
  arr_left =  (x > s_x);
  arr_top =   (y < s_y);
  int count = 0;
  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if (INSIDE(i, j) && (i == x || j == y) && !(i == x && j == y) && INSIDE(x, y)) { // стрелочки в порядке left, down, top, right
        digits[count] = Delta_height[i][j] + abs(Height[x][y] - Height[i][j]);
        count++;
      }
    }
  }
  int min_delta_height = MAX_INT;
  digits[0] *= arr_left;
  digits[1] *= arr_down;
  digits[2] *= arr_top;
  digits[3] *= arr_right;
  for (int i = 0; i < 4; i++)
  {
    if (digits[i] && digits[i] < min_delta_height) {
      min_delta_height = digits[i];
    }
  }
  Delta_height[x][y] = min_delta_height;
}

int main() {
  scanf("%d%d", &n, &m);
  scanf("%d%d%d%d", &s_x, &s_y, &f_x, &f_y);

  Height = (int**) calloc(n, sizeof(int*));
  for(int i = 0; i < n; i++)
    Height[i] = (int*) calloc(m, sizeof(int));

  Delta_height = (int**) calloc(n, sizeof(int*));
  for(int i = 0; i < n; i++)
    Delta_height[i] = (int*) calloc(m, sizeof(int));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &Height[i][j]);
    }
  }
  /*
  for (int i = s_x - 1; i <= s_x + 1; i++){
    for (int j = s_y - 1; j <= s_y + 1; j++){
      if ((i == s_x || j == s_y) && 0 <= s_x && s_x <= n && 0 <= s_y && s_y <= m){
        Delta_height[i][j] = abs(Height[i][j] - Height[s_x][s_y]);
      }
    }
  }

  //Delta_height[s_x][s_y] = 1;
  */
  const int epoch_finish = abs(s_x - f_x) + abs(s_y - f_y);
  int x, y;
  for (int epoch = 1; epoch < epoch_finish; epoch++) {
    for (int delta = -epoch; delta <= epoch; delta++) {
      x = s_x + delta;
      y = s_y + (epoch - abs(delta));
      set_val(x, y);
      y = s_y - (epoch - abs(delta));
      set_val(x, y);
    }
  }
  /*
  for (int epoch = 0 + 1; epoch < epoch_finish; epoch++) {
    for (int i = -epoch; i <= epoch; i++) {
      int y = s_x + i;
      int x;

      x = s_x - (epoch - abs(i));
      int flag = 1;
      if (0 <= x && x <= n && 0 <= y && y <= m) {
        if (i == -epoch)
          Delta_height[x][y] = abs(Height[x][y] - Height[x][y + 1]) + Delta_height[x][y + 1];
        if (-epoch < i && i < 0)
          Delta_height[x][y] = MIN(abs(Height[x][y] - Height[x][y + 1]) + Delta_height[x][y + 1], abs(Height[x][y] - Height[x + flag][y]) + Delta_height[x + flag][y]);
        if (epoch == 0)
          Delta_height[x][y] = abs(Height[x][y] - Height[x + flag][y]) + Delta_height[x + flag][y];
        if (0 < i < epoch)
          Delta_height[x][y] = MIN(abs(Height[x][y] - Height[x][y - 1]) + Delta_height[x][y - 1], abs(Height[x][y] - Height[x + flag][y]) + Delta_height[x + flag][y]);
        if (i == epoch)
          Delta_height[x][y] = abs(Height[x][y] - Height[x][y - 1]) + Delta_height[x][y - 1];
      }

      x = s_x + (epoch - abs(i));
      flag = -1;
      if (0 <= x && x <= n && 0 <= y && y <= m) {
        if (i == -epoch)
          Delta_height[x][y] = abs(Height[x][y] - Height[x][y + 1]) + Delta_height[x][y + 1];
        if (-epoch < i && i < 0)
          Delta_height[x][y] = MIN(abs(Height[x][y] - Height[x][y + 1]) + Delta_height[x][y + 1], abs(Height[x][y] - Height[x + flag][y]) + Delta_height[x + flag][y]);
        if (epoch == 0)
          Delta_height[x][y] = abs(Height[x][y] - Height[x + flag][y]) + Delta_height[x + flag][y];
        if (0 < i < epoch)
          Delta_height[x][y] = MIN(abs(Height[x][y] - Height[x][y - 1]) + Delta_height[x][y - 1], abs(Height[x][y] - Height[x + flag][y]) + Delta_height[x + flag][y]);
        if (i == epoch)
          Delta_height[x][y] = abs(Height[x][y] - Height[x][y - 1]) + Delta_height[x][y - 1];
      }
    }
  }
  */
  printf("%d\n", Delta_height[f_x][f_y]);
}
