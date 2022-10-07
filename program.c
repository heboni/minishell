#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

int main(void)
{
    char    *s;

    s = "I'm program to test relative path\n";
    write(1, s, ft_strlen(s));
    return (0);
}