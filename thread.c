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
	while(1)
	{
		i = 0;
		while (i < rules->n_ph)
		{
			if (rules->philo_finish == rules->n_ph)
				exit (0);
			else if (get_time() - (rules->start_time + rules->philo[i].last_meal) >= (uint64_t)rules->time_death)
			{
				//printf("\ntime:%llu, start_time:%llu, last_meal:%llu\n", get_time(), rules->start_time, rules->philo[i].last_meal);
				//printf("philo1last_eat:%llu, philo2last_eat:%llu, philo3last_eat:%llu", rules->philo[0].last_meal, rules->philo[1].last_meal, rules->philo[2].last_meal);
				pthread_mutex_lock(&rules->write);
				printf ("%llu %d %s\n",  get_time() - rules->start_time, rules->philo[i].id, "died");
				exit (0) ;
			}
			i++;
		}
	}
	return (0);
}

void	ft_wait(uint64_t wait_time)
{
	u_int64_t	start_time;

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
		usleep(ph->rules->time_eat * 100);
	while (1)
	{
		take_forks(ph);
		print_msg(ph->rules->start_time, ph->id, &ph->rules->write, "is eating");
		ph->last_meal = get_time() - ph->rules->start_time;
		ph->n_eat++;
		if (ph->n_eat == ph->rules->nb_must_eat)
			ph->rules->philo_finish++;
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
