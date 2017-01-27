/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whitespaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 10:21:32 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/27 09:32:23 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_word(char const *s, int i, int word)
{
	int	tmp;

	while (s[i] != '\0')
	{
		if (!ft_isspace(s[i]) && s[i] != '\0')
			word++;
		if (s[i++] == 34)
		{
			tmp = i;
			while (s[i] != 34 && s[i])
				i++;
			if (s[i] == '\0')
			{
				word--;
				i = tmp;
			}
		}
		else
			while (!ft_isspace(s[i]) && s[i] != '\0' && s[i])
				i++;
		s[i] != '\0' ? i++ : 0;
	}
	return (word);
}

void			ft_fill(char const *s, char ***array)
{
	int i;
	int letter;
	int word;

	i = 0;
	word = 0;
	while (s[i])
	{
		letter = 0;
		if (s[i] == 34)
		{
			i++;
			while (s[i] && s[i] != 34)
				(*array)[word][letter++] = s[i++];
			if (s[i] == 34)
				i++;
		}
		else
			while (!ft_isspace(s[i]) && s[i])
				(*array)[word][letter++] = s[i++];
		(*array)[word++][letter] = '\0';
		while (ft_isspace(s[i]) && s[i])
			i++;
	}
	(*array)[word] = 0;
}

void			ft_letter(char const *s, char ***array, int i, int word)
{
	int letter;

	while (s[i])
	{
		letter = 0;
		if (s[i] == 34)
		{
			i++;
			while (s[i++] != 34 && s[i])
				letter++;
			(s[i] == 34) ? i++ : 0;
		}
		else
			while (!ft_isspace(s[i]) && s[i])
			{
				letter++;
				i++;
			}
		while (ft_isspace(s[i]) && s[i])
			i++;
		if (!((*array)[word++] = (char*)malloc(sizeof(char) * (letter + 1))))
			return ;
	}
}

char			**ft_whitespaces(char const *s)
{
	int		word;
	char	**array;
	char	*string;

	if (!(s))
		return (NULL);
	if (!(string = ft_strtrim(s)))
		return (0);
	word = ft_word(string, 0, 0);
	if (!(array = (char**)malloc(sizeof(char*) * (word + 1))))
		return (0);
	ft_letter(string, &array, 0, 0);
	ft_fill(string, &array);
	free(string);
	return (array);
}
