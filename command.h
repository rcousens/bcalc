//
// Created by ross on 1/08/15.
//

#ifndef BINARY_CALC_COMMAND_H
#define BINARY_CALC_COMMAND_H

#include <stdio.h>
#include <unistd.h>

/* The names of functions that actually do the manipulation. */
int com_convert(char *);
int com_sum(char *);
int com_sub(char *);
int com_help(char *);
int com_quit(char *);
int com_mul(char *);
int com_base(char *);

static void print_result(char, char *, char *, char *);

/* A structure which contains information on the commands this program
   can understand. */

typedef struct {
    char *name;			    /* User printable name of the function. */
    int (*func)(char *);    /* Function to call to do the job. */
    char *doc;			    /* Documentation for this function.  */
} COMMAND;


COMMAND* find_command(char *);
char* get_command(int);
int execute_line(char *line);

#define whitespace(c) (((c) == ' ') || ((c) == '\t'))

#endif //BINARY_CALC_COMMAND_H
