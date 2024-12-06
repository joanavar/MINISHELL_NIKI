/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:00:13 by camurill          #+#    #+#             */
/*   Updated: 2024/02/05 21:09:51 by camurill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cword(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[0] != c && s[0])
	{
		count++;
		i++;
	}
	while (s[i])
	{
		while (s[i] == c && s[i + 1])
			i++;
		if (s[i] != c && s[i - 1] == c && s[i])
			count++;
		i++;
	}
	return (count);
}

static char	*ft_dupchar(char const *s, char c, int *pos)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	len = 0;
	while (*s == c)
	{
		s++;
		(*pos)++;
	}
	while (s[len] && s[len] != c)
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (0);
	while (i < len)
	{
		dup[i] = *s;
		i++;
		s++;
	}
	dup[i] = '\0';
	*pos += i;
	return (dup);
}

static char	**ft_free(char **s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	char	**split;
	int		pos;

	if (!s)
		return (NULL);
	i = 0;
	pos = 0;
	count = ft_cword(s, c);
	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	while (i < count)
	{
		split[i] = ft_dupchar(s + pos, c, &pos);
		if (split[i] == NULL)
			return (ft_free(split, i));
		i++;
	}
	split[i] = NULL;
	return (split);
}
/*
int main(void)
{
	char const *p = "hello!zzzzzzzz";
	char t = 'z';
	ft_split(p, t);
	return (0);
}*/
