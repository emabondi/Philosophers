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

void	*monitoring(void *r)
{
	int		i;
	t_rules	*rules;

	rules = r;
	i = 0;
	while(rules->finish == 0)
	{
		//printf("\nms_ultima_mangiata%llu, time_death:%d\n", (((get_time() - rules->start_time) - rules->philo[i].last_meal)), (uint16_t)rules->time_death);
		if (get_time() - (rules->start_time + rules->philo[i].last_meal) >= (uint16_t)rules->time_death)
		{
			printf("\ntime:%llu, start_time:%llu, last_meal:%llu\n", get_time(), rules->start_time, rules->philo[i].last_meal);
			rules->finish = 1;
			print_msg(rules->start_time, rules->philo[i].id, &rules->write, "died");
			exit (0);
		}
		i++;
		if (i == rules->n_ph)
			i = 0;
	}
	return (0);
}

void	ft_wait(uint16_t wait_time)
{
	u_int16_t	start_time;

	start_time = get_time();
	usleep(wait_time * 1000 - 20000);
	while (get_time() < start_time + wait_time)
		continue ;
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
		ph->last_meal = get_time() - ph->rules->start_time;
		ft_wait(ph->rules->time_eat);
		pthread_mutex_unlock(ph->left);
		pthread_mutex_unlock(ph->right);
		print_msg(ph->rules->start_time, ph->id, &ph->rules->write, "is sleeping");
		ft_wait(ph->rules->time_sleep);
		print_msg(ph->rules->start_time, ph->id, &ph->rules->write, "is thinking");
	}
	return (philo);
}

void	ft_threadmaker(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	pthread_create(&rules->monitoring_thread, NULL, monitoring, rules);
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
