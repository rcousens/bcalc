
#include <readline/readline.h>

#include "completion.h"
#include "command.h"


char* dupstr (char *s)
{
    char* r;

    r = xmalloc(strlen(s) + 1);
    strcpy(r, s);
    return r;
}

void initialize_completion()
{
    rl_readline_name = "bcalc";

    rl_completion_entry_function = command_generator;
}

/* Generator function for command completion.  STATE lets us know whether
   to start from scratch; without any state (i.e. STATE == 0), then we
   start at the top of the list. */
char* command_generator (const char *text, int state)
{
    static int list_index;
    static size_t len;
    char *name;

    /* If this is a new word to complete, initialize now.  This includes
       saving the length of TEXT for efficiency, and initializing the index
       variable to 0. */
    if (!state)
    {
        list_index = 0;
        len = strlen (text);
    }

    /* Return the next name which partially matches from the command list. */
    while (name = get_command(list_index))
    {
        list_index++;

        if (strncmp (name, text, len) == 0)
            return (dupstr(name));
    }

    /* If no names matched, then return NULL. */
    return ((char *)NULL);
}




