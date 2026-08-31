/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 18:50:13 by jmagand           #+#    #+#             */
/*   Updated: 2025-04-11 18:50:13 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	parse_args(t_params *p, char **av)
{
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0)
		return (ft_write(2, R"An argument is incorrect."RST, 0));
	if (av[5])
	{
		if (ft_atoi(av[5]) <= 0)
			return (ft_write(2, R"Argument [5] is incorrect."RST, 0));
		p->x_meals = ft_atoi(av[5]);
	}
	else
		p->x_meals = -42;
	p->x_philos = ft_atoi(av[1]);
	p->t_die = ft_atoi(av[2]);
	p->t_eat = ft_atoi(av[3]);
	p->t_sleep = ft_atoi(av[4]);
	return (true);
}

bool	check_args(t_params *p, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (ft_write(2, R"Invalid number of argument."RST, 0));
	if (!check_digit(av))
		return (ft_write(2, R"Argument must contains only digit."RST, 0));
	if (!parse_args(p, av))
		return (false);
	return (true);
}
