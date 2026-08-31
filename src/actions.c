/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 14:54:04 by jmagand           #+#    #+#             */
/*   Updated: 2025-04-12 14:54:04 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lets_think(t_philo *philo)
{
	t_params	*p;

	p = philo->params;
	print_action(philo, THINKING);
	if (p->x_philos % 2 != 0)
		ft_usleep(p, p->t_eat * 2 - p->t_sleep);
}

void	lets_sleep(t_philo *philo)
{
	print_action(philo, SLEEPING);
	ft_usleep(philo->params, philo->params->t_sleep);
}

void	lets_eat(t_philo *philo)
{
	while (!get_bool(&philo->first_fork->m_fork, &philo->first_fork->available))
		usleep(50);
	set_bool(&philo->first_fork->m_fork, &philo->first_fork->available, false);
	print_action(philo, TAKE_FIRST);
	while (!get_bool(&philo->second_fork->m_fork,
			&philo->second_fork->available))
		usleep(50);
	set_bool(&philo->second_fork->m_fork, &philo->second_fork->available,
		false);
	print_action(philo, TAKE_SECOND);
	set_bool(&philo->m_philo, &philo->is_eating, true);
	set_long(&philo->m_philo, &philo->t_last_meal,
		get_elapsed_time(philo->params));
	increment_long(&philo->m_philo, &philo->meals_count);
	print_action(philo, EATING);
	if (philo->params->t_eat > philo->params->t_die)
		ft_usleep(philo->params, philo->params->t_die);
	else
		ft_usleep(philo->params, philo->params->t_eat);
	set_bool(&philo->m_philo, &philo->is_eating, false);
	if (philo->params->x_meals && get_long(&philo->m_philo,
			&philo->meals_count) == philo->params->x_meals)
		set_bool(&philo->m_philo, &philo->still_hungry, false);
	set_bool(&philo->first_fork->m_fork, &philo->first_fork->available, true);
	set_bool(&philo->second_fork->m_fork, &philo->second_fork->available, true);
}

bool	start_simulation(t_params *p)
{
	if (!create_philosophers(p, 0))
	{
		set_bool(&p->m_params, &p->end_simulation, true);
		usleep(1000);
		return (false);
	}
	if (!create_watcher(p))
	{
		set_bool(&p->m_params, &p->end_simulation, true);
		return (false);
	}
	if (!join_philosophers(p))
	{
		set_bool(&p->m_params, &p->end_simulation, true);
		if (p->watcher_created)
			if (pthread_join(p->watcher, NULL))
				return (ft_write(2, R FAIL_THR_JOIN RST, 0));
		return (false);
	}
	set_bool(&p->m_params, &p->end_simulation, true);
	return (true);
}
