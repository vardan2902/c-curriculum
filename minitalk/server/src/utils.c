#include "server.h"

void set_bit_in_char(int sig, t_server *state)
{
    if (sig == SIGUSR1)
        state->current_char |= (1 << (7 - state->bit_index));
}

void append_char_to_message(t_server *state)
{
    state->message[state->msg_index++] = state->current_char;
    state->message[state->msg_index] = '\0';
}

void print_message(t_server *state, int pid)
{
    if (state->message[state->msg_index - 1] == '\0')
    {
        ft_printf("Received message: %s\n", state->message);
        kill(pid, SIGUSR1);
        state->bit_index = 0;
        state->current_char = 0;
        state->msg_index = 0;
    }
}