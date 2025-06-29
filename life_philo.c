/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:44:16 by omgorege          #+#    #+#             */
/*   Updated: 2025/06/29 16:59:51 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	if (life_philo_break(philo) == 1)
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		if (life_philo_break(philo) == 1)
		{
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		if (life_philo_break(philo) == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		pthread_mutex_lock(philo->right_fork);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	if (take_forks(philo) == 1)
		return (1);
	if (life_philo_break(philo) == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->data->n);
	if (!philo->data->is_finish)
	{
		printf("%lu %d has taken a fork\n", get_ms() - philo->data->start_time,
			philo->id);
		printf("%lu %d has taken a fork\n", get_ms() - philo->data->start_time,
			philo->id);
		printf("%lu %d is eating\n", get_ms() - philo->data->start_time,
			philo->id);
		philo->last_meal_time = get_ms() - philo->data->start_time;
		philo->meals_eaten++;
	}
	pthread_mutex_unlock(philo->data->n);
	ms_usleep(philo->data->eating_time);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (life_philo_break(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->data->n);
	if (!philo->data->is_finish)
		printf("%lu %d is thinking\n", get_ms() - philo->data->start_time,
			philo->id);
	pthread_mutex_unlock(philo->data->n);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (life_philo_break(philo) == 1)
		return (1);
	pthread_mutex_lock(philo->data->n);
	if (!philo->data->is_finish)
		printf("%lu %d is sleeping\n", get_ms() - philo->data->start_time,
			philo->id);
	pthread_mutex_unlock(philo->data->n);
	ms_usleep(philo->data->sleeping_time);
	return (0);
}

void	*life_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (thinking(philo) == 1)
			break ;
		if (eating(philo) == 1)
			break ;
		if (sleeping(philo) == 1)
			break ;
	}
	return (NULL);
}
