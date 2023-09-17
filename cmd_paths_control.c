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

// fonction qui va chercher tous les paths dans la variable d'environnement pour les tester ensuite
// retourne un pointeur sur char si chemin de la commande teste est accessible 
// 0 si aucun des chemins ne permet d'executer la commande
char	*check_command_paths(char *cmd, char **envp)
{
	int		i;
	char	**paths_array;
	char	*path_to_test;

	paths_array = create_array_of_paths(envp);
	// calls this function to obtain an array of directory paths when executables might be located
	i = 0;
	while (paths_array[i]) // on parcourt chaque path trouve grace a fonction 'create_array_of_paths'
	{
		path_to_test = create_path_command(paths_array[i], cmd);
		// create a full path to the executable by concatenating the path with the cmd name
		if (access(path_to_test, F_OK) == 0) // signifie que le chemin commande existe et qu'il est accessible
		{
			free(paths_array); // on efface tableau contenant les paths
			return(path_to_test); // on retourne le path valide
		}
		free(path_to_test); // on efface le chemin teste non accessible
		path_to_test = NULL;// on clear la variable pour pouvoir lui attribuer le prochain chemin a tester
		i++; // on passe au chemin d'apres
	}
	free_array(paths_array, size_array(paths_array)); // libere cases tableaux ainsi que pointeur sur case
	return (0);
}

// retourne un pointeur qui pointe vers un tableau de char contenant a chaque index
// un chemin particulier de la commande a executer
char	**create_array_of_paths(char **envp)
{
	char	*paths; // pointeur sur string qui representera tous les chemins contenu ds 'PATH='
	char	**paths_array; // pointeur sur un tableau de strings ou chaque case contient un path
	int		i;

	i = 0;
	// chaque i represente une ligne dans envp[i]; tant que nous ne sommes pas sur la ligne 'PATH='
	// nous incrementons i;
	while (envp[i])
	{
		// si nous nous trouvons sur la ligne 'PATH=' de envp[i]
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = ft_substr(envp[i], 6, ft_strlen(envp[i]) - 5);
			// on recopie toute la ligne 'i' contenant tous les chemins trouves ds la variable d'environnemt
			// a partir du 6e caractere ds la striong path
		i++;
	}
	// ensuite on separe chaque path trouve dans 'PATH=' ac 'ft_split'et le separateur ':'
	paths_array = ft_split(paths, ':');
	free(paths);
	paths = NULL;
	return(paths_array);
}

// concatene le path valide avec le nom de la commande en utilisant '/'
char	*create_path_command(char *path, char *cmd)
{
	char	*temp;
	char	*path_cmd;

	temp = ft_strjoin(path, "/");
	path_cmd = ft_strjoin(temp, cmd);
	free(temp);
	temp = NULL; // clear le pointeur qui pointait sur la string
	return (path_cmd);
}