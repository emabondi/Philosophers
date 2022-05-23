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
	int		count;
	t_rules	*rules;
	long long	temp;

	rules = r;
	while(1)
	{
		i = 0;
		count = 0;
		temp = get_time() - rules->start_time;
		while (i < rules->n_ph)
		{
			if (temp - rules->philo[i].last_meal > rules->time_death)
			{
				print_msg(&rules->philo[i], "died");
				rules->finish = 1;
				return (0);
			}
			if (rules->philo[i].philo_finish == 1)
				count++;
			i++;
		}
		if (count == rules->n_ph)
		{
			rules->finish = 1;
			break ;
		}
	}
	return (0);
}

void	ft_wait(long long wait_time)
{
	long long	start_time;

	start_time = get_time();
	usleep(wait_time * 1000 - 20000);
	while (get_time() < start_time + wait_time)
		continue ;
}

//void	take_forks(t_philo *philo)
//{
//	pthread_mutex_lock(philo->right);
//	print_msg(philo->rules->start_time, philo->id, &philo->rules->write, "has taken a fork");
//	pthread_mutex_lock(philo->left);
//	print_msg(philo->rules->start_time, philo->id, &philo->rules->write, "has taken a fork");
//}

void	*ft_thread(void *philo)
{
	t_philo *ph;

	ph = philo;
	ph->last_meal = get_time() - ph->rules->start_time;
	if (ph->id % 2 == 0)
		ft_wait(ph->rules->time_eat);
	while (ph->rules->finish == 0)
	{
		pthread_mutex_lock(ph->left);
		print_msg(ph, "has taken a fork");
		if (ph->rules->n_ph == 1)
			break ;
		pthread_mutex_lock(ph->right);
		print_msg(ph, "has taken a fork");
		//take_forks(ph);
		print_msg(ph, "is eating");
		ph->n_eat++;
		if (ph->n_eat == ph->rules->nb_must_eat)
			ph->philo_finish = 1;
		ph->last_meal = get_time() - ph->rules->start_time;
		ft_wait(ph->rules->time_eat);
		pthread_mutex_unlock(ph->right);
		pthread_mutex_unlock(ph->left);
		if (ph->rules->finish == 1)
			break ;
		print_msg(ph, "is sleeping");
		ft_wait(ph->rules->time_sleep);
		print_msg(ph, "is thinking");
	}
	return (NULL);
}

void	ft_exit(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	pthread_join(rules->monitoring_thread, NULL);
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->write);
	free(rules->forks);
	free(philo);
}

void	ft_threadmaker(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	rules->start_time = get_time();
	pthread_create(&rules->monitoring_thread, NULL, monitoring, rules);
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_create(&philo[i].thread, NULL, ft_thread, &philo[i]);
		i++;
	}
	ft_exit(rules);
}
