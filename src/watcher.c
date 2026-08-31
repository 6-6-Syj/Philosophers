/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 20:35:43 by jmagand           #+#    #+#             */
/*   Updated: 2025-04-12 20:35:43 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	are_all_philos_ready(t_params *p)
{
	return (get_long(&p->m_params, &p->x_philos_rdy) == p->x_philos);
}

static void	*watch_philos(void *arg)
{
	t_params	*p;
	int			i;

	p = (t_params *)arg;
	while (!is_simulation_finished(p))
	{
		i = 0;
		while (i < p->x_philos && !is_simulation_finished(p))
		{
			if (is_dead(p->philos + i))
			{
				set_bool(&p->m_params, &p->end_simulation, true);
				print_action(p->philos + i, DIED);
				return (NULL);
			}
			i++;
		}
		usleep(p->t_eat * 2);
	}
	return (NULL);
}

bool	create_watcher(t_params *p)
{
	if (pthread_create(&p->watcher, NULL, watch_philos, &p->watcher))
		return (ft_write(2, FAIL_THR_CREATE, 0));
	set_bool(&p->m_params, &p->watcher_created, true);
	return (true);
}
