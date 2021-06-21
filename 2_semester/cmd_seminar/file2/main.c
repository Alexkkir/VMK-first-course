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
    } else if(!strcmp(argv[1], "--add")) {
        if (argc <= 3 || argc > 4) {
            printf("'-add' ��������� ��������� ��� ���������\n");
        } else {
            int a, b;
            if(sscanf(argv[2], "%d", &a) != 1 || sscanf(argv[3], "%d", &b) != 1) {
                printf("'--add' �������� ������� ������������� ����������\n");
            } else {
                printf("%d + %d = %d\n", a, b, a+b);
            }
        }
    } else {
        printf("����������� ��������: '%s'. ������� %s --help ��� �������\n", argv[1], argv[0]);
    }
    return 0;
}
