#ifndef SHELL_H
#define SHELL_H
typedef struct{
    char user[256];
    char host[256];
    char pwd[256];
    char *pwd_current;
    char home[256];
    char prompt[1024];
} user_data;

user_data *load_user_data();
#endif
