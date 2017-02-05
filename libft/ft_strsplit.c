/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 15:27:12 by lbopp             #+#    #+#             */
/*   Updated: 2017/02/05 16:27:41 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			word++;
		}
		while (s[i] != c && s[i + 1] != '\0' && s[i])
			i++;
		s[i] ? i++ : 0;
	}
	return (word);
}

static	char	**ft_fill(char *s, char **array, char c)
{
	int i;
	int letter;
	int word;

	i = 0;
	word = 0;
	while (s[i])
	{
		letter = 0;
		while (s[i] != c && s[i])
		{
			array[word][letter] = s[i];
			letter++;
			i++;
		}
		array[word][letter] = '\0';
		while (s[i] == c && s[i])
			i++;
		word++;
	}
	array[word] = 0;
	free(s);
	return (array);
}

static	char	**ft_letter(char const *s, char c, char **array)
{
	int i;
	int letter;
	int word;

	i = 0;
	word = 0;
	while (s[i])
	{
		letter = 0;
		while (s[i] != c && s[i])
		{
			letter++;
			i++;
		}
		while (s[i] == c && s[i])
			i++;
		if (!(array[word] = (char*)malloc(sizeof(char) * (letter + 1))))
			return (NULL);
		word++;
	}
	return (array);
}

char			**ft_strsplit(char *s, char c)
{
	int		i;
	int		word;
	char	**array;
	char	*new;

	i = 0;
	word = 0;
	if (!(s))
		return (NULL);
	if (!(new = ft_strtrimchar(s, c)))
		return (0);
	free(s);
	if (!(array = (char**)malloc(sizeof(char*) * (ft_word(new, c) + 1))))
		return (0);
	if (!(array = ft_letter(new, c, array)))
		return (0);
	return (ft_fill(new, array, c));
}
