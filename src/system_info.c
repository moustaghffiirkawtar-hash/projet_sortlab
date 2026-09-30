#include <stdio.h>
#include <windows.h>

#include "../include/system_info.h"


/* ============================================================
   DISPLAY SYSTEM INFORMATION
   ============================================================ */

void display_system_info(void)
{
    SYSTEM_INFO system_info;

    MEMORYSTATUSEX memory_status;

    ULARGE_INTEGER free_bytes;
    ULARGE_INTEGER total_bytes;
    ULARGE_INTEGER total_free_bytes;


    /*
       ========================================================
       GET PROCESSOR INFORMATION
       ========================================================
    */

    GetSystemInfo(&system_info);


    /*
       ========================================================
       GET MEMORY INFORMATION
       ========================================================
    */

    memory_status.dwLength =
        sizeof(memory_status);

    GlobalMemoryStatusEx(
        &memory_status
    );


    /*
       ========================================================
       GET STORAGE INFORMATION
       ========================================================
    */

    if (
        !GetDiskFreeSpaceExA(
            "C:\\",
            &free_bytes,
            &total_bytes,
            &total_free_bytes
        )
    ) {

        free_bytes.QuadPart = 0;

        total_bytes.QuadPart = 0;

        total_free_bytes.QuadPart = 0;
    }


    /*
       ========================================================
       HEADER
       ========================================================
    */

    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "          SORTLAB SYSTEM INFO           \n"
    );

    printf(
        "========================================\n\n"
    );


    /*
       ========================================================
       OPERATING SYSTEM
       ========================================================
    */

    printf(
        "Operating System\n"
    );

    printf(
        "----------------------------------------\n"
    );

    printf(
        "Platform        : Windows\n"
    );


    /*
       ========================================================
       PROCESSOR
       ========================================================
    */

    printf("\n");

    printf(
        "Processor\n"
    );

    printf(
        "----------------------------------------\n"
    );

    printf(
        "CPU Cores       : %lu\n",
        system_info.dwNumberOfProcessors
    );


    printf(
        "Architecture    : "
    );


    switch (
        system_info.wProcessorArchitecture
    ) {

        case PROCESSOR_ARCHITECTURE_AMD64:

            printf(
                "x64 (AMD64)\n"
            );

            break;


        case PROCESSOR_ARCHITECTURE_ARM64:

            printf(
                "ARM64\n"
            );

            break;


        case PROCESSOR_ARCHITECTURE_INTEL:

            printf(
                "x86 (32-bit)\n"
            );

            break;


        default:

            printf(
                "Unknown\n"
            );

            break;
    }


    /*
       ========================================================
       MEMORY
       ========================================================
    */

    printf("\n");

    printf(
        "Memory\n"
    );

    printf(
        "----------------------------------------\n"
    );

    printf(
        "Total RAM       : %.2f GB\n",
        (double) memory_status.ullTotalPhys
        / (1024.0 * 1024.0 * 1024.0)
    );


    printf(
        "Available RAM   : %.2f GB\n",
        (double) memory_status.ullAvailPhys
        / (1024.0 * 1024.0 * 1024.0)
    );


    /*
       ========================================================
       STORAGE
       ========================================================
    */

    printf("\n");

    printf(
        "Storage - C:\n"
    );

    printf(
        "----------------------------------------\n"
    );


    if (total_bytes.QuadPart > 0) {

        printf(
            "Total Space     : %.2f GB\n",
            (double) total_bytes.QuadPart
            / (1024.0 * 1024.0 * 1024.0)
        );


        printf(
            "Free Space      : %.2f GB\n",
            (double) free_bytes.QuadPart
            / (1024.0 * 1024.0 * 1024.0)
        );

    }

    else {

        printf(
            "Storage         : Unable to detect\n"
        );
    }


    /*
       ========================================================
       INPUT PERIPHERALS
       ========================================================
    */

    printf("\n");

    printf(
        "Input Peripherals\n"
    );

    printf(
        "----------------------------------------\n"
    );


    /*
       GetSystemMetrics provides a basic indication
       that the system has a keyboard and mouse.
    */

    if (
        GetSystemMetrics(SM_MOUSEPRESENT)
    ) {

        printf(
            "Mouse           : Detected\n"
        );

    }

    else {

        printf(
            "Mouse           : Not detected\n"
        );
    }


    /*
       Windows desktop systems normally have
       keyboard input available.

       We display it explicitly as a system input
       peripheral.
    */

    printf(
        "Keyboard        : Available\n"
    );


    /*
       ========================================================
       FOOTER
       ========================================================
    */

    printf("\n");

    printf(
        "========================================\n"
    );

    printf(
        "       SYSTEM INFORMATION COMPLETE     \n"
    );

    printf(
        "========================================\n"
    );
}