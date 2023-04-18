/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 09:25:01 by lsordo            #+#    #+#             */
/*   Updated: 2022/11/01 15:00:40 by lsordo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static	char	**ft_freealloc(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
		free(arr[j++]);
	free(arr);
	return (NULL);
}

static	char	**ft_getwds(char **arr, char *s, char c)
{
	size_t		last;
	size_t		len;
	size_t		i;

	i = 0;
	len = 0;
	last = 0;
	while (s[last + len])
	{
		while (s[last + len] && s[last + len] != c)
			len++;
		arr[i] = malloc((len + 1) * sizeof(char));
		if (arr[i] == NULL)
			return (ft_freealloc(arr));
		ft_memcpy(arr[i], s + last, len);
		arr[i][len] = '\0';
		while (s[last + len] && s[last + len] == c)
			len++;
		last += len;
		len = 0;
		i++;
	}
	return (NULL);
}

static	size_t	ft_ctwd(char *s, char c)
{
	size_t		wds;
	size_t		i;

	wds = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
		wds++;
	}
	return (wds);
}

char	**ft_split(const char *s, char c)
{
	char	*st;
	size_t	wds;
	char	**arr;
	char	buf[2];

	if (!s)
		return (NULL);
	buf[0] = c;
	buf[1] = '\0';
	st = ft_strtrim(s, buf);
	if (!st)
		return (NULL);
	wds = ft_ctwd(st, c);
	arr = malloc((wds + 1) * sizeof(char *));
	if (arr == NULL)
	{
		free(st);
		return (NULL);
	}
	ft_getwds(arr, st, c);
	arr[wds] = NULL;
	free(st);
	return (arr);
}
