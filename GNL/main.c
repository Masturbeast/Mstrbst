#include <stdio.h>
#include "get_next_line.h"

int main()
{
	char 	*line;
	int		out;
	int		p[2];
	char 	*str;
	int		len = 50;

	write(1, "hello\n", 7);
	str = (char *)malloc(1000 * 1000);
	*str = '\0';
	while (len--)
		strcat(str, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur in leo dignissim, gravida leo id, imperdiet urna. Aliquam magna nunc, maximus quis eleifend et, scelerisque non dolor. Suspendisse augue augue, tempus");
	out = dup(1);
	pipe(p);
	dup2(p[1], 1);
	if (str)
	{
		write(1, str, strlen(str));
	}
	close(p[1]);
	dup2(out, 1);
	get_next_line(p[0], &line);
	if (ft_strequ(line, str))
		printf("ok\n");
	else
		printf("ko\n");
	free(str);
	return 0;
}
