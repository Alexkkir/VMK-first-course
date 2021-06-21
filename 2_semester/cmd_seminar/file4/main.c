#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <locale.h>

int main(int argc, char **argv) {
    setlocale(LC_ALL, "Rus");

    int *a, *b; float *c; // указатели на массив
    int n, op, min, max; // параметры
    int fl_n = 0, fl_r = 0, fl_op = 0; // флаги задания параметров


    if(argc <= 1) {
        printf("Использование : \n\t%s —help or\n\t%s —n [a] —r [min] [max] —op 0|1|2|3\n", argv[0],argv[0]);
        return 0;
    }
    if(!strcmp(argv[1], "--help")){
        printf("Здесь могла бы быть справочная информация.\n");
        return 0;
    }

    for( int i = 1 ; i < argc; i++) {
        if(!strcmp(argv[i], "--n")){
            fl_n = 1;
            if(i+1>argc-1 || sscanf(argv[i+1], "%d", &n) != 1) {
                printf("'--n' параметр требует целочисленного аргумента\n");
                return 0;
            }
        }

        if(!strcmp(argv[i], "--r")){
            fl_r = 1;
            if(i+1>argc-1 || sscanf(argv[i+1], "%d", &min) != 1 || i+2>argc-1 || sscanf(argv[i+2], "%d", &max) != 1){
                printf("'--r' параметр требует пару целочисленных аргументов\n");
                return 0;
            }
        }

        if(!strcmp(argv[i], "--op")){
            fl_op = 1;
            if(i+1>argc-1 || sscanf(argv[i+1], "%d", &op) != 1 ) {
                printf("'--op' параметр требует аргумента 0|1|2|3\n");
                return 0;
            }
        }

    }

    if(fl_n == 0 & fl_r == 0 & fl_op != 0){
        n = 10;
        min = 0;
        max = 100;
        printf("По умолчанию: n = %d min, max = %d, %d \n",n,min,max);
        printf("Задано: ор = %d \n", op);
    }else if(fl_n == 0 & fl_r != 0 & fl_op == 0){
        n = 10;
        op = 0;
        printf("По умолчанию: n = %d op = %d \n",n,op);
        printf("Задано: min, max = %d, %d \n",min,max);
    }else if(fl_n != 0 & fl_r == 0 & fl_op == 0){
        op = 0;
        min = 0;
        max = 100;
        printf("По умолчанию: op = %d min, max = %d, %d \n",op,min,max);
        printf("Задано: n = %d \n",n);
    }else if(fl_n == 0 & fl_r != 0 & fl_op != 0){
        n = 10;
        printf("По умолчанию: n = %d \n",n);
        printf("Задано: ор = %d min, max = %d, %d \n", op,min,max);
    }else if(fl_n != 0 & fl_r != 0 & fl_op == 0){
        op = 0;
        printf("По умолчанию: op = %d \n",op);
        printf("Задано: n = %d min, max = %d, %d \n",n,min,max);
    }else if(fl_n != 0 & fl_r == 0 & fl_op != 0){
        min = 0;
        max = 100;
        printf("По умолчанию: min, max = %d, %d \n",min,max);
        printf("Задано: n = %d op = %d \n",n,op);
    }else if(fl_n != 0 & fl_r != 0 & fl_op != 0){
        printf("Задано: n = %d op = %d min, max = %d, %d \n",n,op,min,max);
    }

    // Выделение памяти
    a = (int*)malloc(n * sizeof(int));
    b = (int*)malloc(n * sizeof(int));
    c = (float*)calloc(n , sizeof(float));

    srand(time(NULL));
    for (int j = 0; j<n; j++){
        a[j] = rand()%(max - min + 1) + min;
        b[j] = rand()%(max - min + 1) + min;
        if(op == 0){
            c[j] = a[j] + b[j];
        }else if(op == 1){
            c[j] = a[j] - b[j];
        }else if(op == 2){
            c[j] = a[j] * b[j];
        }else if(op == 3){
            c[j] = (float)a[j] / b[j];
        }else{
            printf("Код операции задан не верно ! \n");
        return 0;
        }
        printf("a: %d ", a[j]);
        printf("b: %d ", b[j]);
        printf("c: %g \n", c[j]);
    }
    free(a);
    free(b);
    free(c);
    return 0;
}
