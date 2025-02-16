#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#include <math.h>

int validate_and_parse_int(const char *input, int *output) {
    if (input == NULL || *input == '\0') {
        return 0;
    }

    const char *ptr = input;
    int is_negative = 0;

    if (*ptr == '+' || *ptr == '-') {
        is_negative = (*ptr == '-');
        ptr++;
    }

    if (*ptr == '\0') {
        return 0;
    }

    long result = 0;
    while (*ptr != '\0') {
        if (*ptr < '0' || *ptr > '9') {
            return 0;
        }

        int digit = *ptr - '0';

        if ((!is_negative && result > (INT_MAX - digit) / 10) ||
            (is_negative && -result < (-INT_MIN + digit) / 10)) {
            return 0;
        }

        result = result * 10 + digit;
        ptr++;
    }

    *output = is_negative ? -(int)result : (int)result;
    return 1;
}

int input_int(int *output) {
    char buffer[100];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        while (getchar() != '\n');
        return 0;
    }

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
    }

    return validate_and_parse_int(buffer, output);
}

int check_int_1(char *input) {
    if (input == NULL || *input == '\0') {
        return 0;
    }
    const char *ptr = input;
    int is_negative = 0;
    if (*ptr == '-') {
        is_negative = 1;
        ptr++;
    }
    if (*ptr == '\0') {
        return 0;
    }
    long result = 0;
    while (*ptr != '\0') {
        if (*ptr < '0' || *ptr > '9') {
            return 0;
        }
        int digit = *ptr - '0';

        if (is_negative) {
            if (-result < (INT_MIN + digit) / 10) {
                return 0;
            }
        } else {
            if (result > (INT_MAX - digit) / 10) {
                return 0;
            }
        }
        result = result * 10 + digit;
        ptr++;
    }
    return 1;
}

char* new_input_metod() {
    int size = 0;
    int current_pointer = 0;
    int has_num = 0;
    char* line = (char*)malloc(1);
    if (line == NULL) {
        return NULL;
    }
    line[0] = '\0';

    while (1) {
        char key = _getch();

        if (key == ' ') {

            if (size > 0 && line[size - 1] != ' ' && line[size - 1] != '-') {
                char* temp = realloc(line, size + 2);
                if (temp == NULL) {
                    free(line);
                    return NULL;
                }
                line = temp;
                line[size] = ' ';
                line[size + 1] = '\0';
                printf(" ");
                size++;
                has_num = 0;
            }
        }

        else if (key == '-') {

            if (size == 0 || line[size - 1] == ' ') {
                char* temp = realloc(line, size + 2);
                if (temp == NULL) {
                    free(line);
                    return NULL;
                }
                line = temp;
                line[size] = '-';
                line[size + 1] = '\0';
                printf("-");
                size++;
                current_pointer = size - 1;
                has_num = 1;
            }
        }

        else if (key >= '0' && key <= '9') {

            if(line[size-1] == '0' && (line[size-2] == ' ' || line[size-2] == '-') || (size == 1 && line[0] == '0'))  { continue;}


            if (has_num) {

                int buf_size = (size - current_pointer) + 2;
                char* buf = (char*)malloc(buf_size);
                if (buf == NULL) {
                    free(line);
                    return NULL;
                }
                int iter = 0;
                for (int i = current_pointer; i < size; i++) {
                    buf[iter++] = line[i];
                }
                buf[iter++] = key;
                buf[iter] = '\0';

                if (check_int_1(buf)) {
                    char* temp = realloc(line, size + 2);
                    if (temp == NULL) {
                        free(buf);
                        free(line);
                        return NULL;
                    }
                    line = temp;
                    line[size] = key;
                    line[size + 1] = '\0';
                    printf("%c", key);
                    size++;
                }
                free(buf);
            } else {

                char* temp = realloc(line, size + 2);
                if (temp == NULL) {
                    free(line);
                    return NULL;
                }
                line = temp;
                line[size] = key;
                line[size + 1] = '\0';
                printf("%c", key);
                current_pointer = size;
                size++;
                has_num = 1;
            }
        }

        else if (key == '\b') {
            if (size > 0) {
                size--;
                char* temp = realloc(line, size + 1);
                if (temp == NULL) {
                    free(line);
                    return NULL;
                }
                line = temp;
                line[size] = '\0';


                printf("\b \b");


                if (size == 0 || line[size - 1] == ' ' || line[size - 1] == '-') {
                    has_num = 0;
                }
            }
        }
        else if (key == '\r' || key == '\n') {
            if(line[size-1] != '-' && size != 0) {
                char *temp = realloc(line, size + 2);
                if (temp == NULL) {
                    free(line);
                    return NULL;
                }
                line = temp;
                line[size] = '\0';
                size++;
                break;
            }
        }
    }

    return line;
}

void getMousePosition(POINT *point) {
    GetCursorPos(point);
}

int lerp(int start, int end, float t) {
    return (int)(start + t * (end - start));
}

void enableAnsiColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void moveCursor(int row, int col) {
    COORD coord = { (short)col, (short)row };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

double calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void print_array(int *data, int size)
{
    puts("\n");
    for(int i = 0; i < size; i ++)
    {
        printf("%d ", data[i]);
    }
    puts("\n");
}

