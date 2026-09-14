#include "config.h"

void clearScreen(void)
{
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J\033[H");
#endif
}

void pauseScreen(void)
{
    s32 character;

    printf("\nPress [Enter] to return to the main menu...");
    while ((character = getchar()) != '\n' && character != EOF)
    {
        /* Discard remaining input. */
    }
}
