/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_export.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nepage-l <nepage-l@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 15:38:46 by nepage-l     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/25 16:40:17 by nepage-l    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_tabdup(char **tab)
{
	int		i;
	char	**dup;

	i = 0;
	while (tab[i])
		i++;
	if (!(dup = ft_calloc(sizeof(char *) , i + 1)))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		dup[i] = ft_strdup(tab[i]);
		i++;
	}
	return (dup);
}

void	ft_sort_string_tab(char **tab)
{
	int		i;
	char	*temp;

	i = 0;
	while (tab[i + 1] != 0)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

int		ft_export_print(t_file *file, int i)
{
	char 	**print;
	char 	*temp;
	int 	j;

	i = 0;
	print = ft_tabdup(file->envp);
	ft_sort_string_tab(print);
	while (print[i])
	{
		j = 0;
		while (print[i][j] != '=')
			j++;
		temp = ft_strndup(print[i], j);
		ft_printf("declare -x %s=\"%s\"\n", temp, ft_strchr(print[i], '=') + 1);
		free(temp);
		i++;
	}
	i = -1;
	while (print[++i])
		free(print[i]);
	free(print);
	return (1);
}

int     ft_exist_env(char **env, char *args)
{
	int     i;
	int     j;
	char 	*tmp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		tmp = ft_strndup(env[i], j + 1);
		if (!ft_strncmp(args, tmp, ft_strlen(tmp)))
		{
			free(tmp);
			ft_strcpy(env[i] + j, ft_strchr(args, '='));
			return (1);
		}
		i++;
		free(tmp);
	}
	return (0);
}

int     ft_export(char **args, t_file *file , int i)
{
	char   **new;
	char   *temp;
	t_env	*tmp;
	int		j;

	if (!args[1])
		return (ft_export_print(file, i));
	while (args[i])
	{
		if (!args[i][0] || ft_isdigit(args[i][0]))
		{
			F->status = 1;
			ft_printf("export: `%s': not a valid identifier\n" , args[i]);
			return (1);
		}
		if (!ft_isvar(args[i]))
		{
			tmp = F->env;
			while (tmp && tmp->name && j != -1)
			{
				if (!ft_strcmp(tmp->name, args[i]))
				{
					j = 0;
					while (F->envp[j])
						j++;
					F->envp[j] = ft_strdup(tmp->name);
					F->envp[j] = ft_strjoinrem(F->envp[j], "=");
					F->envp[j] = ft_strjoinrem(F->envp[j], tmp->content);
					F->envp[j + 1] = NULL;
					j = -1;
				}
				tmp = tmp->next;
			}
		}
		else if (!ft_exist_env(F->envp, args[i]))
		{
			j = 0;
			while (F->envp[j])
					j++;
			F->envp[j] = ft_strdup(args[i]);
			F->envp[j + 1] = NULL;
		}
		i++;
	}
	return (1);
}
