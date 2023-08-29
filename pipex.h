#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

void	child_process1(int *fd, char **argv, char **envp);
void	child_process2(int *fd, char **argv, char **envp);

char	**create_array_of_paths(char **envp);
char	*create_path_command(char *path, char *cmd);
char	*check_command_paths(char *cmd, char **envp);

int		size_array(char **array);
void	free_array(char **array, int size);

void	handle_dup2_error(int infile, int fd, char **cmd_array, char *path_cmd);
void	error_exit_pipe(void);
void	error_exit_fork(void);
void	handle_split_error(int fd, char **cmd1_array);
void	open_error_msg(char *file_name);
void	handle_open_error(int fd, char *file_name);
void	handle_execve_error(int fd, char **cmd_array, char *cmd_path);
void	handle_cmd_error(int fd, char **cmd1_array);
void	cmd_not_found(char *cmd);
void	handle_execve_error(int fd, char **cmd_array, char *cmd_path);

size_t	ft_strlen(const char *str);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);

char	**ft_split(const char *s, char c);

#endif