/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndecotti <ndecotti@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:57:25 by ndecotti          #+#    #+#             */
/*   Updated: 2023/08/12 16:57:25 by ndecotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **array, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		free(array[i]); // libere la case contenat la string du path
		i++;
	}
	free(array); // libere le tableau
}

int		size_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}