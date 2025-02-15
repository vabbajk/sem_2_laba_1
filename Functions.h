#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Header.h"



void writeDataToFile(const char *filename, const char *str) {
    int capacity = 10;
    int size = 0;

    int *numbers = malloc(capacity * sizeof(int));
    if (!numbers) {
        perror("Ашыпка выделення мемори");
        system("pause");
        exit(1);
    }

    char *token = strtok(str, " ");
    while (token != NULL) {

        int num = atoi(token);

        if (size >= capacity) {
            capacity *= 2;
            numbers = realloc(numbers, capacity * sizeof(int));
            if (!numbers) {
                perror("Ашыпка реаллока");
                system("pause");
                exit(1);
            }
        }
        numbers[size++] = num;

        token = strtok(NULL, " ");
    }

    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Ашыбка опенинг файл");
        free(numbers);
        system("pause");
        exit(1);
    }

    fwrite(numbers, sizeof(int), size, file);
    fclose(file);

    free(numbers);
}

int *read_binary_file(const char *filename) {
    int size = 0;
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Ашыбка опенинг файл");
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    size = file_size / sizeof(int);

    int *data = malloc(size * sizeof(int));
    if (!data) {
        perror("Ашыпка выделения мемори");
        fclose(file);
    }

    if (fread(data, sizeof(int), size, file) != size) {
        perror("Ашыпка чтення дата фром файле");
        free(data);
        fclose(file);
    }

    fclose(file);

    print_array(data, size);

}

void findMinMax(const char *filename, int *min_value, int *max_value) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ашыбка опенинг файл");
        *min_value = *max_value = 0;
        return;
    }

    int current_value;
    int is_first_value = 1;

    while (fread(&current_value, sizeof(int), 1, file) == 1) {
        if (is_first_value) {
            *min_value = *max_value = current_value;
            is_first_value = 0;
        } else {
            if (current_value < *min_value) {
                *min_value = current_value;
            }
            if (current_value > *max_value) {
                *max_value = current_value;
            }
        }
    }

    fclose(file);
}

int countMaxValues(const char *filename, int max_value) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Ашыбка опенинг файл");
        return -1;
    }

    int current_value = 0;
    int count = 0;

    while (fread(&current_value, sizeof(int), 1, file) == 1) {
        if (current_value == max_value) {
            count++;
        }
    }

    fclose(file);
    return count;
}

void replace_max_with_min(const char *filename, int max_val, int min_val) {
    FILE *file = fopen(filename, "r+b");
    if (!file) {
        perror("Ашыбка опенинг файл");
        return;
    }

    int current;
    int count_max = 0;


    while (fread(&current, sizeof(int), 1, file) == 1) {
        if (current == max_val) {
            count_max++;

            fseek(file, -sizeof(int), SEEK_CUR);

            fwrite(&min_val, sizeof(int), 1, file);

            fflush(file);
        }
    }

    fclose(file);
}

void sortPositiveNumbersInPlace(const char *filename) {
    FILE *file = fopen(filename, "r+b");
    if (!file) {
        perror("Ашыбка опенинг файл!!!");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size == 0) {
        printf("Файл пуст.\n");
        fclose(file);
        return;
    }

    size_t num_elements = file_size / sizeof(int);

    for (size_t i = 0; i < num_elements; i++) {
        int min_positive = INT_MAX;
        size_t min_index = -1;


        for (size_t j = i; j < num_elements; j++) {
            int current;
            fseek(file, j * sizeof(int), SEEK_SET);
            fread(&current, sizeof(int), 1, file);

            if (current > 0 && current < min_positive) {
                min_positive = current;
                min_index = j;
            }
        }

        if (min_index != -1 && min_index != i) {
            int temp;
            fseek(file, i * sizeof(int), SEEK_SET);
            fread(&temp, sizeof(int), 1, file);

            if (temp > 0 || min_positive < temp) {
                fseek(file, i * sizeof(int), SEEK_SET);
                fwrite(&min_positive, sizeof(int), 1, file);

                fseek(file, min_index * sizeof(int), SEEK_SET);
                fwrite(&temp, sizeof(int), 1, file);
            }
        }
    }

    printf("Положительные числа успешно отсортированы:");

    fclose(file);
}


