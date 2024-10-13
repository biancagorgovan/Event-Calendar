#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "timelib.h"
const int IANT = 1, FEBT = 2, MART = 3, APRT = 4, MAIT = 5, IUNT = 6, IULT = 7, AUGT = 8;
const int SEPT = 9, OCTT = 10, NOIT = 11, SEC_IN_A_DAY = 86400, SEC_IN_A_MIN = 60;
const int SEC_IN_A_HOUR = 3600, DAYS_YEAR = 365, DAYS_LEAP_YEAR = 366, DAYS_LONG_MONTH = 31;
const int DAYS_SHORT_MONTH = 30, DAYS_FEB_LEAP = 29, DAYS_FEB = 28, HOURS_PER_DAY = 24, BEGIN_YEART = 1970;
const int CRIT_LEAP_S = 400, CRIT_LEAP_I = 100, MAX_LENT = 5;
TTime convertUnixTimestampToTime(unsigned int timestamp) {
    TTime result;
    result.hour = (unsigned char)((timestamp % SEC_IN_A_DAY) / SEC_IN_A_HOUR);
    result.min = (unsigned char)((timestamp % SEC_IN_A_HOUR) / SEC_IN_A_MIN);
    result.sec = (unsigned char)(timestamp % SEC_IN_A_MIN);
    return result;
}

TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp) {
    TDate result;
    unsigned int month = 1, days_number_start_year = 0, c = 0;
    // var month functioneaza ca un contor pt luna timestampului
    // var days_number_start_year salveaza initial zilele trecute de la 1 ian
    days_number_start_year = (timestamp % (DAYS_YEAR*HOURS_PER_DAY*SEC_IN_A_HOUR)) / (SEC_IN_A_HOUR*HOURS_PER_DAY);
    while ((days_number_start_year >= DAYS_FEB) && (c == 0)) {
        if (month == 2) {
            days_number_start_year -= DAYS_FEB;
            month++;
        } else if (days_number_start_year >= DAYS_LONG_MONTH) {
            if ((month % 2 == 1 && month < AUGT) || (month % 2 == 0 && month >= AUGT)) {
                days_number_start_year -= DAYS_LONG_MONTH;
                month++;
            } else if ((month % 2 == 0 && month < AUGT) || (month % 2 == 1 && month > AUGT)) {
                days_number_start_year -= DAYS_SHORT_MONTH;
                month++;
            } else {
                c = 1;
            }
        } else if (days_number_start_year >= DAYS_SHORT_MONTH) {
            if ((month % 2 == 0 && month < AUGT) || (month % 2 == 1 && month > AUGT)) {
                days_number_start_year -= DAYS_SHORT_MONTH;
                month++;
            } else {
                c = 1;
            }
        } else {
            c = 1;
        }
    }
    result.day = (unsigned char)(1 + days_number_start_year);
    result.month = (unsigned char)month;
    result.year = BEGIN_YEART + (timestamp / (DAYS_YEAR*HOURS_PER_DAY*SEC_IN_A_HOUR));
    return result;
}

TDate convertUnixTimestampToDate(unsigned int timestamp) {
    TDate result;
    unsigned int  days_number = 0, month = 1, days_feb = 0, c = 0, control = 0;
    unsigned int year = BEGIN_YEART;
    days_number = timestamp / (SEC_IN_A_HOUR*HOURS_PER_DAY);
    while ((days_number >= DAYS_YEAR) && (control == 0)) {
        if (year % 4 == 0) {
            if (year % CRIT_LEAP_I != 0) {
                if (days_number >= DAYS_LEAP_YEAR) {
                    days_number -= DAYS_LEAP_YEAR;
                    year++;
                } else {
                    control = 1;
                }
            } else if (year % CRIT_LEAP_S == 0) {
                if (days_number >= DAYS_LEAP_YEAR) {
                    days_number -= DAYS_LEAP_YEAR;
                    year++;
                } else {
                    control = 1;
                }
            } else {
                days_number -= DAYS_YEAR;
                year++;
            }
        } else {
            days_number -= DAYS_YEAR;
            year++;
        }
    }
    if (year % 4 == 0) {
        if (year % CRIT_LEAP_I != 0 || year % CRIT_LEAP_S == 0) {
            days_feb = DAYS_FEB_LEAP;
        }
    } else {
        days_feb = DAYS_FEB;
    }
    while ((days_number >= DAYS_FEB) && (c == 0)) {
        if (month == 2) {
            days_number -= days_feb;
            month++;
        } else if (days_number >= DAYS_LONG_MONTH) {
            if ((month % 2 == 1 && month < AUGT) || (month % 2 == 0 && month >= AUGT)) {
                days_number -= DAYS_LONG_MONTH;
                month++;
            } else if ((month % 2 == 0 && month < AUGT) || (month % 2 == 1 && month > AUGT)) {
                days_number -= DAYS_SHORT_MONTH;
                month++;
            } else {
                c = 1;
            }
        } else if (days_number >= DAYS_SHORT_MONTH) {
            if ((month % 2 == 0 && month < AUGT) || (month % 2 == 1 && month > AUGT)) {
                days_number -= DAYS_SHORT_MONTH;
                month++;
            } else {
                c = 1;
            }
        } else {
            c = 1;
        }
    }
    result.day = (unsigned char)(1 + days_number);
    result.month = (unsigned char)month;
    result.year = year;
    return result;
}

TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index) {
    TDateTimeTZ result;
    timestamp += (timezones + timezone_index)->utc_hour_difference*SEC_IN_A_HOUR;
    result.date = convertUnixTimestampToDate(timestamp);
    result.time = convertUnixTimestampToTime(timestamp);
    result.tz = timezones + timezone_index;
    return result;
}

unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ datetimetz) {
    unsigned int timestamp = 0;
    int i = 0;
    timestamp += datetimetz.time.sec;
    timestamp += datetimetz.time.min*SEC_IN_A_MIN;
    timestamp += datetimetz.time.hour*SEC_IN_A_HOUR;
    timestamp -= (datetimetz.tz->utc_hour_difference)*SEC_IN_A_HOUR;
    timestamp += (datetimetz.date.day - 1)*HOURS_PER_DAY*SEC_IN_A_HOUR;
    for (i = 1; i < datetimetz.date.month; i++) {
        if (i == 2) {
            if (datetimetz.date.year % 4 == 0) {
                if (datetimetz.date.year % CRIT_LEAP_I != 0 || datetimetz.date.year % CRIT_LEAP_S == 0) {
                    timestamp += DAYS_FEB_LEAP*HOURS_PER_DAY*SEC_IN_A_HOUR;
                }
            } else {
                timestamp += DAYS_FEB*HOURS_PER_DAY*SEC_IN_A_HOUR;
            }
        } else if ((i % 2 == 1 && i < AUGT) || (i % 2 == 0 && i >= AUGT)) {
            timestamp += DAYS_LONG_MONTH*HOURS_PER_DAY*SEC_IN_A_HOUR;
        } else {
            timestamp += DAYS_SHORT_MONTH*HOURS_PER_DAY*SEC_IN_A_HOUR;
        }
    }
    for (i = BEGIN_YEART; i < datetimetz.date.year; i++) {
        if (i % 4 == 0) {
            if (i % CRIT_LEAP_I != 0 || i % CRIT_LEAP_S == 0) {
                timestamp += DAYS_LEAP_YEAR*HOURS_PER_DAY*SEC_IN_A_HOUR;
            }
        } else {
            timestamp += DAYS_YEAR*HOURS_PER_DAY*SEC_IN_A_HOUR;
        }
    }
    return timestamp;
}

void printDateTimeTZ(TDateTimeTZ datetimetz) {
    unsigned char zi = 0, luna = 0, min = 0, sec = 0, ora = 0;
    signed char difora = 0;
    unsigned int an = 0;
    char s[MAX_LENT];
    zi = datetimetz.date.day;
    luna = datetimetz.date.month;
    an = datetimetz.date.year;
    ora = datetimetz.time.hour;
    min = datetimetz.time.min;
    sec = datetimetz.time.sec;
    difora = datetimetz.tz->utc_hour_difference;
    snprintf(s, sizeof(s), "%s", datetimetz.tz->name);
     if (datetimetz.date.month == IANT) {
        printf("%02hhu ianuarie %u, %02hhu:%02hhu:%02hhu %s (UTC%+hhd)\n", zi, an, ora, min, sec, s, difora);
    } else if (luna == FEBT) {
        printf("%02hhu februarie %u, %02hhu:%02hhu:%02hhu %s (UTC%+hhd)\n", zi, an, ora, min, sec, s, difora);
    } else if (luna == MART) {
        printf("%02hhu martie %u, %02hhu:%02hhu:%02hhu %s (UTC%+hhd)\n", zi, an, ora, min, sec, s, difora);
    } else if (luna == APRT) {
        printf("%02hhu aprilie %u, %02hhu:%02hhu:%02hhu %s (UTC%+hhd)\n", zi, an, ora, min, sec, s, difora);
    } else if (luna == MAIT) {
        printf("%02hhu mai %u, %02hhu:%02hhu:%02hhu %s (UTC%+hhd)\n", zi, an, ora, min, sec, s, difora);
    } else if (luna == IUNT) {
        printf("%02hhu iunie %u, %02hhu:%02hhu:%02hhu %s (UTC%+hhd)\n", zi, an, ora, min, sec, s, difora);
    } else if (luna == IULT) {
        printf("%02hhu iulie %u, %02hhu:%02hhu:%02hhu %s (UTC%+hhd)\n", zi, an, ora, min, sec, s, difora);
    } else if (luna == AUGT) {
        printf("%02hhu august %u, %02hhu:%02hhu:%02hhu %s (UTC%+hhd)\n", zi, an, ora, min, sec, s, difora);
    } else if (luna == SEPT) {
        printf("%02hhu septembrie %u, %02hhu:%02hhu:%02hhu %s (UTC%+hhd)\n", zi, an, ora, min, sec, s, difora);
    } else if (luna == OCTT) {
        printf("%02hhu octombrie %u, %02hhu:%02hhu:%02hhu %s (UTC%+hhd)\n", zi, an, ora, min, sec, s, difora);
    } else if (luna == NOIT) {
        printf("%02hhu noiembrie %u, %02hhu:%02hhu:%02hhu %s (UTC%+hhd)\n", zi, an, ora, min, sec, s, difora);
    } else {
        printf("%02hhu decembrie %u, %02hhu:%02hhu:%02hhu %s (UTC%+hhd)\n", zi, an, ora, min, sec, s, difora);
    }
}
