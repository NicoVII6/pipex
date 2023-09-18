/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndecotti <ndecotti@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:47:40 by ndecotti          #+#    #+#             */
/*   Updated: 2023/09/18 15:55:38 by ndecotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_arg_error(void)
{
	ft_putstr_fd("Error : invalid number of arguments\n", 2);
	exit(EXIT_FAILURE);
}

void	error_exit_pipe(void)
{
	perror("failed to pipe");
	exit(EXIT_FAILURE);
}

void	error_exit_fork(void)
{
	perror("failed to fork");
	exit(EXIT_FAILURE);
}

//REMARQUE: as the errno is a global variable provided by the C library,
// any function within the program has access to the value stored in 'errno'
void	open_error_msg(char *file_name)
{
	char	*msg_syst;
	char	*error_msg;
	char	*temp;

	msg_syst = strerror(errno);
	temp = ft_strjoin(msg_syst, ": ");
	error_msg = ft_strjoin(temp, file_name);
	free(temp);
	temp = NULL;
	temp = ft_strjoin(error_msg, "\n");
	free(temp);
	ft_putstr_fd(error_msg, 2);
	free(error_msg);
}

void	handle_open_error(int fd, char *file_name)
{
	close(fd);
	open_error_msg(file_name);
	exit(EXIT_FAILURE);
}
