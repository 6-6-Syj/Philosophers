/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 13:16:19 by jmagand           #+#    #+#             */
/*   Updated: 2025-04-12 13:16:19 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	secure_mutex(pthread_mutex_t *mutex, t_e_m_op op)
{
	if (op == INIT)
	{
		if (pthread_mutex_init(mutex, NULL))
			return (ft_write(2, R FAIL_M_INIT RST, 1));
	}
	else if (op == DESTROY)
	{
		if (pthread_mutex_destroy(mutex))
			return (ft_write(2, R FAIL_M_DESTROY RST, 1));
	}
	else if (op == LOCK)
	{
		if (pthread_mutex_lock(mutex))
			return (ft_write(2, R FAIL_M_LOCK RST, 1));
	}
	else if (op == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex))
			return (ft_write(2, R FAIL_M_UNLOCK RST, 1));
	}
	return (false);
}

void	increment_long(pthread_mutex_t *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

static int	ft_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

bool	ft_write(int fd, char *s, bool ret)
{
	int	len;

	len = ft_len(s);
	write(fd, s, len);
	write(fd, "\n", 1);
	return (ret);
}
