/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 20:31:15 by jmagand           #+#    #+#             */
/*   Updated: 2025-04-12 20:31:15 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_philos(t_params *p)
{
	long	start_time;
	int		i;

	i = 0;
	increment_long(&p->m_params, &p->x_philos_rdy);
	if (get_long(&p->m_params, &p->x_philos_rdy) == p->x_philos)
	{
		set_bool(&p->m_params, &p->philos_ready, true);
		start_time = get_time();
		set_long(&p->m_params, &p->t_start, start_time);
		while (i < p->x_philos)
		{
			set_long(&p->philos[i].m_philo, &p->philos[i].t_last_meal,
				start_time);
			i++;
		}
		set_long(&p->m_params, &p->x_philos_rdy, 0);
	}
	while (!get_bool(&p->m_params, &p->philos_ready) && !get_bool(&p->m_params,
			&p->end_simulation))
		usleep(50);
}

bool	join_philosophers(t_params *p)
{
	int		i;
	long	x_created;

	i = 0;
	x_created = get_long(&p->m_params, &p->x_philos_created);
	while (i < x_created)
	{
		if (pthread_join(p->philos[i].thread, NULL))
			return (ft_write(2, R FAIL_THR_JOIN RST, 0));
		i++;
	}
	return (true);
}

static void	*alive(void *arg)
{
	t_philo		*philo;
	t_params	*p;

	philo = (t_philo *)arg;
	p = philo->params;
	wait_philos(p);
	increment_long(&p->m_params, &p->x_philos_rdy);
	if (philo->id % 2 == 0)
		ft_usleep(p, (p->t_eat / 2));
	set_long(&philo->m_philo, &philo->t_last_meal, get_time()
		- get_long(&philo->params->m_params, &philo->params->t_start));
	while (!is_simulation_finished(p))
	{
		lets_eat(philo);
		if (!get_bool(&philo->m_philo, &philo->still_hungry))
			break ;
		lets_sleep(philo);
		lets_think(philo);
	}
	return (NULL);
}

static void	*alone_alive(void *arg)
{
	t_philo		*philo;
	t_params	*p;

	philo = (t_philo *)arg;
	p = philo->params;
	increment_long(&p->m_params, &p->x_philos_rdy);
	print_action(philo, TAKE_FIRST);
	while (!is_simulation_finished(p))
		usleep(200);
	return (NULL);
}

bool	create_philosophers(t_params *p, int i)
{
	if (get_long(&p->m_params, &p->x_philos) == 1)
	{
		if (pthread_create(&p->philos[0].thread, NULL, alone_alive,
				&p->philos[0]))
			return (ft_write(2, R FAIL_THR_CREATE RST, 0));
		p->x_philos_created = 1;
	}
	else
	{
		while (i < get_long(&p->m_params, &p->x_philos))
		{
			if (pthread_create(&p->philos[i].thread, NULL, alive,
					&p->philos[i]))
				return (ft_write(2, R FAIL_THR_CREATE RST, 0));
			i++;
			set_long(&p->m_params, &p->x_philos_created, i);
		}
	}
	return (true);
}
