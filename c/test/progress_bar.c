#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

/* This datastruct represents the state of multiline progressbar UI */
struct pacman_multibar_ui {
    /* Number of active download bars that multibar UI handles. */
    size_t active_downloads_num;

    /* Specifies whether a completed progress bar need to be reordered and moved
     * to the top of the list.
     */
    bool move_completed_up;

    /* Cursor position relative to the first active progress bar,
     * e.g. 0 means the first active progress bar, active_downloads_num-1 means the last bar,
     * active_downloads_num - is the line below all progress bars.
     */
    int cursor_lineno;
};

struct pacman_multibar_ui multibar_ui = {0};

/* Moves console cursor `lines` up */
void console_cursor_move_up(unsigned int lines)
{
    printf("\x1B[%dF", lines);
}

/* Moves console cursor `lines` down */
void console_cursor_move_down(unsigned int lines)
{
    printf("\x1B[%dE", lines);
}

/* Erases line from the current cursor position till the end of the line */
void console_erase_line(void)
{
    printf("\x1B[K");
}

/* Goto the line that corresponds to num-th active download */
void console_cursor_goto_bar(int num)
{
    if(num > multibar_ui.cursor_lineno) {
        console_cursor_move_down(num - multibar_ui.cursor_lineno);
    } else if(num < multibar_ui.cursor_lineno) {
        console_cursor_move_up(multibar_ui.cursor_lineno - num);
    }
    multibar_ui.cursor_lineno = num;
}

/* Goto the line *after* the last active progress bar */
void console_cursor_move_end(void)
{
    console_cursor_goto_bar(multibar_ui.active_downloads_num);
}

int main(int argc, char *argv[])
{
    multibar_ui.active_downloads_num = 4;

    /* draw 5 progress bars */
    printf("draw bar 0\n");
    multibar_ui.cursor_lineno++;
    printf("draw bar 1\n");
    multibar_ui.cursor_lineno++;
    printf("draw bar 2\n");
    multibar_ui.cursor_lineno++;
    printf("draw bar 3\n");
    multibar_ui.cursor_lineno++;
    printf("draw bar total\n");
    multibar_ui.cursor_lineno++;
    fflush(stdout);
    sleep(1);

    /* goto bar 3 */
    console_cursor_goto_bar(3);
    printf("goto bar 3");
    fflush(stdout);
    sleep(1);

    /* goto bar 1 */
    console_cursor_goto_bar(1);
    printf("goto bar 1");
    fflush(stdout);
    sleep(1);

    /* remove bar 0, and go to bar 1 */
    multibar_ui.cursor_lineno--;
    multibar_ui.active_downloads_num--;
    console_cursor_goto_bar(1);
    printf("[remove bar 0] goto bar 1 (old bar 2)");
    fflush(stdout);
    sleep(1);

    console_cursor_goto_bar(0);
    printf("[remove bar 0] goto bar 0 (old bar 1)");
    fflush(stdout);
    sleep(1);

    /* goto bar total */
    console_cursor_move_end();
    printf("[remove bar 0] goto bar total");
    fflush(stdout);
    sleep(1);

    printf("\n");

    return 0;
}

