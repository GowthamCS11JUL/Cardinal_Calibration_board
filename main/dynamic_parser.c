#include <headers.h>

/* ------------------------------------------------ */
/* PARSE COMMAND                                    */
/* ------------------------------------------------ */

bool dynamic_parse(

    char *input,

    Parsed_Command_t *cmd

)
{
    char *token;

    uint8_t index = 0;

    /* -------------------------------------------- */
    /* CLEAR STRUCT                                 */
    /* -------------------------------------------- */

    memset(

        cmd,

        0,

        sizeof(Parsed_Command_t)

    );

    /* -------------------------------------------- */
    /* FIRST TOKEN                                  */
    /* -------------------------------------------- */

    token = strtok(input, "_");

    while((token != NULL) &&

          (index < MAX_TOKENS))
    {
        strncpy(

            cmd->tokens[index],

            token,

            MAX_TOKEN_LENGTH - 1

        );

        index++;

        token = strtok(NULL, "_");
    }

    cmd->token_count = index;

    /* -------------------------------------------- */
    /* NO TOKENS                                    */
    /* -------------------------------------------- */

    if(index == 0)
    {
        return false;
    }

    return true;
}

