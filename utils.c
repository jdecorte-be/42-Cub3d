#include "parsing.h"

static void	free_join(void *s1, void *s2, int e)
{
	if (e == 1 || e == 3)
		free(s1);
	else if (e == 2 || e == 3)
		free(s2);
}

char	*ft_free_join(char const *s1, char const *s2, int e)
{
	char	*dst;
	size_t	i;
	size_t	len_s1;
	size_t	len_dst;

	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	len_s1 = ft_strlen(s1);
	len_dst = len_s1 + ft_strlen(s2);
	dst = malloc(sizeof(*dst) * len_dst + 1);
	if (!dst)
		return (0);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	i = -1;
	while (s2[++i])
		dst[len_s1 + i] = s2[i];
	dst[len_s1 + i] = '\0';
	if (e)
		free_join((void *)s1, (void *)s2, e);
	return (dst);
}