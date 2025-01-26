#ifndef CLIENT_H
# define CLIENT_H

# include <signal.h>

# include "libft.h"
# include "ft_printf.h"

void    send_message(char *message, pid_t server_pid);

#endif