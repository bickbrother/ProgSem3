/**
 * @file WordCont.c
 * @author Ignatiev Andrey (ignatiev.andreyka@gmail.com)
 * @brief Программа считает количсетво либо строк, либо байтов, либо слов в файле
 * 
 * Формат входных данных: "WordCont.exe <command> <file>"
 * Варианты command: -l --lines -- программа выведет количество строк в файле
 *                   -c --bytes -- программа выведет количество байт в файле
 *                   -w --words -- программа выведет количество слов файле
 * file - имя файла для которого надо выполнить указанные выше команды 
 * @version 0.1
 * @date 2021-10-23
 * 
 * @copyright Copyright (c) 2021
 * 
 **/

#include "cstdio"
#include "cstring"

/**
 * @brief Функция подсчета строк
 * 
 * @param [in] name <имя файла>
 * @param [out] out <количество строк>
 */ 

void linesCount(char *name, int *out) {
    char str;
    int counter = 1;
    FILE *fileproc;
    fileproc = fopen(name, "r");
    str = getc(fileproc);
    while (str != EOF) {
        str = getc(fileproc);
        if (str == '\n') {
            counter++;
        }
    }
    fclose(fileproc);
    *out = counter;
    return;
}

/**
 * @brief Функция подсчета байтов
 * 
 * @param [in] name <имя файла>
 * @param [out] out <количество байт>
 */

void bytesCount(char *name, int *out) {
    FILE *fileproc;
    fileproc = fopen(name, "r");
    fseek(fileproc, 0L, SEEK_END);
    *out = ftell(fileproc);
    return;
}

/**
 * @brief Функция подсчета слов
 * 
 * @param [in] name <имя файла>
 * @param [out] out <количество слов>
 *
 */

void wordsCount(char *name, int *out) {
    int counter = 0;
    char ccurrent, cprevious = ' ';
    FILE *fileproc;
    fileproc = fopen(name, "r");
    while (ccurrent != EOF) {
        ccurrent = fgetc(fileproc);
        if ((cprevious == ' ' || cprevious == '\n' || cprevious == '\t') && (ccurrent != ' ' || ccurrent != '\n' || ccurrent != '\t')) {
            counter++;
        }
        cprevious = ccurrent;
    }
    fclose(fileproc);
    *out = counter;
    return;
}

/**
 * @brief Основное тело программы
 * 
 * В случае если формат входных данных не соответсвует установленному, программа сообщит об этом. 
 * Также в случае,  если имя файла введено неверно, то программа сообщит что не может открыть файл для работы с ним.
 * Если же данные введены корректно, то программа выполнит задачу.
 * @param [in] argc количество аргументов командой строки 
 * @param [in] argv аргументы командной строоки 
 */

int WordCont(char command[], char name[]) {
    int out = -1;
    if (fopen(name, "r") == NULL) {
        printf("Cannot open the file");
    } else {
        if (strcmp(command, "-l") == 0 || strcmp(command, "--lines") == 0) {
            linesCount(name, &out);
        } else if (strcmp(command, "-c") == 0 || strcmp(command, "--bytes") == 0) {
            bytesCount(name, &out);
        } else if (strcmp(command, "-w") == 0 || strcmp(command, "--words") == 0) {
            wordsCount(name, &out);
        };
    }
    return out;
}