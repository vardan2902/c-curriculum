#include "server.h"

t_server g_server_state = {0, 0, {0}, 0};

void append_bit(int sig, siginfo_t *info, void *context)
{
    t_server *state;
    
    (void)context;
    state = &g_server_state;
    set_bit_in_char(sig, state);
    state->bit_index++;
    if (state->bit_index == 8)
    {
        append_char_to_message(state);
        state->current_char = 0;
        state->bit_index = 0;
        print_message(state, info->si_pid);
    }
}

void server_loop(void)
{
    char    message[MAX_MSG_LENGTH];
    int     bit_index;
    char    current_char;
    int     msg_index;

    bit_index = 0;
    current_char = 0;
    msg_index = 0;
    ft_memset(message, 0, sizeof(message));
    while (1)
    {
        pause();
        if (bit_index == 0)
        {
            message[msg_index++] = current_char;
            message[msg_index] = '\0';
            if (message[msg_index - 1] == '\0')
            {
                ft_printf("Received message: %s\n", message);
                break ;
            }
        }
    }
}

int main(void)
{
    t_sigaction sa;
    pid_t       pid;

    pid = getpid();
    ft_memset(&sa, 0, sizeof(t_sigaction));
    sa.sa_sigaction = append_bit;
    sa.sa_flags = SA_SIGINFO;    
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        ft_printf("sigaction(SIGUSR1) failed");
        exit(1);
    }
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        ft_printf("sigaction(SIGUSR2) failed");
        exit(1);
    }
    ft_printf("Server PID: %d\n", pid);
    while (1)
        pause();
    return (0);
}