/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:38:00 by omgorege          #+#    #+#             */
/*   Updated: 2025/02/01 15:18:16 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void printsss(t_general *data)
{
    printf("%d\n",data->number_of_philo);
    printf("%d\n",data->death_time);
    printf("%d\n",data->eating_time);
    printf("%d\n",data->sleeping_time);
    printf("%d\n",data->nmeals);
}

int main(int ac, char **av)
{
    t_general *data;

    if(ac < 4 || control_philo(&av[1]) == -1)
        return (-1);
    data = malloc(sizeof(t_general *));
    add_philo(&av[1], data);
    init_philosop(data);
    start_phlosop(data);
    printsss(data);
}