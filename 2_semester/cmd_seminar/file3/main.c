#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


int main(int argc, char **argv)
{
    setlocale(LC_ALL, "Rus");


    if(argc <= 1) {
        printf("������������� \n\t%s --help or\n\t%s --ad [a] [b]\n", argv[0], argv[0]);
    }
    if(!strcmp(argv[1], "--help")) {
       printf("����� �������");
       return 0;
    }

    for (int i = 0; i < argc; i++) {
        if(!strcmp(argv[i], "--n")) {
            if(sscanf(argv[i+1], %d, &n) != 1) {
                printf("'--n' �������� ������� �������������� ���������\n");
            } else {
                printf("�������� ��������.\n");
                a = (int*) malloc(n * sizeof(int));
                b = (int*) malloc(n * sizeof(int))'
            }
        }
        if(!strcmp(argv[i], "--p")) {
            if(sscanf(argv[i+1], "%d", &n) != 1) {
                printf("--p' �������� ������� ��������� 0|1|2|3\n");
            } else {
                printf("AAAA.\n");
            }
        }
    }
    free(a);
    free(b);
    return 0;
}
