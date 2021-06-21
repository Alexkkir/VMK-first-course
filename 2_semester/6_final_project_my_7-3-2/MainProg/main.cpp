#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <string.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN_3(a, b, c) MIN(a, MIN(b, c))
#define MAX_3(a, b, c) MAX(a, MAX(b, c))

/*
extern float f1 (float x);
extern float f2 (float x);
extern float f3 (float x);
extern float f1_d (float x);
extern float f2_d (float x);
extern float f3_d (float x);
*/

float f1 (float x) {
    return log2(x) / log2(M_E);
}

float f1_d (float x) {
    return 1 / x;
}

float f2 (float x) {
    return -2 * x + 14;
}

float f2_d (float x) {
    return -2;
}

float f3 (float x) {
    return 1 / (2 - x) + 6;
}

float f3_d (float x) {
    return 1 / ((x - 2) * (x - 2));
}


float F(float (*f) (float),
         float (*g) (float),
         float (*f_d) (float),
         float (*g_d) (float),
         float x)
{
    return x - (f(x) - g(x)) / (f_d(x) - g_d(x));
}

struct root_return {
    float x;
    int iters;
};

struct area_return {
    float square;
    float x_12;
    float x_13;
    float x_23;
    int n_inters;
};

struct root_return root(float (*f) (float),
                        float (*g) (float),
                        float (*f_d) (float),
                        float (*g_d) (float),
                        float a,
                        float b,
                        float eps)
{
    // calculating of roots
    int is_convex =
            (f(a) - g(a)) + (f(b) - g(b)) / 2 <
            (f((a + b) / 2) - g((a + b) / 2)) ?
            1 : 0;
    int is_increasing = (f(b) - g(b)) - (f(a) - g(a)) > 0 ? 1 : 0;

    float x;
    if (is_convex && is_increasing) x = a;
    if (!is_convex && !is_increasing) x = a;
    if (!is_convex && is_increasing) x = b;
    if (is_convex && !is_increasing) x = b;

    int n = 1 / eps + 100;
    for (int i = 0; i < n; i++) {
        x = F(f, g, f_d, g_d, x);
    }

    struct root_return ret_val = {x, n};
    return ret_val;
}

float integral(float (*f) (float),
                float a,
                float b,
                float eps)
{
    int n = 1 / eps + 100;
    float integral = 0;
    float delta = (b - a) / n;
    float x1 = a, x2 = x1 + delta;
    for (int i = 0; i < n - 1; i++) {
        integral += (f(x2) + f(x1)) / 2 * delta;
        x1 = x2;
        x2 += delta;
    }

    return integral;
}

struct area_return area(float a, float b, float eps) {
    int sum_iters = 0;
    float x_12, x_13, x_23;
    float int_1, int_2, int_3;
    float ans;

    struct root_return ret;
    ret = root(f1, f2, f1_d, f2_d, a, b, eps);
    x_12 = ret.x;
    sum_iters += ret.iters;

    ret = root(f1, f3, f1_d, f3_d, a, b, eps);
    x_13 = ret.x;
    sum_iters += ret.iters;

    ret = root(f2, f3, f2_d, f3_d, a, b, eps);
    x_23 = ret.x;
    sum_iters += ret.iters;

    float left = MIN_3(x_12, x_13, x_23),
            right = MAX_3(x_12, x_13, x_23),
            mid = x_12 + x_13 + x_23 - left - right;
    int is_normal = 1;

    float (*funs[3])(float);

    if (mid == x_12) {
        funs[1] = f3;
        if (x_13 == left) {
            funs[0] = f2;
            funs[2] = f1;
        }
        else {
            funs[2] = f2;
            funs[0] = f1;
        }
    }
    if (mid == x_13) {
        funs[1] = f2;
        if (x_12 == left) {
            funs[0] = f3;
            funs[2] = f1;
        }
        else {
            funs[2] = f3;
            funs[0] = f1;
        }
    }
    if (mid == x_23) {
        funs[1] = f1;
        if (x_12 == left) {
            funs[0] = f3;
            funs[2] = f2;
        }
        else {
            funs[2] = f3;
            funs[0] = f2;
        }
    }


    is_normal = funs[2](mid) > funs[1](mid);
    ans = integral(funs[2], left, mid, eps) +
          integral(funs[0], mid, right, eps) -
          integral(funs[1], left, right, eps);
    ans *= is_normal * 2 - 1;

