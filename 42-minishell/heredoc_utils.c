#include "shell.h"

void	check_quotes(char **ptr, int *in_single_quote, int *in_double_quote)
{
	if (**ptr == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (**ptr == '\"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

int	detect_heredoc(char **ptr, int in_single_quote, int in_double_quote)
{
	if (**ptr == '<' && !in_single_quote && !in_double_quote)
	{
		if (*(*ptr + 1) == '<')
		{
			*ptr += 2;
			while (**ptr && ft_isspace(**ptr))
				(*ptr)++;
			if (**ptr && !ft_isspace(**ptr))
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

int	is_heredoc(char *input)
{
	int		in_single_quote;
	int		in_double_quote;
	char	*ptr;

	in_single_quote = 0;
	in_double_quote = 0;
	ptr = input;
	while (*ptr)
	{
		check_quotes(&ptr, &in_single_quote, &in_double_quote);
		if (detect_heredoc(&ptr, in_single_quote, in_double_quote))
			return (1);
		ptr++;
	}
	return (0);
}
