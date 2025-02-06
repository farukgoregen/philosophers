/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_and_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:23:31 by omgorege          #+#    #+#             */
/*   Updated: 2025/02/06 14:25:17 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int    control_philo(char **str)
{
    int j;

    j = 0;
    while (str[j])
    {
        if (ft_atoi(str[j]) <= 0)
            return (-1);

        j++;
    }
    return 0;
}

void    add_philo(char  **str, t_general *data)
{
    int j;

    j = 0;
    while (str[j])
    {
        if (j == 0)
            data->number_of_philo = ft_atoi(str[j]);
        else if (j == 1)
            data->death_time = ft_atoi(str[j]);
        else if (j == 2)
            data->eating_time = ft_atoi(str[j]);
        else if (j == 3)
            data->sleeping_time = ft_atoi(str[j]);
        else if (j == 4)
            data->nmeals = ft_atoi(str[j]);
        j++;
    }
}

void init_philosop(t_general *data)
{
    int i;

    data->philo = malloc(sizeof(t_philo) * data->number_of_philo);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
    data->n = malloc(sizeof(pthread_mutex_t));
    i = 0;
    pthread_mutex_init(data->n, NULL);
    while(i < data->number_of_philo)
    {
        data->philo[i].id = i + 1;
        data->philo[i].left_fork = &data->forks[i];
        data->philo[i].right_fork = &data->forks[(i + 1) % data->number_of_philo];
        data->philo[i].data = data;
        data->philo[i].meals_eaten = 0;
        data->philo[i].last_meal_time = 0;
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    data->start_time = get_ms();
}