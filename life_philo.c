/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:44:16 by omgorege          #+#    #+#             */
/*   Updated: 2025/06/28 14:45:02 by omgorege         ###   ########.fr       */
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
	philo->last_meal_time = get_ms() - philo->data->start_time;
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->data->n);
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
	pthread_mutex_unlock(philo->data->n);
	ms_usleep(philo->data->sleeping_time);
}

void	*life_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(philo->data->n);
		if (philo->data->is_finish)
		{
			pthread_mutex_unlock(philo->data->n);
			break ;
		}
		if (philo->data->nmeals != -1
			&& philo->meals_eaten >= philo->data->nmeals)
		{
			pthread_mutex_unlock(philo->data->n);
			break ;
		}
		pthread_mutex_unlock(philo->data->n);
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}

void	start_phlosop(t_general *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, life_cycle,
			&data->philo[i]);
		usleep(100);
		i++;
	}
}
