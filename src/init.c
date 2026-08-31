/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 20:24:39 by jmagand           #+#    #+#             */
/*   Updated: 2025-04-11 20:24:39 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	malloc_params(t_params *p)
{
	p->philos = malloc(sizeof(t_philo) * p->x_philos);
	if (!p->philos)
		return (ft_write(2, R"Malloc failed for p->philos"RST, 0));
	p->forks = malloc(sizeof(t_fork) * p->x_philos);
	if (!p->forks)
	{
		free(p->philos);
		p->philos = NULL;
		return (ft_write(2, R"Malloc failed for p->forks"RST, 0));
	}
	return (true);
}

bool	init_params(t_params *p, int i)
{
	p->end_simulation = false;
	p->philos_ready = false;
	p->x_philos_rdy = 0;
	p->x_philos_created = 0;
	p->watcher_created = false;
	p->t_start = get_time();
	if (!malloc_params(p))
		return (false);
	while (i < p->x_philos)
	{
		if (secure_mutex(&p->forks[i].m_fork, INIT))
			return (false);
		p->forks[i].initialized = true;
		p->forks[i].debug_fork_id = i + 1;
		p->forks[i].available = true;
		i++;
	}
	if (secure_mutex(&p->m_params, INIT))
		return (false);
	if (secure_mutex(&p->m_print, INIT))
	{
		secure_mutex(&p->m_params, DESTROY);
		return (false);
	}
	return (true);
}

static void	assign_forks(t_philo *philo, t_fork *forks, int i)
{
	int	x_philos;

	x_philos = philo->params->x_philos;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[i];
		philo->second_fork = &forks[(i + 1) % x_philos];
	}
	else
	{
		philo->first_fork = &forks[(i + 1) % x_philos];
		philo->second_fork = &forks[i];
	}
}

bool	init_philo(t_params *p, int i)
{
	t_philo	*philo;

	while (i < p->x_philos)
	{
		philo = p->philos + i;
		philo->id = i + 1;
		philo->still_hungry = true;
		philo->meals_count = 0;
		philo->params = p;
		philo->t_last_meal = 0;
		philo->is_eating = false;
		if (secure_mutex(&p->philos[i].m_philo, INIT))
			return (false);
		philo->m_initialized = true;
		assign_forks(philo, p->forks, i);
		set_long(&philo->m_philo, &philo->t_last_meal, 0);
		i++;
	}
	return (true);
}
