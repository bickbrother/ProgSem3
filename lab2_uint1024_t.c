#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "limits.h"

#define CELLSNUMBER 32

struct uint1024_t {
    unsigned int cells[CELLSNUMBER];
};

typedef struct uint1024_t uint1024_t;

bool more(uint1024_t x, uint1024_t y) {
    for (int i = CELLSNUMBER - 1; i >= 0; --i) {
        if (x.cells[i] > y.cells[i])
            return true;
        else if (y.cells[i] > x.cells[i])
            return false;
    }
    return false;
}

bool eq(uint1024_t x, uint1024_t y) {
    for (int i = 0; i < CELLSNUMBER; ++i) {
        if (x.cells[i] != y.cells[i]) {
            return false;
        }
    }
    return true;
}

uint1024_t from_uint(unsigned int x) {
    uint1024_t X = {0};
    X.cells[0] = x;
    return X;
}

uint1024_t add_op(uint1024_t x, uint1024_t y) {
    uint1024_t result = {0};
    unsigned long long sum;
    bool div = 0;
    for (int i = 0; i < CELLSNUMBER; i++) {
        sum = (unsigned long long)x.cells[i] + (unsigned long long)y.cells[i] + (unsigned long long)div;
        result.cells[i] = sum;
        if (sum > (unsigned long long)UINT_MAX) {
            div = 1;
        } else {
            div = 0;
        }
        if (sum > (unsigned long long)UINT_MAX && i == CELLSNUMBER - 1) {
            printf("\n !!! UNDEFINED BEHAVIOR !!! \n");
        }
    }
    return result;
}

uint1024_t subtr_op(uint1024_t x, uint1024_t y) {
    uint1024_t result = {0};
    bool div = 0;
    if (eq(x, y)) {
        return result;
    } else if(more(x, y)) {
        for(int i = 0; i < CELLSNUMBER; i++) {
            result.cells[i] = x.cells[i] - y.cells[i] - (unsigned)div;
            if((unsigned long long)x.cells[i] >= (unsigned long long)y.cells[i] + (unsigned long long)div) {
                div = 0;
            } else {
                div = 1;
            }
        }
    }  else {
        for(int i = 0; i < CELLSNUMBER; i++) {
            result.cells[i] = y.cells[i] - x.cells[i] - (unsigned)div;
            if((unsigned long long)y.cells[i] >= (unsigned long long)x.cells[i] + (unsigned long long)div) {
                div = 0;
            } else {
                div = 1;
            }
        }
    } 
    return result;
}

uint1024_t mult_op(uint1024_t x, uint1024_t y) {
    uint1024_t product = from_uint(0);
    if (more(x, y))
        while (!eq(y, from_uint(0))) {
            product = add_op(product, x);
            y = subtr_op(y, from_uint(1));
        }
    else
        while (!eq(x, from_uint(0))) {
            product = add_op(product, y);
            x = subtr_op(x, from_uint(1));
        }
    return product;
}

void printf_value(uint1024_t x) {
    bool flag = false;
    for (int i = 31; i >= 0; i--) {
        char cell[9] = {0};
        sprintf(cell, "%X", x.cells[i]);
        if (flag) {
            int len = strlen(cell);
            for (int j = 7; j > len; j--) {
                printf("0");
            }
            for (int j = 0; j <= len; j++) {
                printf("%c", cell[j]);
            }
        } else if (!flag && i != 0) {
            if (x.cells[i] != 0) {
                int len = strlen(cell);
                for (int j = 7; j > len; j--) {
                    printf("%c", cell[j]);
                }
                for (int j = 0; j <= len; j++) {
                    printf("%c", cell[j]);
                }
                flag = true;
                }
        } else {
            printf("%X", x.cells[0]);
        }   
    }
}

void scanf_value(uint1024_t* x) {
    char chr = '0';
    while (chr >= '0' && chr <= '9') {
        *x = mult_op(*x, from_uint(10));
        *x = add_op(*x, from_uint(chr - '0'));
        chr = getchar();
        }
    }

int main() {
    uint1024_t value1 = {0}, value2 = {0};
    printf("Enter the first value: ");
    scanf_value(&value1);
    printf("Enter the second value: ");
    scanf_value(&value2);

    printf("\n ");
    printf_value(value1);
    printf(" + ");
    printf_value(value2);
    printf(" = ");
    printf_value(add_op(value1, value2));

    printf("\n|");
    printf_value(value1);
    printf(" - ");
    printf_value(value2);
    printf("| = ");
    printf_value(subtr_op(value1, value2));

    printf("\n ");
    printf_value(value1);
    printf(" * ");
    printf_value(value2);
    printf(" = ");
    printf_value(mult_op(value1, value2));
    return 0;
}