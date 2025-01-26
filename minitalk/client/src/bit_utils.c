#include "client.h"

static void char_to_bits(char c, int *bits)
{
    int i = 8;
    while (--i >= 0)
        bits[7 - i] = (c >> i) & 1;
}

static void send_bit(int bit, pid_t server_pid)
{
    if (bit == 1)
        kill(server_pid, SIGUSR1);
    else
        kill(server_pid, SIGUSR2);
    usleep(100);
}

static void send_null_byte(pid_t server_pid)
{
    int i;

    i = -1;
    while (++i < 8)
        send_bit(0, server_pid);
}

void    send_message(char *message, pid_t server_pid)
{
    int bits[8];
    int i;
    int j;

    i = -1;
    while (message[++i] != '\0')
    {
        char_to_bits(message[i], bits);
        j = -1;
        while (++j < 8)
            send_bit(bits[j], server_pid);
    }
    send_null_byte(server_pid);
}
