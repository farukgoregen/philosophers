/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:38:00 by omgorege          #+#    #+#             */
/*   Updated: 2025/02/22 14:25:06 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pthread_free(t_general *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(data->n);
	free(data);
}

unsigned long	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

void	ms_usleep(size_t ms)
{
	size_t	timeing;

	timeing = get_ms();
	while (get_ms() - timeing < ms)
	{
		usleep(100);
	}
}

int	philo_dead_check(t_general *data, int a)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philo)
	{
		pthread_mutex_lock(data->n);
		if ((get_ms() - data->start_time)
			- data->philo[i].last_meal_time > data->death_time)
		{
			data->philo[i].dead = 1;
			data->is_finish = 1;
		}
		pthread_mutex_unlock(data->n);
		pthread_mutex_lock(data->n);
		if (data->philo[i].meals_eaten == data->nmeals)
			a++;
		pthread_mutex_unlock(data->n);
		if (data->is_finish == 1 || a == data->number_of_philo)
		{
			if (data->philo[i].dead == 1)
			{
				pthread_mutex_lock(data->n);
				printf("%lu %d died\n", (get_ms() - data->start_time),
					data->philo[i].id);
				pthread_mutex_unlock(data->n);
			}
			return (-1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_general *data;
	int a;
	int b;
	if ((ac < 5 && ac < 6) || control_philo(&av[1]) == -1)
		return (-1);
	data = malloc(sizeof(t_general));
	add_philo(&av[1], data);
	init_philosop(data);
	start_phlosop(data);
	a = -1;
	while (1)
	{
		b = 0;
		if (philo_dead_check(data, b) == -1)
		{
			return (1);
		}
	}
	while (++a < data->number_of_philo)
	{
		pthread_join(data->philo[a].thread, (void *)&data->philo[a]);
	}
}