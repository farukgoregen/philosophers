/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:44:16 by omgorege          #+#    #+#             */
/*   Updated: 2025/02/04 15:00:27 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->data->dead);
	printf("%d took the left fork\n", philo->id);
	pthread_mutex_unlock(philo->data->dead);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->data->dead);
	printf("%d took the right fork\n", philo->id);
	printf("%d is eating\n", philo->id);
	pthread_mutex_unlock(philo->data->dead);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	usleep(philo->data->eating_time * 1000);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->data->dead);
	printf("%d is thinking\n", philo->id);
	pthread_mutex_unlock(philo->data->dead);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->data->dead);
	printf("%d is sleeping\n", philo->id);
	pthread_mutex_unlock(philo->data->dead);
	usleep(philo->data->sleeping_time * 1000);
}

void	*life_cycle(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
void	start_phlosop(t_general *data)
{
	int i;

	i = 0;
	while (i < data->number_of_philo)
	{
        pthread_mutex_init(&data->forks[i], NULL);
		pthread_create(&data->philo[i].thread, NULL, life_cycle,
			&data->philo[i]);
		i++;
	}
}