/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:44:16 by omgorege          #+#    #+#             */
/*   Updated: 2025/02/06 14:44:16 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->data->n);
	printf("%d %lu took the left fork\n", philo->id, get_ms() - philo->data->start_time);
	pthread_mutex_unlock(philo->data->n);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->data->n);
	printf("%d %lu took the right fork\n", philo->id, get_ms() - philo->data->start_time);
	printf("%d %lu is eating\n", philo->id, get_ms() - philo->data->start_time);
	pthread_mutex_unlock(philo->data->n);
	philo->last_meal_time = get_ms() - philo->data->start_time;
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->data->n);
	printf("%d is thinking\n", philo->id);
	pthread_mutex_unlock(philo->data->n);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->data->n);
	printf("%d is sleeping\n", philo->id);
	pthread_mutex_unlock(philo->data->n);
}

void	*life_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		philo_dead_check(philo);
		if (philo->dead == 1)
		{
			printf("%d philo dead\n", philo->id);
			break ;
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