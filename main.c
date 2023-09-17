/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndecotti <ndecotti@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:10:47 by ndecotti          #+#    #+#             */
/*   Updated: 2023/09/17 20:09:15 by ndecotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// on garde un pointeur sur le pipe (write end pour child1), (read end pour child2)
void	child_process1(int *fd, char **argv, char **envp);
void	child_process2(int *fd, char **argv, char **envp);
// dup2() it is a function that duplicates fd1 into fd2. so fd2 is now pointing to whatever
// fd1 was ! here we want to fd1 which is the write end of the pipe to take the standart output
// from the execution of the command to write th
// since we have to take the standart output from the command1 to write to the pipe, we
// have to put fd[1] to the first parameter and STDOUT_FILENO as 2nd parameter
int		main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid1;
	int		pid2;

	if (argc != 5)
	{
		ft_putstr_fd("Error : invalid number of arguments\n", 2);
		return (1);
	}
	if (pipe(fd) == -1)
		error_exit_pipe();
	pid1 = fork();
	if (pid1 == -1)
		error_exit_fork();
	if (pid1 == 0)
		child_process1(fd, argv, envp);
	// we know that everything following can be only executed by the main process since
	// if we are in the child process1, nothing will be executed after the execve() function
	// that's why we don't have to write an 'else' condition
	pid2 = fork();
	if (pid2 == -1)
		error_exit_fork();
	if (pid2 == 0)
		child_process2(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	// on ferme les entrees du pipe qui sont ouvertes ds notre programme principal (parent process)
	// command2 needs main process pipe to be closed to finish its execution. if not, command2 is still
	// waiting from the pipe to get input
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
// on envoie le pipe complet ds chaque child_process grace au pointeur sur int

// RQ: SANS DUP2() execve() execute la commande et renvoie effet de execution sur le terminal (standart output)
void	child_process1(int *fd, char **argv, char **envp)
{
	char	*path_cmd1;
	char	**cmd1_array;
	int		infile;

	close(fd[0]); // on close le cote du pipe dont on a pas besoin
	infile = open(argv[1], O_RDONLY, 0644); //0644 permission mode saying that file should be readable and writable
	if (infile == -1)
		handle_open_error(fd[1], argv[1]);
	cmd1_array = ft_split(argv[2], ' ');
	if (cmd1_array == NULL)
		handle_split_error(fd[1], cmd1_array);
	path_cmd1 = check_command_paths(cmd1_array[0], envp); // on envoie la commande ainsi que la variable d'environnement
	// pour checker les differents paths et trouver celui qui permettra a la commande de s'executer
	if (path_cmd1 == NULL)
	{
		handle_cmd_error(fd[1], cmd1_array);
		return ;
	}
	// 1st dup2() duplicate and redirect the standart input of the child process to come from the file 'infile'
	// 2nd dup2() duplicate and redirect the standard output of the child process to the fd[1]
	if (dup2(infile, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
		handle_dup2_error(infile, fd[1], cmd1_array, path_cmd1);
	close(infile);
	// fd[1] remains open because dup2() doesn't simply just move the fd, it also duplicates it.
	// so we have two fd[1] which points to the same pipe. we don't need the two of them, that's
	// why we have to close one ! (same for infile)
	if (execve(path_cmd1, cmd1_array, envp) == -1)
		handle_execve_error(fd[1], cmd1_array, path_cmd1);
	close(fd[1]);
}

void	child_process2(int *fd, char **argv, char **envp)
{
	char	*cmd2_path;
	char	**cmd2_array;
	int		outfile;

	close(fd[1]);
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644); // TRUNC is used to clear the file if something is in it
	if (outfile == -1)
		handle_open_error(fd[0], argv[4]);
	cmd2_array = ft_split(argv[3], ' ');
	if (cmd2_array == NULL)
		handle_split_error(fd[0], cmd2_array);
	cmd2_path = check_command_paths(cmd2_array[0], envp);
	if (cmd2_path == NULL)
	{
		handle_cmd_error(fd[0], cmd2_array);
		return ;
	}
	// in 1st dup2() we redirect the standart input into the read end of the pipe which is pointing to
	// the cmd1 execution output
	// 2nd dup2() redirect the standart output to the outfile. Like that, what is done when cmd2 is
	// executed will be done in the outfile
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(outfile, STDOUT_FILENO) == -1)
		handle_dup2_error(outfile, fd[0], cmd2_array, cmd2_path);
	close(outfile);
	if (execve(cmd2_path, cmd2_array, envp) == -1)
		handle_execve_error(fd[0], cmd2_array, cmd2_path);
	close(fd[0]);
}