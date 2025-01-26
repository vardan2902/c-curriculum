#ifndef SERVER_H
# define SERVER_H

# define MAX_MSG_LENGTH 1024

# include <sys/types.h>
# include <signal.h>

# include "libft.h"
# include "ft_printf.h"

typedef struct sigaction    t_sigaction;

typedef struct s_server
{
    char    current_char;
    int     bit_index;
    char    message[MAX_MSG_LENGTH];
    int     msg_index;
} t_server;

void set_bit_in_char(int sig, t_server *state);
void append_char_to_message(t_server *state);
void print_message(t_server *state, int pid);

#endif