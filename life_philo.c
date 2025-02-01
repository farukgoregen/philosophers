/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:44:16 by omgorege          #+#    #+#             */
/*   Updated: 2025/02/01 16:14:21 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void    eating(t_philo *philo)
{
    
}

void    *life_cycle(void *arg)
{
    t_philo *philo;

    philo = (t_philo*)arg;
    while(1)
    {
        eating(philo);
    }
    return (NULL);
}
void    start_phlosop(t_general *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philo)
    {
        pthread_create(&data->philo[i].thread,NULL, life_cycle, &data->philo[i]);
        i++;
    }
}