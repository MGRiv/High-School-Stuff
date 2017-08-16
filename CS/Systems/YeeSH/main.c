/*******************************************************************************
 * main program for YeeSH                                                      *
 *                                                                             *
 * Authors                                                                     *
 *  Jared Beh, Michael Rivera, Yicheng Wang                                    *
 *                                                                             *
 * Description                                                                 *
 *  The main program for YeeSH, an interactive shell written for mks65         *
 *                                                                             *
 ******************************************************************************/

/* TODO
 *  parse function in parser.c
 *  trim function in parser.c
 */

/* Dev Log
 *  Project Created: 2015-11-17 11:50 - Yicheng W.
 *  main() function and prompt created: 2015-11-17: 13:40 - Yicheng W.
 *  structure determined, basic headers and TODO written: 2015-11-18: 12:31 - All
 */

/* INIT ***********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "parser.h"
#include "execute.h"
#include "shell.h"

/* MAIN ***********************************************************************/
int main() {
    user_data *current_user;
    current_user = load_user_data();
    char input[256];
    command *commands;
    int ret_val = 0;
    while (1) {
        current_user = load_user_data();
        if (ret_val) {
            printf("(%d)-", ret_val);
        }
        printf("%s", current_user->prompt);
        fgets(input, sizeof(input), stdin);
        commands = break_line(input);
        if (commands) {
            ret_val = execute(commands);
        }
        else {
            ret_val = 1;
        }
    }
    return 0;
}

/* UTILS **********************************************************************/
/* load_user_user_data: loads the user informations and user_datas
 * looks at system informations and user config to generate key data and prompt
 */
user_data *load_user_data() {
    user_data *data = (user_data *)malloc(sizeof(user_data));
    //TODO error checking
    getcwd(data->pwd, sizeof(data->pwd));
    char *tmp = data->pwd;
    while (tmp) {
        data->pwd_current = strsep(&tmp, "/");
    }
    strncpy(data->user, getenv("USER"), sizeof(data->user));
    gethostname(data->host, sizeof(data->host));
    sprintf(data->prompt, "%s@%s: %s $ ", data->user, data->host, data->pwd_current);
    return data;
}
