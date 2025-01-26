#include "client.h"

void handle_ack(int sig)
{
    if (sig == SIGUSR1)
        ft_printf("Message received by server.\n");
    exit(0);
}

int are_args_valid(char **argv)
{
    pid_t server_pid;
    
    server_pid = ft_atoi(argv[1]);
    if (server_pid <= 0)
    {
        ft_printf("Error: Invalid server PID.\n");
        return 1;
    }
    if (ft_strlen(argv[2]) == 0)
    {
        ft_printf("Error: Empty message.\n");
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    pid_t   server_pid;
    char    *message;
    
    if (argc != 3 || are_args_valid(argv))
    {
        ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
        return (1);
    }
    server_pid = ft_atoi(argv[1]);
    message = argv[2];
    signal(SIGUSR1, handle_ack);
    send_message(message, server_pid);
    pause();
    return (0);
}