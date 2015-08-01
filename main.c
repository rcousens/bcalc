#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <unistd.h>

#include <sys/select.h>

#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "command.h"
#include "completion.h"

static void cb_linehandler (char *);

int running;

const char* prompt = "> ";

void stop()
{
    running = 0;
    rl_callback_handler_remove();
}


static void cb_linehandler(char* line)
{
    if (line == NULL)
    {
        stop();
    }
    else
    {
        if (*line) {
            add_history(line);
            if (!execute_line(line))
                stop();
        }
        free(line);
    }
}


int main (int c, char** v)
{
    fd_set fds;
    int r;

    rl_callback_handler_install (prompt, cb_linehandler);


    initialize_completion();

    running = 1;
    while (running)
    {
        FD_ZERO (&fds);
        FD_SET (fileno(rl_instream), &fds);

        r = select(FD_SETSIZE, &fds, NULL, NULL, NULL);
        if (r < 0)
        {
            perror ("rltest: select");
            stop();
            break;
        }

        if (FD_ISSET (fileno (rl_instream), &fds))
            rl_callback_read_char();
    }

    return 0;
}