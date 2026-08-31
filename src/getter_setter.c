/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 15:55:27 by jmagand           #+#    #+#             */
/*   Updated: 2025-04-12 15:55:27 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	ret;

	secure_mutex(mutex, LOCK);
	ret = *value;
	secure_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	secure_mutex(mutex, LOCK);
	*dest = value;
	secure_mutex(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	secure_mutex(mutex, LOCK);
	ret = *value;
	secure_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	secure_mutex(mutex, LOCK);
	*dest = value;
	secure_mutex(mutex, UNLOCK);
}

bool	is_simulation_finished(t_params *p)
{
	return (get_bool(&p->m_params, &p->end_simulation));
}
