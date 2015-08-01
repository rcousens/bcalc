#ifndef BINARY_CALC_COMPLETION_H
#define BINARY_CALC_COMPLETION_H

extern char *xmalloc PARAMS((size_t));
void initialize_completion();
char *command_generator(const char *text, int state);

#endif //BINARY_CALC_COMPLETION_H
