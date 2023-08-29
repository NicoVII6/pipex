/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndecotti <ndecotti@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:18:21 by ndecotti          #+#    #+#             */
/*   Updated: 2023/08/13 20:18:21 by ndecotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(const char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (words);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < (len - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

static char	**free_all(char **arr)
{
	while (*arr)
		free(*arr);
	free(arr);
	return(NULL);
}

/* retourne la valeur du pointeur de str_len à chaque fin de mot trouvé dans la chaine de caractères
dans la fonction split */

static void	get_row(char **str, int *str_len, char c)
{
	int	i;

	*str += *str_len;
	*str_len = 0;
	i = 0;
	while (**str && **str == c)
		(*str)++;
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			return;
		(*str_len)++;
		i++;
	}
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	char	*str;
	int		words_nb;
	int		i;
	int		str_len;

	words_nb = count_words(s, c);
	arr = malloc(sizeof(char *) * (words_nb + 1));
	if (!arr)
		return (NULL);
	str = (char *)s;
	i = 0;
	str_len = 0;
	while (i < words_nb)
	{
		get_row(&str, &str_len, c);
		arr[i] = malloc(sizeof(char) * (str_len + 1));
		if (arr[i] == NULL)
			return (free_all(arr));
		ft_strlcpy(arr[i], str, str_len + 1);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
/* arr[i] = NULL libère le tableau qui contient l'adresse du début de chaque mot */