/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 11:49:57 by omgorege          #+#    #+#             */
/*   Updated: 2025/02/22 14:28:15 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
long	ft_atoi(char *str)
{
	size_t	i;
	int		j;
	long	s;

	j = 1;
	i = 0;
	s = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		s = s * 10 + (str[i] - 48);
		i++;
	}
	return (s * j);
}

int	control_philo(char **str)
{
	int j;
	int i;

	j = 0;
	while (str[j])
	{
		if (ft_atoi(str[j]) <= 0 || ft_atoi(str[0]) > 200)
			return (-1);
		j++;
	}
	j = 0;
	while (str[j])
	{
		i = 0;
		while (str[j][i])
		{
			if (ft_isdigit(str[j][i]) == 0)
				return (-1);
			i++;
		}
		j++;
	}
	return (0);
}