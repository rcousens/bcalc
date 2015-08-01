

#include <string.h>
#include <stdlib.h>
#include "command.h"

COMMAND commands[] = {
        { "convert", com_convert, "Convert decimal to current base" },
        { "sum", com_sum, "Sum two arguments" },
        { "mul", com_mul, "Multiple two arguments"},
        { "sub", com_sub, "Subtract two arguments"},
        { "help", com_help, "Display this text" },
        { "base", com_base, "Change base for calculations, default is 2"},
        { "quit", com_quit, "Quit using bcalc" },
        { (char *)NULL, (int (*)(char *))NULL, (char *)NULL }
};

int base = 2;
char answer[65];
char operand1[65];
char operand2[65];

char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

COMMAND* find_command (char *name)
{
    register int i;

    for (i = 0; commands[i].name; i++)
        if (strcmp (name, commands[i].name) == 0)
            return (&commands[i]);

    return ((COMMAND*)NULL);
}

int execute_line (char *line)
{
    register int i;
    COMMAND *command;
    char *word;

    /* Isolate the command word. */
    i = 0;
    while (line[i] && whitespace (line[i]))
        i++;
    word = line + i;

    while (line[i] && !whitespace (line[i]))
        i++;

    if (line[i])
        line[i++] = '\0';

    command = find_command (word);

    if (!command)
    {
        fprintf (stderr, "%s: No such command for bcalc.\n", word);
        return (-1);
    }

    /* Get argument to command, if any. */
    while (whitespace (line[i]))
        i++;

    word = line + i;

    /* Call the function. */
    return ((*(command->func)) (word));
}

char* get_command(int list_index)
{
    return commands[list_index].name;
}

int com_base(char* arg)
{
    if (!arg)
        arg = "";

    char *operand;

    operand = strtok(arg, " \t");

    if (operand) {
        base = atoi(operand);
    }

    return 1;
}

int com_convert (char* arg)
{
    if (!arg)
        arg = "";

    char *operand;
    char buffer[65];

    operand = strtok(arg, " \t");

    if (operand) {
        printf("%s\n", itoa(atoi(operand), buffer, base));
    }

    return 1;
}

int com_sum (char* arg)
{
    if (!arg)
        arg = "";
    int operands[2];

    char *operand;
    operand = strtok(arg, " ");

    if (operand) {
        operands[0] = atoi(operand);
    }

    operand = strtok(NULL, " ");

    if (operand) {
        operands[1] = atoi(operand);
    }

    print_result('+', itoa(operands[0], operand1, base), itoa(operands[1], operand2, base), itoa((operands[0] + operands[1]), answer, base));

    return 1;
}

int com_mul (char* arg)
{
    if (!arg)
        arg = "";
    int operands[2];

    char *operand;
    operand = strtok(arg, " ");

    if (operand) {
        operands[0] = atoi(operand);
    }

    operand = strtok(NULL, " ");

    if (operand) {
        operands[1] = atoi(operand);
    }

    print_result('*', itoa(operands[0], operand1, base), itoa(operands[1], operand2, base), itoa((operands[0] * operands[1]), answer, base));

    return 1;
}

int com_sub(char* arg)
{
    if (!arg)
        arg = "";
    int operands[2];

    char *operand;
    operand = strtok(arg, " ");

    if (operand) {
        operands[0] = atoi(operand);
    }

    operand = strtok(NULL, " ");

    if (operand) {
        operands[1] = atoi(operand);
    }

    print_result('-', itoa(operands[0], operand1, base), itoa(operands[1], operand2, base), itoa((operands[0] - operands[1]), answer, base));
    return 1;
}

int com_help (char* arg)
{
    register int i;
    int printed = 0;

    for (i = 0; commands[i].name; i++)
    {
        if (!*arg || (strcmp (arg, commands[i].name) == 0))
        {
            printf ("%-10s\t%s.\n", commands[i].name, commands[i].doc);
            printed++;
        }
    }

    if (!printed)
    {
        printf ("No commands match `%s'.  Possibilties are:\n", arg);

        for (i = 0; commands[i].name; i++)
        {
            /* Print in six columns. */
            if (printed == 6)
            {
                printed = 0;
                printf ("\n");
            }

            printf ("%s ", commands[i].name);
            printed++;
        }

        if (printed)
            printf ("\n");
    }
    return 1;
}

int com_quit (char* arg)
{
    return 0;
}

static void print_result(char sign, char* operand1, char* operand2, char* result)
{
    printf("%32s\n%32s %c\n%.*s\n%32s\n", operand1, operand2, sign, 32, "================================", result);
}