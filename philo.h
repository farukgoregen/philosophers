/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:44:00 by omgorege          #+#    #+#             */
/*   Updated: 2025/02/04 14:52:41 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philo
{
    int             id;
    long            last_meal_time;
    int             meals_eaten;
    pthread_t   thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_general *data;
}               t_philo;

typedef struct s_general
{
    int     number_of_philo;
    int     death_time;
    int     eating_time;
    int     sleeping_time;
    int     nmeals;
    pthread_mutex_t *forks;
    pthread_mutex_t *dead;
    struct s_philo *philo;
}       t_general;

void    add_philo(char  **str, t_general *data);
int    control_philo(char **str);
long	ft_atoi(char *str);
void printsss(t_general *data);
void init_philosop(t_general *data);
void    start_phlosop(t_general *data);
void    *life_cycle(void *arg);
void eating(t_philo *philo);
void thinking(t_philo *philo);
void sleeping(t_philo *philo);
#endif