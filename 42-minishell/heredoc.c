#include "shell.h"

char	*generate_unique_filename(void)
{
	static int	i = 0;
	char		*number;
	char		*filename;

	number = ft_itoa(i++);
	if (!number)
		exit(EXIT_FAILURE);
	filename = ft_strjoin("/tmp/minishell_heredoc", number);
	free(number);
	if (!filename)
		exit(EXIT_FAILURE);
	return (filename);
}

char	*get_delimiter(char *input)
{
	char	*start;
	char	*end;
	size_t	len;
	char	*delimiter;

	start = ft_strnstr(input, "<<", strlen(input));
	if (!start)
		return (NULL);
	start += 2;
	while (*start == ' ')
		start++;
	end = start;
	while (*end && *end != ' ' && *end != '\n')
		end++;
	len = end - start;
	delimiter = (char *)malloc(len + 1);
	if (!delimiter)
		return (NULL);
	ft_strlcpy(delimiter, start, len + 1);
	return (delimiter);
}

char	*read_heredoc_input(const char *delimiter)
{
	char	*heredoc_content;
	char	*line;
	size_t	total_len;
	size_t	line_len;

	heredoc_content = NULL;
	total_len = 0;
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0))
			break ;
		line_len = strlen(line);
		heredoc_content = ft_realloc(heredoc_content, total_len + line_len + 2);
		if (!heredoc_content)
			exit(EXIT_FAILURE);
		ft_strlcpy(heredoc_content + total_len, line, line_len + 1);
		total_len += line_len;
		heredoc_content[total_len++] = '\n';
		heredoc_content[total_len] = '\0';
		free(line);
	}
	free(line);
	if (heredoc_content)
		return (heredoc_content);
	return (ft_strdup(""));
}

char	*replace_heredoc_with_filename(char *input, char *delimiter, char *filename)
{
	char	*start;
	char	*end;
	size_t	new_input_len;
	char	*new_input;

	start = ft_strnstr(input, "<<", ft_strlen(input));
	if (!start)
		return (NULL);
	end = start + 2;
	while (*end == ' ')
		end++;
	end += ft_strlen(delimiter);
	while (*end == ' ' || *end == '\n')
		end++;
	new_input_len = ft_strlen(input) - (end - start) + ft_strlen(filename) + 5;
	new_input = (char *)malloc(new_input_len);
	if (!new_input)
		exit(EXIT_FAILURE);
	ft_strlcpy(new_input, input, start - input + 1);
	ft_strlcat(new_input, "< ", new_input_len);
	ft_strlcat(new_input, filename, new_input_len);
	ft_strlcat(new_input, " ", new_input_len);
	ft_strlcat(new_input, end, new_input_len);
	return (new_input);
}

char	*handle_heredoc(char *input)
{
	char	*delimiter;
	char	*heredoc_content;
	char	*tmp_filename;
	int		fd;
	char	*updated_input;

	tmp_filename = generate_unique_filename();
	delimiter = get_delimiter(input);
	if (!delimiter)
		return (input);
	heredoc_content = read_heredoc_input(delimiter);
	if (!heredoc_content)
	{
		free(delimiter);
		return (NULL);
	}
	fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	write(fd, heredoc_content, ft_strlen(heredoc_content));
	close(fd);
	updated_input = replace_heredoc_with_filename(input, delimiter, tmp_filename);
	free(delimiter);
	free(heredoc_content);
	free(tmp_filename);
	return (updated_input);
}
