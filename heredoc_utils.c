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

char	*append_line_to_heredoc_content(
	char *heredoc_content, char *line, size_t *total_len)
{
	size_t	line_len;

	line_len = strlen(line);
	heredoc_content = ft_realloc(heredoc_content, *total_len + line_len + 2);
	if (!heredoc_content)
		exit(EXIT_FAILURE);
	ft_strlcpy(heredoc_content + *total_len, line, line_len + 1);
	*total_len += line_len;
	heredoc_content[(*total_len)++] = '\n';
	heredoc_content[*total_len] = '\0';
	return (heredoc_content);
}

void	write_heredoc_to_file(const char *filename, const char *content)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	write(fd, content, ft_strlen(content));
	close(fd);
}
