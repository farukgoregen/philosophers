/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:44:16 by omgorege          #+#    #+#             */
/*   Updated: 2025/02/09 16:09:08 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->data->n);
	printf("%lu %d has taken a fork\n", get_ms() - philo->data->start_time,
		philo->id);
	pthread_mutex_unlock(philo->data->n);
	pthread_mutex_lock(philo->data->n);
	printf("%lu %d has taken a fork\n", get_ms() - philo->data->start_time,
		philo->id);
	printf("%lu %d is eating\n", get_ms() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->data->n);
	philo->last_meal_time = get_ms() - philo->data->start_time;
	philo->meals_eaten++;
	ms_usleep(philo->data->eating_time);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->data->n);
	printf("%lu %d is thinking\n", get_ms() - philo->data->start_time,
		philo->id);
	pthread_mutex_unlock(philo->data->n);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->data->n);
	printf("%lu %d is sleeping\n", get_ms() - philo->data->start_time,
		philo->id);
	ms_usleep(philo->data->sleeping_time);
	pthread_mutex_unlock(philo->data->n);
}

void	*life_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while(!(philo->data->is_read))
		continue;
	while (1)
	{
		if(philo->id % 2 == 0)
		{
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
		else
		{
			sleeping(philo);
			thinking(philo);
			eating(philo);
		}
	}
	return (NULL);
}
void	start_phlosop(t_general *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, life_cycle,
			&data->philo[i]);
		i++;
	}
}