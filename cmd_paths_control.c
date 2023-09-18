/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndecotti <ndecotti@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 21:04:02 by ndecotti          #+#    #+#             */
/*   Updated: 2023/08/26 21:04:02 by ndecotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**create_array_of_paths(char **envp);
char	*create_path_command(char *path, char *cmd);

// recoit en parametre la commande et la variable d'env
// fonction qui va chercher tous les paths dans la variable d'environnement
// pour les tester ensuite
// if (access(path_to_test, F_OK) == 0) -> chemin existe et est accessible
// si path non accessible on clear path_to_test et on passe au suivant (i++)
char	*check_command_paths(char *cmd, char **envp)
{
	int		i;
	char	**paths_array;
	char	*path_to_test;

	paths_array = create_array_of_paths(envp);
	i = 0;
	while (paths_array[i])
	{
		path_to_test = create_path_command(paths_array[i], cmd);
		if (access(path_to_test, F_OK) == 0)
		{
			free(paths_array);
			return (path_to_test);
		}
		free(path_to_test);
		path_to_test = NULL;
		i++;
	}
	free_array(paths_array, size_array(paths_array));
	return (0);
}

// retourne un pointeur qui pointe vers un tableau de char contenant a chaque
// case un path particulier
// i is used to iterate through each element of the envp array until it reachs
// the end of the envp array (envp[i] becomes NULL)
char	**create_array_of_paths(char **envp)
{
	char	*paths;
	char	**paths_array;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = ft_substr(envp[i], 6, ft_strlen(envp[i]) - 5);
		i++;
	}
	paths_array = ft_split(paths, ':');
	free(paths);
	paths = NULL;
	return (paths_array);
}

//create a full path to the executable by concatenating the path with the cmd
char	*create_path_command(char *path, char *cmd)
{
	char	*temp;
	char	*path_cmd;

	temp = ft_strjoin(path, "/");
	path_cmd = ft_strjoin(temp, cmd);
	free(temp);
	temp = NULL;
	return (path_cmd);
}
// temp = NULL -> clear le pointeur