#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

#define MIN_INT -2147483648
#define MAX_INT 2147483647


#define MIN(a, b) (a < b) ? a : b
#define MAX(a, b) (a > b) ? a : b

struct t{
    long long x;
    long long y;
};
long long First_for_x, First_for_y;


long long make_rotating(struct t A,struct t B,struct t C){
    return (B.x-A.x)*(C.y-B.y)-(B.y-A.y)*(C.x-B.x);
}

int comparator (const void *a,const void *b){
    struct t x=*(struct t *)a,y=*(struct t *)b;
    if (((x.x-First_for_x)*(y.y-x.y)-((x.y-First_for_y))*(y.x-x.x))!=0)
        return ((x.x-First_for_x)*(y.y-x.y)-((x.y-First_for_y))*(y.x-x.x));
    else
        return (((y.x-First_for_x)*(y.x-First_for_x)+((y.y-First_for_y))*(y.y-First_for_y))-((x.x-First_for_x)*(x.x-First_for_x)+((x.y-First_for_y))*(x.y-First_for_y)));
}

int main() {
    long long n;
    long long m;

    scanf("%lld",&n);
    struct t *main_array;

    main_array=(struct t*) malloc (sizeof(struct t)*(n + 2));

    for (long long i=0;i<n;i++){
        scanf("%lld%lld",&main_array[i].x,&main_array[i].y);
        m++;
    }

    long long k=0;
    for (long long i=1;i<n;i++){
        if (main_array[i].x<main_array[0].x){
            long long x_pointer=main_array[i].x;
            long long y_pointer=main_array[i].y;
            main_array[i].x=main_array[0].x;
            main_array[i].y=main_array[0].y;
            main_array[0].x=x_pointer;
            main_array[0].y=y_pointer;
        } else if (main_array[i].x==main_array[0].x && main_array[i].y>main_array[0].y){
            long long x_pointer=main_array[i].x;
            long long y_pointer=main_array[i].y;
            main_array[i].x=main_array[0].x;
            main_array[i].y=main_array[0].y;
            main_array[0].x=x_pointer;
            main_array[0].y=y_pointer;
        }

    }
    First_for_x=main_array[0].x;
    First_for_y=main_array[0].y;
    qsort(main_array+1,n-1,sizeof(struct t),comparator);
    long long main_array1[n];
    main_array1[k++]=0;
    main_array1[k++]=1;
    for (long long i=2;i<n;i++){
        while (k>=2 && make_rotating(main_array[main_array1[k-2]],main_array[main_array1[k-1]],main_array[i])>=0){
            k--;
        }
        main_array1[k++]=i;
    }
    double p=0;
    for (long long i=0;i<k-1;i++){
        p+=sqrt((main_array[main_array1[i]].x-main_array[main_array1[i+1]].x)*(main_array[main_array1[i]].x-main_array[main_array1[i+1]].x) + (main_array[main_array1[i]].y-main_array[main_array1[i+1]].y)*(main_array[main_array1[i]].y-main_array[main_array1[i+1]].y));
    }
    p+=sqrt((main_array[main_array1[0]].x-main_array[main_array1[k-1]].x)*(main_array[main_array1[0]].x-main_array[main_array1[k-1]].x) + (main_array[main_array1[0]].y-main_array[main_array1[k-1]].y)*(main_array[main_array1[0]].y-main_array[main_array1[k-1]].y));

    printf("%.2lf",p);
    if (m > 0) k++;
    return 0;
}
