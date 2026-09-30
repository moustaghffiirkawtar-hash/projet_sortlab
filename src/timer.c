#include <windows.h>

#include "../include/timer.h"


/* ==============================
   HIGH-RESOLUTION TIMER
   ============================== */

double get_time_seconds(void) {

    static LARGE_INTEGER frequency;

    LARGE_INTEGER counter;


    /* ==============================
       INITIALIZE FREQUENCY
       ============================== */

    if (frequency.QuadPart == 0) {

        QueryPerformanceFrequency(
            &frequency
        );
    }


    /* ==============================
       READ CURRENT COUNTER
       ============================== */

    QueryPerformanceCounter(
        &counter
    );


    /* ==============================
       CONVERT TO SECONDS
       ============================== */

    return (double)counter.QuadPart
           / (double)frequency.QuadPart;
}