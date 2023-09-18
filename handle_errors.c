/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndecotti <ndecotti@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 20:14:32 by ndecotti          #+#    #+#             */
/*   Updated: 2023/08/13 20:14:32 by ndecotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_not_found(char *cmd)
{
	char	*error_msg;
	char	*temp;

	temp = ft_strjoin("command not found: ", cmd);
	error_msg = ft_strjoin(temp, "\n");
	ft_putstr_fd(error_msg, 2);
	free(temp);
	free(error_msg);
}

void	handle_cmd_error(int fd, char **cmd1_array)
{
	cmd_not_found(cmd1_array[0]);
	free_array(cmd1_array, size_array(cmd1_array));
	close(fd);
}

// Remarque: fd peut etre le write end fd[1] ou le read end fd[0] du pipe.
// tout depend du child process qui appelle la fonction
void	handle_dup2_error(int file, int fd, char **cmd_array, char *cmd_path)
{
	free(cmd_path);
	free_array(cmd_array, size_array(cmd_array));
	close(file);
	close(fd);
	perror("failed to dup2");
	exit(EXIT_FAILURE);
}

void	handle_split_error(int fd, char **cmd1_array)
{
	close(fd);
	free_array(cmd1_array, size_array(cmd1_array));
	perror("failed to split command");
	exit(EXIT_FAILURE);
}

void	handle_execve_error(int fd, char **cmd_array, char *cmd_path)
{
	free(cmd_path);
	free_array(cmd_array, size_array(cmd_array));
	close(fd);
	perror("failed to execute the command");
	exit(EXIT_FAILURE);
}
