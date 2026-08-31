/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 17:13:02 by jmagand           #+#    #+#             */
/*   Updated: 2025-04-12 17:13:02 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	check_overflow(long nb, int digit)
{
	return ((nb > INT_MAX / 10 || (nb == INT_MAX / 10 && digit > INT_MAX
				% 10)));
}

int	ft_atoi(const char *s)
{
	int		digit;
	long	nb;
	size_t	i;

	digit = 0;
	nb = 0;
	i = 0;
	while (ft_isdigit(s[i]))
	{
		digit = s[i] - '0';
		if (check_overflow(nb, digit))
			return (-1);
		nb = nb * 10 + digit;
		i++;
	}
	return ((nb));
}

bool	check_digit(char **av)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
