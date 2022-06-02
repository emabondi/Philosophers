/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:11:16 by ebondi            #+#    #+#             */
/*   Updated: 2022/04/25 11:11:16 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_wait(long long wait_time)
{
	long long	start_time;

	start_time = get_time();
	usleep(wait_time * 1000 - 20000);
	while (get_time() < start_time + wait_time)
		continue ;
}


void	philo_process(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->rules->forks);
		print_msg(philo, "has taken a fork");
		sem_wait(philo->rules->forks);
		print_msg(philo, "has taken a fork");
		print_msg(philo, "is eating");

		philo->last_meal = get_time() - philo->rules->start_time;
		ft_wait(philo->rules->time_eat);
		sem_post(philo->rules->forks);
		sem_post(philo->rules->forks);
		print_msg(philo, "is sleeping");
		ft_wait(philo->rules->time_sleep);
		print_msg(philo, "is thinking");
	}
}

void	ft_philomaker(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	
	rules->start_time = get_time();
	i = 0;
	while (i < rules->n_ph)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			philo_process(&philo[i]);
		i++;
	}
}
