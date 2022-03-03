#include "minishell.h"

int main(void)
{
	int fd;
	int num_error = 127;
	int buf_size = 4;
	char *filename = "sandbox/save_error.txt";
	char *str_error;

	str_error = ft_itoa(num_error);
	fd = open(filename, O_CREAT | O_WRONLY, S_IRWXU);
	write(fd, str_error, ft_strlen(str_error));
	close(fd);
	free(str_error);

	str_error = ft_calloc(sizeof(char), buf_size);
	fd = open(filename, O_RDONLY, S_IRWXU);
	read(fd, str_error, buf_size);
	close(fd);
	printf("%s\n", str_error);
	free(str_error);
}