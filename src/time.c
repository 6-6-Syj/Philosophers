/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 19:10:44 by jmagand           #+#    #+#             */
/*   Updated: 2025-04-11 19:10:44 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *philo)
{
	long	current_time;
	long	t_die;

	t_die = philo->params->t_die;
	current_time = get_elapsed_time(philo->params);
	if (!get_bool(&philo->m_philo, &philo->still_hungry)
		|| get_bool(&philo->m_philo, &philo->is_eating))
		return (false);
	return ((current_time - get_long(&philo->m_philo,
				&philo->t_last_meal)) >= t_die);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_elapsed_time(t_params *p)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec * 0.001) - get_long(&p->m_params,
			&p->t_start));
}

void	ft_usleep(t_params *p, long milliseconds)
{
	long	start;
	long	elapsed;

	start = get_time();
	while ("elapsed < milliseconds")
	{
		elapsed = get_time() - start;
		if (elapsed >= milliseconds || is_simulation_finished(p))
			break ;
		usleep(100);
	}
}
