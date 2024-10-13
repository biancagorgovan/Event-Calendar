#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "timelib.h"
int const SEC_IN_HOUR = 3600;
#define LENGHT 10
#define LUNG 5
#define MAX 1000
typedef struct {
    unsigned int begining_unixcode;
    unsigned int ending_unixcode;
} TPosibility;
typedef struct {
    unsigned int F;
    unsigned int duration;
} TEvent;
typedef struct {
    TDateTimeTZ data;
    int durata;
    unsigned int unix_code_begin;
    unsigned int unix_code_end;
} TInterval;
typedef struct {
    char nume[LENGHT];
    char tzname[LUNG];
    int K;
    TInterval free_interval[MAX];
} TPerson;
int Compare(const void *a, const void *b) {
    TPosibility *p1 = (TPosibility *)a;
    TPosibility *p2 = (TPosibility *)b;
    if (p1->begining_unixcode < p2->begining_unixcode) {
        return -1;
    } else if (p1->begining_unixcode > p2->begining_unixcode) {
        return 1;
    } else {
        return 0;
    }
}
int comparePeople(const void *a, const void *b) {
    TPerson *p1 = (TPerson *)a;
    TPerson *p2 = (TPerson *)b;
    return strcmp(p1->nume, p2->nume);
}
int main() {
    unsigned int T = 0, i = 0, P = 0, j = 0, l = 0, nr_pos = 0, dur = 0, contor_pers = 0, found = 0, timestamp_ev = 0;
    unsigned int timestamp_evend = 0, gasit = 0, faraev = 0;
    TEvent event;
    TTimezone *tz = NULL;
    scanf("%d", &T);
    tz = (TTimezone *)calloc(T, sizeof(TTimezone));
    for (i = 0; i < T; i++) {
        scanf("%s%hhd", tz[i].name, &tz[i].utc_hour_difference);
    }
    scanf("%d", &P);
    TPerson *persoane = NULL;
    persoane = (TPerson *)calloc(P, sizeof(TPerson));
    for (i = 0; i < P; i++) {
        scanf("%s%s%d", (persoane+i)->nume, (persoane+i)->tzname, &(persoane+i)->K);
        for (j = 0; j < (persoane+i)->K; j++) {
            scanf("%u", &(persoane+i)->free_interval[j].data.date.year);
            scanf("%hhu", &(persoane+i)->free_interval[j].data.date.month);
            scanf("%hhu", &(persoane+i)->free_interval[j].data.date.day);
            scanf("%hhu", &(persoane+i)->free_interval[j].data.time.hour);
            scanf("%d", &(persoane+i)->free_interval[j].durata);
            (persoane+i)->free_interval[j].data.time.min = 0;
            (persoane+i)->free_interval[j].data.time.sec = 0;
            for (l = 0; l < T; l++) {
                if (strcmp((tz+l)->name, (persoane+i)->tzname) == 0) {
                    (persoane+i)->free_interval[j].data.tz = (tz+l);
                }
            }
            TDateTimeTZ data_aux;
            data_aux = (persoane+i)->free_interval[j].data;
            (persoane+i)->free_interval[j].unix_code_begin = convertDateTimeTZToUnixTimestamp(data_aux);
            unsigned int codeb = 0;
            codeb = (persoane+i)->free_interval[j].unix_code_begin;
            (persoane+i)->free_interval[j].unix_code_end = codeb + (persoane+i)->free_interval[j].durata*SEC_IN_HOUR;
        }
    }
    scanf("%u%u", &event.F, &event.duration);
    for (i = 0; i < P; i++) {
        if ((persoane+i)->K != 0) {
            for (j = 0; j < ((persoane+i)->K - 1); j++) {
                if ((persoane+i)->free_interval[j].unix_code_end == (persoane+i)->free_interval[j+1].unix_code_begin) {
                    (persoane+i)->free_interval[j].durata += (persoane+i)->free_interval[j+1].durata;
                    (persoane+i)->free_interval[j].unix_code_end = (persoane+i)->free_interval[j+1].unix_code_end;
                    for (l = (j + 1); l < ((persoane+i)->K - 1); l++) {
                        (persoane+i)->free_interval[l] = (persoane+i)->free_interval[l+1];
                    }
                    (persoane+i)->K--;
                    j--;
                }
            }
        }
    }
    TPosibility *p = NULL;
    nr_pos = 0;
    p = (TPosibility *)calloc(MAX, sizeof(TPosibility));
    for (i = 0; i < P; i++) {
        for (j = 0; j < (persoane+i)->K; j++) {
            if ((persoane+i)->free_interval[j].durata >= event.duration) {
                dur = (persoane+i)->free_interval[j].durata;
                l = 0;
                faraev = 1;
                unsigned int codeunixb = (persoane+i)->free_interval[j].unix_code_begin;
                while (dur >= event.duration) {
                    p[nr_pos].begining_unixcode = codeunixb + l*event.duration*SEC_IN_HOUR;
                    p[nr_pos].ending_unixcode = p[nr_pos].begining_unixcode + event.duration*SEC_IN_HOUR;
                    l++;
                    dur -= event.duration;
                    nr_pos++;
                }
            }
        }
    }
    if (faraev == 0) {
        printf("imposibil\n");
        free(tz);
        free(persoane);
        free(p);
    } else {
        qsort(p, nr_pos, sizeof(TPosibility), Compare);
        for (i = 0; (i < nr_pos) && (found == 0); i++) {
            contor_pers = 0;
            for (j = 0; j < P; j++) {
                for (l = 0; l < (persoane+j)->K; l++) {
                    unsigned int codeunixb = (persoane+j)->free_interval[l].unix_code_begin;
                    unsigned int codeunixe = (persoane+j)->free_interval[l].unix_code_end;
                    if ((codeunixb <= (p+i)->begining_unixcode) && (codeunixe >= (p+i)->ending_unixcode)) {
                        contor_pers++;
                    }
                }
            }
            if (contor_pers >= event.F) {
                found = 1;
                timestamp_ev = p[i].begining_unixcode;
                timestamp_evend = timestamp_ev + SEC_IN_HOUR*event.duration;
            }
        }
        if (found == 0) {
            printf("imposibil\n");
        } else {
            qsort(persoane, P, sizeof(TPerson), comparePeople);
            for (i = 0; i < P; i++) {
                gasit = 0;
                for (j = 0; (j < (persoane+i)->K) && (gasit == 0); j++) {
                    unsigned int codeunixb = (persoane+i)->free_interval[j].unix_code_begin;
                    unsigned int codeunixe = (persoane+i)->free_interval[j].unix_code_end;
                    if ((codeunixb <= timestamp_ev) && (codeunixe >= timestamp_evend)) {
                        gasit = 1;
                    }
                }
                printf("%s: ", (persoane+i)->nume);
                if (gasit == 0) {
                    printf("invalid\n");
                } else {
                    TDateTimeTZ datep;
                    TDate convert;
                    TTime timp;
                    unsigned int timestamptemp = 0;
                    for (l = 0; l < T; l++) {
                        if (strcmp((tz+l)->name, (persoane+i)->tzname) == 0) {
                            datep.tz = (tz+l);
                            timestamptemp = timestamp_ev + SEC_IN_HOUR*(tz+l)->utc_hour_difference;
                        }
                    }
                    convert = convertUnixTimestampToDate(timestamptemp);
                    timp = convertUnixTimestampToTime(timestamptemp);
                    datep.date = convert;
                    datep.time = timp;
                    printDateTimeTZ(datep);
                }
            }
        }
        free(tz);
        free(persoane);
        free(p);
        return 0;
    }
}
