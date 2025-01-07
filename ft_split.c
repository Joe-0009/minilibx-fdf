/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:11:30 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/07 15:44:38 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_words_count(char const *s, char c)
{
	int	count;
	int	word;

	count = 0;
	word = 0;
	while (*s)
	{
		if (*s != c && !word)
		{
			word = 1;
			count++;
		}
		else if (*s == c)
		{
			word = 0;
		}
		s++;
	}
	return (count);
}

char	*ft_str_s_dup(char const *s, char c, int *start)
{
	char	*dup;
	int		end;
	int		i;

	end = 0;
	while (s[*start + end] && s[*start + end] != c)
		end++;
	dup = (char *)calloc(end + 1, 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < end)
	{
		dup[i] = s[*start];
		(*start)++;
		i++;
	}
	return (dup);
}

void	ft_free_strs(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	strs = (char **)calloc((ft_words_count(s, c) + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c && s[i++])
			continue ;
		strs[j] = ft_str_s_dup(s, c, &i);
		if (!strs[j++])
			return (ft_free_strs(strs), NULL);
	}
	strs[j] = NULL;
	return (strs);
}
