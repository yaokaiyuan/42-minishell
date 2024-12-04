#include "shell.h"

void	handle_sigquit(int sig)
{
	(void)sig;
	write(1, "Quit (core dumped)\n", 19);
}

void	handle_sigint_blocking(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0); // check on linux
	rl_redisplay();
}
