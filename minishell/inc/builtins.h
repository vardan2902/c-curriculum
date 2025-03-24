/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vapetros <vapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:12:10 by vapetros          #+#    #+#             */
/*   Updated: 2025/03/24 15:12:35 by vapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_echo(char **args, t_ht *env);
int	ft_pwd(char **args, t_ht *env);
int	ft_cd(char **args, t_ht *env);
int	ft_unset(char **args, t_ht *env);
int	ft_exit(char **args, t_ht *env);
int	ft_env(char **args, t_ht *env);
int	ft_export(char **args, t_ht *env);

#endif
