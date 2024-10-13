#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"
const int DAY_BITS = 31, MONTH_BIT_NUMBER = 5, YEAR_BIT_NUMBER = 9, MAX_LEN = 500;
const int DATE_NUMBER_BITS = 15, MAX_MONTH = 15, MAX_YEAR = 63, FIRST_BITS = 32767;
const int INDEX_FULL_DATE = 15, INDEX_CHANGE_RULE = 8, BEGIN_YEAR = 1970;
const int FIRST_PART = 7, SECOND_PART = 8, BIT_NUMBER_INT = 32;
const int IAN = 1, FEB = 2, MAR = 3, APR = 4, MAI = 5, IUN = 6, IUL = 7, AUG = 8;
const int SEP = 9, OCT = 10, NOI = 11;
TDate DateExtract(unsigned int* v) {
    TDate d;
    d.day = v[0] & DAY_BITS;
    d.month = (v[0] >> MONTH_BIT_NUMBER) & MAX_MONTH;
    d.year = (v[0] >> YEAR_BIT_NUMBER) & MAX_YEAR;
    return d;
}
unsigned int DatePack(TDate *d, unsigned int j) {
    return (d+j)->day | ((d+j)->month << MONTH_BIT_NUMBER) | ((d+j)->year << YEAR_BIT_NUMBER);
}
int ComparaCresc(const void *a, const void *b) {
    int *x = (int*)a, *y = (int*)b;
    return *x-*y;
}
void printDate(TDate *date) {
    int zi = 0, luna = 0;
    unsigned int an = 0;
    zi = date->day;
    luna = date->month;
    an = date->year+BEGIN_YEAR;
     if (luna == IAN) {
        printf("%d ianuarie %d\n", zi, an);
     } else if (luna == FEB) {
        printf("%d februarie %d\n", zi, an);
    } else if (luna == MAR) {
        printf("%d martie %d\n", zi, an);
    } else if (luna == APR) {
        printf("%d aprilie %d\n", zi, an);
    } else if (luna == MAI) {
        printf("%d mai %d\n", zi, an);
    } else if (luna == IUN) {
        printf("%d iunie %d\n", zi, an);
    } else if (luna == IUL) {
        printf("%d iulie %d\n", zi, an);
    } else if (luna == AUG) {
        printf("%d august %d\n", zi, an);
    } else if (luna == SEP) {
        printf("%d septembrie %d\n", zi, an);
    } else if (luna == OCT) {
        printf("%d octombrie %d\n", zi, an);
    } else if (luna == NOI) {
        printf("%d noiembrie %d\n", zi, an);
    } else {
        printf("%d decembrie %d\n", zi, an);
    }
}
int main() {
    unsigned int task = 0;
    scanf("%d", &task);
    if (task == FIRST_PART) {
        unsigned int N = 0, i = 0, a = 0, *v = NULL;
        TDate *d = NULL;
        scanf("%d", &N);
        v = (unsigned int*)malloc(N * sizeof(unsigned int));
        for (i = 0; i < N; i++) {
            scanf("%d", &(*(v+i)));
            a = *(v+i) & FIRST_BITS;
            *(v+i) = a;
        }
        qsort(v, N, sizeof(int), ComparaCresc);
        d = (TDate*)malloc(N * sizeof(TDate));
        for (i = 0; i < N; i++) {
            (d+i)->day = *(v+i) & DAY_BITS;
            (d+i)->month = (*(v+i) >> MONTH_BIT_NUMBER) & MAX_MONTH;
            (d+i)->year = (*(v+i) >> YEAR_BIT_NUMBER) & MAX_YEAR;
        }
        for (i = 0; i < N; i++) {
            printDate(d+i);
        }
        free(v);
        free(d);
    }
    if (task == SECOND_PART) {
        unsigned int N = 0, i = 0, number_int = 0, number_control = 0;
        unsigned int number_of_ones = 0, j = 0, p = 0, w[MAX_LEN], *v = NULL, *c = NULL, *m = NULL;
        unsigned int bit_control = 0, b = 0, aux = 0, g = 0, mask = 0;
        unsigned int pos_int_corupt = 0;
        unsigned int *int_begin = NULL, *int_end = NULL;
        TDate *d = NULL;
        TDate aux_date, *da = NULL;
        scanf("%d", &N);
        if ((N*DATE_NUMBER_BITS) % BIT_NUMBER_INT == 0) {
            number_int = (N*DATE_NUMBER_BITS)/BIT_NUMBER_INT;
        } else {
            number_int = (N*DATE_NUMBER_BITS)/BIT_NUMBER_INT + 1;
        }
        if (number_int % BIT_NUMBER_INT == 0) {
            number_control = number_int/BIT_NUMBER_INT;
        } else {
            number_control = number_int/BIT_NUMBER_INT + 1;
        }
        v = (unsigned int*)malloc(number_int * sizeof(unsigned int));
        c = (unsigned int*)malloc(number_control * sizeof(unsigned int));
        if (c == NULL) {
            printf("eroare alocare");
        }
        m = (unsigned int*)malloc((N + 3)* sizeof(unsigned int));
         if (m == NULL) {
            printf("eroare alocare");
        }
        d = (TDate*)malloc((N + 3) * sizeof(TDate));
         if (d == NULL) {
            printf("eroare alocare");
        }
        int_begin = (unsigned int*)malloc((N + 3) * sizeof(unsigned int));
        int_end = (unsigned int*)malloc((N + 3) * sizeof(unsigned int));
        for (i = 0; i < number_int; i++) {
            scanf(" %d", (v+i));
        }
        for (i = 0; i < number_control; i++) {
            scanf(" %d", &c[i]);
        }
        for (i = 0; i < number_int; i++) {
            number_of_ones = 0;
            p = 1;
            while (p) {
                if (*(v+i) & p) {
                    number_of_ones++;
                }
                p <<= 1;
            }
            bit_control = (*(c+ i/BIT_NUMBER_INT) >> (i%BIT_NUMBER_INT)) & 1;
            if (number_of_ones % 2 != bit_control) {
                b++;
                w[b-1] = i;
            }
        }
        mask = (1 << DATE_NUMBER_BITS) -1;
        for (i = 0; i < number_int; i=i+INDEX_FULL_DATE) {
            g = 0;
            for (p = i; (p < i + INDEX_CHANGE_RULE) && (p < number_int) && (j < N); p++) {
                if (p == 0) {
                    j = 0;
                    aux_date = DateExtract(v);
                    (d+j)->day = aux_date.day;
                    (d+j)->month = aux_date.month;
                    (d+j)->year = aux_date.year;
                    *(m+j) = DatePack(d, j);
                    *(int_begin + j) = 0;
                    *(int_end + j) = 0;
                    j++;
                    v[0] >>= DATE_NUMBER_BITS;
                    aux_date = DateExtract(v);
                    (d+j)->day = aux_date.day;
                    (d+j)->month = aux_date.month;
                    (d+j)->year = aux_date.year;
                    *(m+j) = DatePack(d, j);
                    *(int_begin + j) = 0;
                    *(int_end + j) = 0;
                    j++;
                    v[0] >>= DATE_NUMBER_BITS;
                    g++;
                } else {
                    aux = *(v+p) & mask;
                    aux <<= (2*g);
                    v[0] = v[0] | aux;
                    aux_date = DateExtract(v);
                    (d+j)->day = aux_date.day;
                    (d+j)->month = aux_date.month;
                    (d+j)->year = aux_date.year;
                    *(m+j) = DatePack(d, j);
                    if (p == i) {
                        *(int_begin + j) = p;
                        *(int_end + j) = p;
                    } else {
                        *(int_begin + j) = p-1;
                        *(int_end + j) = p;
                    }
                    j++;
                    *(v+p) >>= DATE_NUMBER_BITS;
                    v[0] >>= DATE_NUMBER_BITS;
                    aux = *(v+p) & mask;
                    aux <<= (2*g);
                    v[0] = v[0] | aux;
                    aux_date = DateExtract(v);
                    (d+j)->day = aux_date.day;
                    (d+j)->month = aux_date.month;
                    (d+j)->year = aux_date.year;
                    *(m+j) = DatePack(d, j);
                    *(int_begin + j) = p;
                    *(int_end + j) = p;
                    j++;
                    *(v+p) >>= DATE_NUMBER_BITS;
                    v[0] >>= DATE_NUMBER_BITS;
                    aux = *(v+p) & mask;
                    aux <<= (2*g);
                    v[0] = v[0] | aux;
                    g++;
                }
            }
            if (p == i+INDEX_CHANGE_RULE) {
                aux_date = DateExtract(v);
                (d+j)->day = aux_date.day;
                (d+j)->month = aux_date.month;
                (d+j)->year = aux_date.year;
                *(m+j) = DatePack(d, j);
                *(int_begin + j) = p-1;
                *(int_end + j) = p-1;
                j++;
                v[0] >>= DATE_NUMBER_BITS;
            }
            g = 0;
            for (p = i + INDEX_CHANGE_RULE; (p < i + INDEX_FULL_DATE) && (p < number_int) && (j < N); p++) {
                aux = *(v+p) & mask;
                aux <<= (2*g + 1);
                v[0] = v[0] | aux;
                aux_date = DateExtract(v);
                (d+j)->day = aux_date.day;
                (d+j)->month = aux_date.month;
                (d+j)->year = aux_date.year;
                *(m+j) = DatePack(d, j);
                *(int_begin + j) = p-1;
                *(int_end + j) = p;
                j++;
                *(v+p) >>= DATE_NUMBER_BITS;
                v[0] >>= DATE_NUMBER_BITS;
                aux = *(v+p) & mask;
                aux <<= (2*g + 1);
                v[0] = v[0] | aux;
                aux_date = DateExtract(v);
                (d+j)->day = aux_date.day;
                (d+j)->month = aux_date.month;
                (d+j)->year = aux_date.year;
                *(m+j) = DatePack(d, j);
                *(int_begin + j) = p;
                *(int_end + j) = p;
                j++;
                *(v+p) >>= DATE_NUMBER_BITS;
                v[0] >>= DATE_NUMBER_BITS;
                aux = *(v+p) & mask;
                aux <<= (2*g + 1);
                v[0] = v[0] | aux;
                g++;
            }
            if (p == i+DATE_NUMBER_BITS) {
                aux_date = DateExtract(v);
                (d+j)->day = aux_date.day;
                (d+j)->month = aux_date.month;
                (d+j)->year = aux_date.year;
                *(m+j) = DatePack(d, j);
                *(int_begin + j) = p-1;
                *(int_end + j) = p-1;
                j++;
                v[0] >>= DATE_NUMBER_BITS;
            }
        }
        if (b != 0) {
            for (i = 0; i < b; i++) {
                pos_int_corupt = w[i];
                for (j = 0; j < N; j++) {
                    if ((int_begin[j] == pos_int_corupt) || (int_end[j] == pos_int_corupt)) {
                        if (j == (N - 1)) {
                            N--;
                        } else {
                            for (unsigned int k = j; k < N - 1; k++) {
                                m[k] = m[k+1];
                                int_begin[k] = int_begin[k+1];
                                int_end[k] = int_end[k+1];
                            }
                            N--;
                            j--;
                        }
                    }
                }
            }
        }
        qsort(m, N, sizeof(int), ComparaCresc);
        da = (TDate*)malloc((N+3) * sizeof(TDate));
        for (i = 0; i < N; i++) {
            (da+i)->day = *(m+i) & DAY_BITS;
            (da+i)->month = (*(m+i) >> MONTH_BIT_NUMBER) & MAX_MONTH;
            (da+i)->year = (*(m+i) >> YEAR_BIT_NUMBER) & MAX_YEAR;
        }
        for (i = 0; i < N; i++) {
            printDate(&da[i]);
        }
        free(d);
        free(v);
        free(c);
        if (m) {
            free(m);
        }
        free(da);
        free(int_begin);
        free(int_end);
    }
    return 0;
}

