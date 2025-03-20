// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

// This code is written for you to simplify the process of changing the colours of
// your console text. The code in here is beyond the scope of this course.

// *** DO NOT EDIT THIS FILE ***

#include <stdio.h>
#include "colours.h"


#if defined (__APPLE__) || defined (__linux__)
    #include <termios.h>
    #include <unistd.h>
    static struct termios tty_opts_backup;
    /* Initialize new terminal i/o settings */
    static void initTermios(void) {
        struct termios tty_opts_raw;

        // don't try to configure a terminal driver if it's not a terminal
        if (!isatty(STDIN_FILENO)) {
            //printf("Error: stdin is not a TTY\n");
            return;
        }
//        printf("stdin is %s\n", ttyname(STDIN_FILENO));

        // Back up current TTY settings
        tcgetattr(STDIN_FILENO, &tty_opts_backup);
        tcgetattr(STDIN_FILENO, &tty_opts_raw);

        // Change TTY settings to raw mode
        tty_opts_raw.c_iflag &= ~(IMAXBEL|IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
        tty_opts_raw.c_oflag &= ~OPOST;
        tty_opts_raw.c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
        tty_opts_raw.c_cflag &= ~(CSIZE|PARENB);
        tty_opts_raw.c_cflag |= CS8;

        tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_raw);
    }

    /* Restore old terminal i/o settings */
    static void resetTermios(void) {
        tcsetattr(STDIN_FILENO, TCSANOW, &tty_opts_backup);
    }

    /* Read 1 character */
    char getch(void) {
        char ch;
        initTermios();
        ch = (char)getchar();
        resetTermios();
        return ch;
    }

#endif

/**
 * Change the colour of the following text!
 * Everyone, even Windows, supports ANSI colours now.
 * @param colour a colour as defined in colours.h
 * @return 0 on success, 1 on failure
 */
int change_text_colour(int colour) {
    switch (colour) {
        case BLUE:   printf("\x1b[34m"); break;
        case YELLOW: printf("\x1b[33m"); break;
        case PINK:   printf("\x1b[35m"); break;
        case WHITE:  printf("\x1b[0m"); break;
        default:     return 1;
    }
    return 0;
}