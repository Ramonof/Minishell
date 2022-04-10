/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolande <mrolande@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:00:30 by mrolande          #+#    #+#             */
/*   Updated: 2022/04/09 18:00:30 by mrolande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	In handle_cd :
**		chdir returns -1 if it fails to change directory
**		return(0) === error
*/

int		cd_minus(t_data *data)
{
	if (var_index("OLDPWD=", data) < 0 ||
	chdir((strchr(data->env[var_index("OLDPWD=", data)], '=') + 1)) == -1)
		return (0);
	change_pwd(data, NULL);
	return (1);
}

int		cd_alone(t_data *data)
{
	if (var_index("HOME=", data) < 0 ||
	chdir((strchr(data->env[var_index("HOME=", data)], '=') + 1)) == -1)
		return (0);
	change_pwd(data, NULL);
	return (1);
}

int		cd_path(char **args, t_data *data)
{
	if (chdir(args[1]) == -1)
		return (0);
	change_pwd(data, args[1]);
	return (1);
}

void	handle_cd(char **args, t_data *data)
{
	if (args[1] && args[2])
		return (error_exit("cd: too many arguments\n"));
	else if (!args[1])
	{
		if (!cd_alone(data))
			return (error_exit("cd: HOME: is undefined\n"));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (!cd_minus(data))
			return (error_exit("cd: OLDPWD is undefined\n"));
	}
	else
	{
		if (!cd_path(args, data))
			return (error_exit("cd: no such file or directory\n"));
	}
}