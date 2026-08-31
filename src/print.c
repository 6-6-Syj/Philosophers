/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 16:24:40 by jmagand           #+#    #+#             */
/*   Updated: 2025-04-12 16:24:40 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, t_status status)
{
	long	elapsed;

	secure_mutex(&philo->params->m_print, LOCK);
	elapsed = get_time() - get_long(&philo->params->m_params,
			&philo->params->t_start);
	if (is_simulation_finished(philo->params) && status != DIED)
	{
		secure_mutex(&philo->params->m_print, UNLOCK);
		return ;
	}
	if (status == TAKE_FIRST || status == TAKE_SECOND)
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING)
		printf("%ld %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING)
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING)
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%ld %d died\n", elapsed, philo->id);
	secure_mutex(&philo->params->m_print, UNLOCK);
}
