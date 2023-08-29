#include "pipex.h"

//dup2() simple example
int	main()
{
	int	fd;

	fd = open("exemple.txt", O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	printf("this is printed in exemple.txt\n");
	return (0);
}

// execve() executes the command ls -l in the terminal
// it doesn't print anything since the process image has been replaced
// by execve()
int	main()
{
	char	*args[3];

	args[0] = "ls";
	args[1] = "-l";
	args[2] = NULL;
	execve("/bin/ls", args, NULL);
	printf("this line won't be executed");
	return (0);
}

// fork() function
// affiche les deux printf sur le terminal ac %d correspondant au numero du pid
// donne par la fonction getpid()
// chaque process a son propre pid
// les deux processus (parent et enfant) s'exit en tte autonomie
int main()
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
        printf("This is the child process. (pid: %d)\n", getpid());
    else
        printf("This is the parent process. (pid: %d)\n", getpid());

    return (0);
}

// pipe() function

int main()
{
    int		fd[2];
    pid_t	pid;
    char	buffer[13];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(fd[0]); // close the read end of the pipe (we don't need this part)
        write(fd[1], "Hello parent!", 13);
        close(fd[1]); // close the write end of the pipe
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fd[1]); // close the write end of the pipe (we need to read only)
        read(fd[0], buffer, 13);
        close(fd[0]); // close the read end of the pipe
        printf("Message from child: '%s'\n", buffer);
        exit(EXIT_SUCCESS);
    }
}
// ici le message s'affiche sur le terminal car a defaut de configuration, le terminal est le
// stdout (standard output) du programme
// dans cette fonction, descripteur de fichier sont crees et vide par default
// lorsque l'on est ds pid == 0, on ferme le read file [0], on ecrit sur le write file [1] le msg
// puis on quitte et on passe au ELSE ou cette fois on ferme le write file [1] pour ne lire que
// le read file [0] qui a acces au write file [1] (puisqu'il y a un pipe) en mode lecture
// ensuite fait appel a printf en imprimant le contenu de la variable buffer (%s) obtenu en faisant
// appel a la fonction read ds read file[0]

// reproduce a bash command using grep
int	main()
{
	int		fd[2];
	int 	pid1;
	int		pid2;
	char	*args;
	char	*args2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		// child process 1 for ping commmand
		dup2(fd[1], STDOUT_FILENO); // duplicate the write end of the pipe
		close(fd[0]);
		close(fd[1]);
		args = {"ping", "-c", "5", NULL}; // la commande a executer
		execve("ping", args, //environnemnt); // fonction qui execute la commande
	}

	pid2 = fork();
	if (pid2 < 0)
		return (3);
	if (pid == 0)
	{
		// child process 2 for grep
		dup2(fd[0], STDIN_FILENO); // on a besoin de voir la reading part dans notr input
		close(fd[0]);
		close(fd[1]);
		args2 = {"grep", "rtt", NULL};
	}
}