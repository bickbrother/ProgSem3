#include "stdio.h"
#include "string.h"
#define NUMBEROFSTRINGS 1891715

char str[391] = {0};
int times[NUMBEROFSTRINGS];

void filling(char* name) {
    FILE* filein = fopen(name, "r");
    char id[100] = {0}, request1[100] = {0}, request2[100] = {0}, request3[100] = {0};
    int day, hour, minutes, seconds, status, bytes;
    for (int i = 0; i < NUMBEROFSTRINGS; i++) {
        fgets(str, 391, filein);
        int j = 0;
        while (str[j] != '[') {
            j++;
        }
        day = (int)(str[j + 1] - '0') * 10 + (int)(str[j + 2] - '0');
        hour = (int)(str[j + 13] - '0') * 10 + (int)(str[j + 14] - '0');
        minutes = (int)(str[j + 16] - '0') * 10 + (int)(str[j + 17] - '0');
        seconds = (int)(str[j + 19] - '0') * 10 + (int)(str[j + 20] - '0');
        times[i] = (day - 1) * 86400 + hour * 3600 + minutes * 60 + seconds;
    }
}

void error5xxList(char* name) {
    int counter = 0;
    printf("Requests with errors:\n");
    FILE *filein = fopen(name, "r");
    for (int i = 0; i < NUMBEROFSTRINGS; i++) {
        char request[350] = {0};
        fgets(str, 391, filein);
        int j = 0;
        while (str[j] != '"') {
            j++;
        }
        j++;
        int k = 0;
        while (str[j] != '"') {
            request[k] = str[j];
            k++;
            j++;
        }
        if (str[j + 2] == '5') {
            counter++;
            printf("%s\n", request);
        }
    }
    printf("Number of requests with errors: %d\n", counter);
}

int binsearchStart(int key, int leftIndex, int rightIndex) {
    if (leftIndex == rightIndex) {
        return leftIndex;
    }
    int middle = (leftIndex + rightIndex) / 2;
    if (key > times[middle]) {
        binsearchStart(key, middle + 1, rightIndex);
    } else {
        binsearchStart(key, leftIndex, middle);
    }
}

int binsearchEnd(int key, int leftIndex, int rightIndex) {
    if (leftIndex == rightIndex) {
        return leftIndex;
    }
    int middle = (leftIndex + rightIndex + 1) / 2;
    if (key >= times[middle]) {
        binsearchEnd(key, middle, rightIndex);
    } else {
        binsearchEnd(key, leftIndex, middle - 1);
    }
}

void timeWindowSearch(int interval) {    
    int firstTime, lastTime, maxFirstTime, maxLastTime, maxLen = 0;
    int i = 0;
    while (i < NUMBEROFSTRINGS) {
        firstTime = times[i];
        lastTime = times[binsearchEnd(times[i] + interval, 0, NUMBEROFSTRINGS - 1)];
        if (binsearchEnd(times[i] + interval, 0, NUMBEROFSTRINGS - 1) - i > maxLen) {
            maxLen = binsearchEnd(times[i] + interval, 0, NUMBEROFSTRINGS - 1) - i;
            maxFirstTime = firstTime;
            maxLastTime = lastTime;
        }
        i = binsearchEnd(times[i], 0, NUMBEROFSTRINGS - 1) + 1;
    }
    int dayFirst = maxFirstTime / 86400 + 1;
    maxFirstTime %= 86400; 
    int dayLast = maxLastTime / 86400 + 1;
    maxLastTime %= 86400;
    int hourFirst = maxFirstTime / 3600;
    maxFirstTime %= 3600;
    int hourLast = maxLastTime / 3600;
    maxLastTime %= 3600;
    int minutesFirst = maxFirstTime / 60;
    maxFirstTime %= 60;
    int minutesLast = maxLastTime / 60;
    maxLastTime %= 60;
    int secondsFirst = maxFirstTime;
    int secondsLast = maxLastTime;
    printf("The first date of time window: %d/Jul/1995:%d:%d:%d -0400\n", dayFirst, hourFirst, minutesFirst, secondsFirst);
    printf("The last date of time window: %d/Jul/1995:%d:%d:%d -0400 \n", dayLast, hourLast, minutesLast, secondsLast);
    printf("Number of requests in this interval: %d\n", maxLen + 1);
}

int main(int argc, char *argv[]) {
    int interval;
    printf("Enter the time interval in seconds: ");
    scanf("%d", &interval);
    filling(argv[1]);
    FILE *filein = fopen("NASA_access_log_Jul95.txt", "r");
    timeWindowSearch(interval);
    char answer[4];
    printf("Do you want to see requests with errors 5xx?\n");
    scanf("%s", &answer);
    if (strcmp(answer, "YES") == 0) {
        error5xxList(argv[1]);
    }
    return 0;
}