    struct area_return ret_val = {ans, x_12, x_13, x_23, sum_iters};
    return ret_val;
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("This program calculates area between three functions:\n"
               "\tf1 = ln(x)\n"
               "\tf2 = -2x+14\n"
               "\tf3 = 1/(2-x)+6\n"
               "It is luckily to calculate area on [2.1, 6] with eps = 0.001\n"
               "For instruction guide type --help.\n");
        return 0;
    }

    if (strcmp(argv[1], "--help") == 0) {
        printf("Possible arguments:\n"
               "\t1. --calc crosses <f1|f2|f3> <f1|f2|f3> <a> <b> <eps>\n"
               "\t2. --calc integral <f1|f2|f3> <a> <b> <eps>\n"
               "\t3. --calc area <a> <b> <eps> [-c] [-i]\n"
               "\t4. --calc fun <f1|f2|f3> <x>\n"
               "\t5. --test <intersection|integral|area|all>\n");
        return 0;
    }

    float (*functions[3])(float) = {f1, f2, f3};
    float (*derivatives[3])(float) = {f1_d, f2_d, f3_d};

    if (argc < 3) {
        printf("Error: not enough arguments\n");
    } else if (!strcmp(argv[1], "--calc")) {
        if (!strcmp(argv[2],  "integral")) {
            if (!strcmp(argv[3], "f1") ||
                !strcmp(argv[3], "f2") ||
                !strcmp(argv[3], "f3"))
            {
                int f_id = (argv[3][1] - '1');
                float a_b_eps[3], a, b, eps;
                float ans;
                for (int i = 0; i < 3; i++) {
                    if (i + 4 >= argc) {
                        printf("Not enough arguments\n");
                        return 0;
                    } else if (sscanf(argv[i + 4], "%f", &a_b_eps[i]) != 1) {
                        printf("Error: argument %d incorrect\n", i);
                        return 0;
                    }
                }
                for (int i = 4 + 3; i < argc; i++) {
                    printf("Error: excess argument \"%s\" ignored\n", argv[i]);
                }
                a = a_b_eps[0], b = a_b_eps[1], eps = a_b_eps[2];
                ans = integral(functions[f_id], a, b, eps);
                printf("Integral under f%d on [%f, %f] is: %f\n", f_id + 1, a, b, ans);
                return 0;
            } else {
                printf("Error: unknown name \"%s\" of function\n", argv[3]);
                return 0;
            }
        }
        else if (!strcmp(argv[2], "area")) {
            float a_b_eps[3], a, b, eps;
            for (int i = 0; i < 3; i++) {
                if (i + 3 >= argc) {
                    printf("Error: enough arguments\n");
                    return 0;
                } else if (sscanf(argv[i + 3], "%f", &a_b_eps[i]) != 1) {
                    printf("Error: argument \"%s\" incorrect\n", argv[i + 3]);
                    return 0;
                }
            }
            a = a_b_eps[0], b = a_b_eps[1], eps = a_b_eps[2];

            int c_flag = 0, i_flag = 0;
            for (int i = 6; i < argc; i++) {
                if (!strcmp(argv[i], "-i"))
                    i_flag = 1;
                else if (!strcmp(argv[i], "-c"))
                    c_flag = 1;
                else {
                    printf("Error: unknown flag \"%s\" ignored\n", argv[i]);
                }
            }

            struct area_return ans = area(a, b, eps);
            printf("Area square is: %f\n", ans.square);
            if (c_flag) {
                printf("Points of crossing:\n"
                       "\t- between f1, f2: %f\n"
                       "\t- between f1, f3: %f\n"
                       "\t- between f2, f3: %f\n", ans.x_12, ans.x_13, ans.x_23);
            }
            if (i_flag) {
                printf("Number of iterations: %d\n", ans.n_inters);
            }
            return 0;
        } else if (!strcmp(argv[2], "crosses")) {
            if (!strcmp(argv[3], "f1") ||
                !strcmp(argv[3], "f2") ||
                !strcmp(argv[3], "f3"))
            {
                if (!strcmp(argv[4], "f1") ||
                    !strcmp(argv[4], "f2") ||
                    !strcmp(argv[4], "f3"))
                {
                    int f_id = (int) (argv[3][1] - '1');
                    int g_id = (int) (argv[4][1] - '1');
                    if (f_id == g_id) {
                        printf("Error: two same functions\n");
                        return 0;
                    } else {
                        float a_b_eps[3], a, b, eps;
                        for (int i = 0; i < 3; i++) {
                            if (i + 5 >= argc) {
                                printf("Not enough arguments\n");
                                return 0;
                            } else if (sscanf(argv[i + 5], "%f", &a_b_eps[i]) != 1) {
                                printf("Error: argument \"%s\" incorrect\n", argv[i]);
                                return 0;
                            }
                        }
                        for (int i = 5 + 3; i < argc; i++) {
                            printf("Error: excess argument \"%s\" ignored\n", argv[i]);
                        }
                        a = a_b_eps[0], b = a_b_eps[1], eps = a_b_eps[2];
                        struct root_return ans = root(functions[f_id], functions[g_id], derivatives[f_id], derivatives[g_id], a, b, eps);
                        printf("Functions f%d and f%d on [%f, %f] crosses in point: %f\n", f_id + 1, g_id + 1, a, b, ans.x);
                        return 0;
                    }
                }
            } else {
                printf("Error: unknown name \"%s\" of function\n", argv[3]);
                return 0;
            }
        } else if (!strcmp(argv[2], "fun")) {
            int f_id = argv[3][1] - '1';
            float x;
            sscanf(argv[4], "%f", &x);
            printf("Value of f%d in %f is: %f\n", f_id + 1, x, functions[f_id](x));
            return 0;
        }
        else {
            printf("Error: unknown command \"%s\"\n", argv[2]);
            return 0;
        }
    } else if (!strcmp(argv[1], "--test")) {
        if (!strcmp(argv[2], "all")) {
            float a = 2.1, b = 6, eps = 0.001;
            printf("Testing of integral with parameters a = %f, b = %f, eps = %f\n", a, b, eps);
            printf("\tfor f1: %f\n"
                   "\tfor f2: %f\n"
                   "\tfor f3: %f\n", integral(f1, a, b, eps), integral(f2, a, b, eps), integral(f3, a, b, eps));
            printf("\nTesting of crosses with parameters a = %f, b = %f, eps = %f\n", a, b, eps);
            printf("\tfor f1, f2: %f\n"
                   "\tfor f1, f3: %f\n"
                   "\tfor f2, f3: %f\n",
                   root(f1, f2, f1_d, f2_d, a, b, eps).x,
                   root(f1, f3, f1_d, f3_d, a, b, eps).x,
                   root(f2, f3, f2_d, f3_d, a, b, eps).x);
            printf("\nTesting of area with parameters a = %f, b = %f, eps = %f\n", a, b, eps);
            printf("Square is %f\n", area(a, b, eps).square);
        } else if (!strcmp(argv[2], "integral")) {
            float a = 3, b = 4, eps = 0.001;
            printf("Testing of integral with parameters a = %f, b = %f, eps = %f\n", a, b, eps);
            printf("\tfor f1: %f\n"
                   "\tfor f2: %f\n"
                   "\tfor f3: %f\n", integral(f1, a, b, eps), integral(f2, a, b, eps), integral(f3, a, b, eps));
        } else if (!strcmp(argv[2], "crosses")) {
            float a = 2.03, b = 7.89, eps = 0.001;
            printf("Testing of crosses with parameters a = %f, b = %f, eps = %f\n", a, b, eps);
            printf("\tfor f1, f2: %f\n"
                   "\tfor f1, f3: %f\n"
                   "\tfor f2, f3: %f\n",
                   root(f1, f2, f1_d, f2_d, a, b, eps).x,
                   root(f1, f3, f1_d, f3_d, a, b, eps).x,
                   root(f2, f3, f2_d, f3_d, a, b, eps).x);
        } else if (!strcmp(argv[2], "area")) {
            float a = 2.03, b = 7.89, eps = 0.001;
            printf("Testing of area with parameters a = %f, b = %f, eps = %f\n", a, b, eps);
            printf("Square is %f\n", area(a, b, eps).square);
        } else {
            printf("Error: unknown command \"%s\"\n", argv[2]);
        }
    } else {
        printf("Error: unknown flag \"%s\"\n", argv[1]);
    }
    return 0;
}
