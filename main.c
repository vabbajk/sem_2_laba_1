#include <stdio.h>
#include "Functions.h"



int main(int argc, char *argv[])
{


    setlocale(LC_ALL, "russian");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    if (argc != 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    puts("Вводите числа для заполнения бинарного файла : \n");

    const char *filename = argv[1];
    char* arr = new_input_metod();
    int  maxValue, minValue;

    printf("\n");

    writeDataToFile(filename, arr);

    findMinMax(filename, &minValue, &maxValue);

    printf("Максимальное значение: %d\n", maxValue);
    printf("Минимальное значение: %d\n", minValue);

    printf("Количество максимальных элементов: %d\n", countMaxValues(filename, maxValue));

    replace_max_with_min(filename,maxValue , minValue);
    printf("Файл после замены макисмальных элементов на минимальные: ");

    read_binary_file(filename);

    sortPositiveNumbersInPlace(filename);

    read_binary_file(filename);

    system("pause");

    const char *url = "https://ascii.live/rick";
    char command[256];
    snprintf(command, sizeof(command), "curl --insecure %s", url);
    system(command);

}