/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:38:00 by omgorege          #+#    #+#             */
/*   Updated: 2025/02/06 14:26:23 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
unsigned long	get_ms(void)
{
    struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000 + tv.tv_sec * 1000);
}

void    philo_dead_check(t_philo *philo)
{
    if(get_ms()- philo->last_meal_time > philo->data->death_time)
        philo->dead = 1;
}

int main(int ac, char **av)
{
    t_general *data;
    if(ac < 5 || ac < 6 || control_philo(&av[1]) == -1)
        return (-1);
    data = malloc(sizeof(t_general));
    
    add_philo(&av[1], data);
    
    init_philosop(data);
    start_phlosop(data);
}