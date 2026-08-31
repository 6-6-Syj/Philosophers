/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 18:47:04 by jmagand           #+#    #+#             */
/*   Updated: 2025-04-11 18:47:04 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	handle_error(t_params *p)
{
	int	i;

	i = 0;
	if (p->philos && get_long(&p->m_params, &p->x_philos_created) > 0)
		join_philosophers(p);
	if (p->watcher_created)
		if (pthread_join(p->watcher, NULL))
			return (ft_write(2, R FAIL_THR_JOIN RST, 0));
	if (secure_mutex(&p->m_params, DESTROY) || secure_mutex(&p->m_print,
			DESTROY))
		return (false);
	if (p->forks)
	{
		while (i < p->x_philos)
		{
			if (p->forks[i].initialized)
				if (secure_mutex(&p->forks[i].m_fork, DESTROY))
					return (false);
			if (p->philos && p->philos[i].m_initialized)
				if (secure_mutex(&p->philos[i].m_philo, DESTROY))
					return (false);
			i++;
		}
	}
	return (true);
}

static bool	handle_normal(t_params *p)
{
	int	i;

	if (p->watcher_created)
		if (pthread_join(p->watcher, NULL))
			return (ft_write(2, R FAIL_THR_JOIN RST, 0));
	i = 0;
	if (secure_mutex(&p->m_params, DESTROY) || secure_mutex(&p->m_print,
			DESTROY))
		return (false);
	if (p->philos)
	{
		while (i < p->x_philos)
		{
			if (p->forks)
			{
				if (secure_mutex(&p->forks[i].m_fork, DESTROY))
					return (false);
			}
			if (secure_mutex(&p->philos[i].m_philo, DESTROY))
				return (false);
			i++;
		}
	}
	return (true);
}

static bool	free_all(t_params *p, bool error)
{
	set_bool(&p->m_params, &p->end_simulation, true);
	if (!error)
		handle_normal(p);
	else
		handle_error(p);
	if (p->philos)
		free(p->philos);
	if (p->forks)
		free(p->forks);
	return (error);
}

int	main(int ac, char **av)
{
	t_params	p;

	if (!check_args(&p, ac, av))
		return (1);
	if (!init_params(&p, 0))
	{
		if (!p.philos)
			return (1);
		return (free_all(&p, true));
	}
	if (!init_philo(&p, 0))
		return (free_all(&p, true));
	if (!start_simulation(&p))
		return (free_all(&p, true));
	if (free_all(&p, false))
		return (ft_write(1, R "\n\t\tfree_all didn't worked well !\n" RST, 1));
	else
		printf(B "\n\t\tSimulation ended normally !\n" RST);
	return (0);
}
