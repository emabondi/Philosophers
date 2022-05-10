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

#include "philo.h"

void	wait(uint16_t wait_time)
{
	u_int16_t	start_time
	usleep(wait_time * 1000)
	while ()
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	print_msg(philo->rules->start_time, philo->id, &philo->rules->write, "has taken a fork");
	pthread_mutex_lock(philo->right);
	print_msg(philo->rules->start_time, philo->id, &philo->rules->write, "has taken a fork");
}

void	*ft_thread(void *philo)
{
	t_philo *ph;

	ph = philo;
	if (ph->id % 2 == 0)
		usleep(ph->rules->time_eat * 1000); 
	while (ph->rules->finish == 0)
	{
		take_forks(ph);
		print_msg(ph->rules->start_time, ph->id, &ph->rules->write, "is eating");
		wait(ph->rules->time_eat)
	}
	return (philo);
}

void	ft_threadmaker(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_create(&philo[i].thread, NULL, ft_thread, &philo[i]);
		i++;
	}
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
