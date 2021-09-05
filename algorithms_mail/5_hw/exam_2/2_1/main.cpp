#include <iostream>

using namespace std;

void fun(int *a, int n, int sum) {
    int i = 0, j = n - 1;
    while (i < j) {
        if (a[i] + a[j] < sum) {
            i++;
        }
        else if (a[i] + a[j] > sum) {
            j--;
        }
        else {
            printf("%d %d\n", a[i], a[j]);
            return;
        }
    }
    printf("Not found\n");
}

int comp (const int *i, const int *j)
{
return *i - *j;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int *a = (int*) malloc (n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), (int(*) (const void *, const void *)) comp);

    int x;
    for (int i = 0; i < m; i++) {
        scanf("%d", &x);
        fun(a, n, x);
    }
}
