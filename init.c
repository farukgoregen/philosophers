/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:23:31 by omgorege          #+#    #+#             */
/*   Updated: 2025/06/28 14:17:01 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	add_philo(char **str, t_general *data)
{
	int	j;

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
		if (str[4] == NULL)
		{
			data->philo_eat_number = -1;
			data->nmeals = -1;
		}
		else if (j == 4)
		{
			data->philo_eat_number = 0;
			data->nmeals = ft_atoi(str[j]);
		}
		j++;
	}
}

void	init_philosop(t_general *data)
{
	int		i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->number_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	data->n = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->n, NULL);
	while (i < data->number_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1)
			% data->number_of_philo];
		data->philo[i].data = data;
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal_time = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->start_time = get_ms();
	data->is_finish = 0;
}
