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

void	handle_cmd_error(int fd, char **cmd1_array)
{
	cmd_not_found(cmd1_array[0]); // le premier element [0] du tableau de path contient le nom de la commande (a verifier)
	free_array(cmd1_array, size_array(cmd1_array));
	close(fd);
}

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

void	error_exit_pipe(void)
{
	perror("failed to pipe");
	exit(EXIT_FAILURE);
}

void	error_exit_fork(void)
{
	perror("failet to fork");
	exit(EXIT_FAILURE);
}

void	open_error_msg(char *file_name)
{
	char	*msg_syst;
	char	*error_msg;
	char	*temp;

	// as the errno is a global variable provided by the C library, any function within the program
	// has access to the value stored in 'errno'
	msg_syst = strerror(errno); // errno = code systeme representant: No such file or directory
	temp = ft_strjoin(msg_syst, ": ");
	error_msg = ft_strjoin(temp, file_name);
	free(temp);
	temp = NULL; // on reassigne valeur NULL a variable
	temp = ft_strjoin(error_msg, "\n");
	free(temp);
	ft_putstr_fd(error_msg, 2); // envoie msg erreur complet dans la sortie d'erreur
	free(error_msg);
}

void	handle_open_error(int fd, char *file_name)
{
	close(fd);
	open_error_msg(file_name);
	exit(EXIT_FAILURE);
}

// a tester
// Remarque: fd peut etre le write end fd[1] ou le read end fd[0] du pipe. tout depend
// du child process qui appel la fonction handle_dup2_error
void	handle_dup2_error(int file, int fd, char **cmd_array, char *cmd_path)
{
	free(cmd_path);
	free_array(cmd_array, size_array(cmd_array));
	close(file);
	close(fd);
	perror("failed to dup2");
	exit(EXIT_FAILURE);
}

// A TESTER
void	handle_split_error(int fd, char **cmd1_array)
{
	close(fd);
	free_array(cmd1_array, size_array(cmd1_array));
	perror("failed to split command");
	exit(EXIT_FAILURE);
}

// A TESTER
void	handle_execve_error(int fd, char **cmd_array, char *cmd_path)
{
	free(cmd_path);
	free_array(cmd_array, size_array(cmd_array));
	close(fd);
	perror("failed to execute the command");
	exit(EXIT_FAILURE);
}