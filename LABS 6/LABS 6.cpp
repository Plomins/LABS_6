#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <time.h>

int is_valid_integer(const char* str) {
    if (*str == '-' || *str == '+') 
        str++;
    if (!*str) return 0; 

    while (*str) {
        if (!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}


void merge(int* arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void sort_even_elements(int* arr, int n) {
    int* even = (int*)malloc(n * sizeof(int));
    int i, j = 0;

    for (i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            even[j++] = arr[i];
        }
    }

    if (j > 0) {
        mergeSort(even, 0, j - 1);
    }

    j = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            arr[i] = even[j++];
        }
    }

    free(even);
}

void sort_desc(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void auto_fill_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; 
    }
}

void auto_fill_matrix(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 100; 
        }
    }
}

void input_array(int* arr, int n) {
    printf("Выберите способ заполнения массива:\n1. Автоматическое заполнение\n2. Ручной ввод\nВаш выбор: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        auto_fill_array(arr, n);
        printf("Массив сгенерирован автоматически: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    else if (choice == 2) {
        for (int i = 0; i < n; i++) {
            char input[256];
            printf("Введите элемент %d: ", i + 1);
            scanf("%255s", input);

            while (!is_valid_integer(input)) {
                printf("Некорректный ввод. Введите целое число: ");
                scanf("%255s", input);
            }

            arr[i] = atoi(input);
        }
    }
    else {
        printf("Некорректный выбор!\n");
        exit(1);
    }
}

void input_matrix(int** matrix, int n, int m) {
    printf("Выберите способ заполнения матрицы:\n1. Автоматическое заполнение\n2. Ручной ввод\nВаш выбор: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        auto_fill_matrix(matrix, n, m);
        printf("Матрица сгенерирована автоматически:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }
    else if (choice == 2) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char input[256];
                printf("Введите элемент [%d][%d]: ", i + 1, j + 1);
                scanf("%255s", input);

                while (!is_valid_integer(input)) {
                    printf("Некорректный ввод. Введите целое число: ");
                    scanf("%255s", input);
                }

                matrix[i][j] = atoi(input);
            }
        }
    }
    else {
        printf("Некорректный выбор!\n");
        exit(1);
    }
}

void execute_task() {
    while (1) {
        int choice;
        printf("Выберите задачу:\n1. Сортировка четных элементов одномерного массива методом слияния\n2. Сортировка нечетных строк матрицы по убыванию суммы элементов\nВаш выбор: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int n;
            printf("Введите размер массива: ");
            scanf("%d", &n);

            int* arr = (int*)malloc(n * sizeof(int));
            if (!arr) {
                printf("Ошибка выделения памяти.\n");
                exit(1);
            }

            input_array(arr, n);
            sort_even_elements(arr, n);

            printf("Отсортированный массив: ");
            for (int i = 0; i < n; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");

            free(arr);
        }
        else if (choice == 2) {
            int n, m;
            printf("Введите количество строк и столбцов матрицы: ");
            scanf("%d %d", &n, &m);

            int** matrix = (int**)malloc(n * sizeof(int*));
            if (!matrix) {
                printf("Ошибка выделения памяти.\n");
                exit(1);
            }
            for (int i = 0; i < n; i++) {
                matrix[i] = (int*)malloc(m * sizeof(int));
                if (!matrix[i]) {
                    printf("Ошибка выделения памяти.\n");
                    exit(1);
                }
            }

            input_matrix(matrix, n, m);

            for (int i = 0; i < n; i++) {
                if ((i + 1) % 2 != 0) {
                    sort_desc(matrix[i], m);
                }
            }

            printf("Отсортированная матрица:\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    printf("%d ", matrix[i][j]);
                }
                printf("\n");
            }

            for (int i = 0; i < n; i++) {
                free(matrix[i]);
            }
            free(matrix);
        }
        else {
            printf("Некорректный выбор задачи.\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand((unsigned int)time(NULL)); 
    execute_task();
    return 0;
}
