#ifndef DYNAMIC_PARSER_H_
#define DYNAMIC_PARSER_H_

#include <stdint.h>
#include <stdbool.h>

/* ------------------------------------------------ */
/* CONFIG                                           */
/* ------------------------------------------------ */

#define MAX_TOKENS          10

#define MAX_TOKEN_LENGTH    32

/* ------------------------------------------------ */
/* PARSED COMMAND STRUCTURE                         */
/* ------------------------------------------------ */

typedef struct
{
    char tokens[MAX_TOKENS]
               [MAX_TOKEN_LENGTH];

    uint8_t token_count;

} Parsed_Command_t;

/* ------------------------------------------------ */
/* FUNCTIONS                                        */
/* ------------------------------------------------ */

/*
 * Example:
 *
 * INPUT:
 *     POWER_SET_3300_1
 *
 * OUTPUT:
 *     tokens[0] = POWER
 *     tokens[1] = SET
 *     tokens[2] = 3300
 *     tokens[3] = 1
 */

bool dynamic_parse(

    char *input,

    Parsed_Command_t *cmd

);

#endif