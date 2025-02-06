/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omgorege <omgorege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:44:00 by omgorege          #+#    #+#             */
/*   Updated: 2025/02/06 12:21:36 by omgorege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
    int             id;
    long            last_meal_time;
    int             meals_eaten;
    int             dead;
    pthread_t   thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_general *data;
}               t_philo;

typedef struct s_general
{
    int     number_of_philo;
    long unsigned    death_time;
    int     eating_time;
    int     sleeping_time;
    int     nmeals;
    unsigned long     start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t *n;
    struct timeval		tv;
    struct s_philo *philo;
}       t_general;

void    add_philo(char  **str, t_general *data);
int    control_philo(char **str);
long	ft_atoi(char *str);
void init_philosop(t_general *data);
void    start_phlosop(t_general *data);
void    *life_cycle(void *arg);
void eating(t_philo *philo);
void thinking(t_philo *philo);
void sleeping(t_philo *philo);
unsigned long	get_ms(t_general *p);
void    philo_dead_check(t_philo *philo);
#endif