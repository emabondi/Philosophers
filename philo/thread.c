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

int	ft_monitor2(t_rules *rules, t_philo *ph, int *count)
{
	int			i;
	long long	temp;

	i = 0;
	while (i < rules->n_ph)
	{
		pthread_mutex_lock(&rules->time);
		temp = get_time() - rules->start_time - ph[i].last_meal;
		pthread_mutex_unlock(&rules->time);
		if (temp > rules->time_death)
		{
			print_msg(&ph[i], "died");
			pthread_mutex_lock(&rules->finish_lock);
			rules->finish_flag = 0;
			pthread_mutex_unlock(&rules->finish_lock);
			return (1);
		}
		if (check_mutex(1, &ph[i]))
			(*count)++;
		i++;
	}
	return (0);
}

void	ft_monitor(t_rules *rules)
{
	int			count;
	t_philo		*ph;

	ph = rules->philo;
	while (1)
	{
		count = 0;
		if (ft_monitor2(rules, ph, &count) == 1)
			return ;
		if (count == rules->n_ph)
		{
			pthread_mutex_lock(&rules->finish_lock);
			rules->finish_flag = 0;
			pthread_mutex_unlock(&rules->finish_lock);
		}
	}
}

void	ft_thread2(t_philo *ph)
{
	if (ph->n_eat == ph->rules->nb_must_eat)
	{
		pthread_mutex_lock(&ph->eat_lock);
		ph->eat_flag = 1;
		pthread_mutex_unlock(&ph->eat_lock);
	}
	pthread_mutex_unlock(&ph->rules->finish_lock);
	pthread_mutex_lock(&ph->rules->time);
	ph->last_meal = get_time() - ph->rules->start_time;
	pthread_mutex_unlock(&ph->rules->time);
	ft_wait(ph->rules->time_eat);
	pthread_mutex_unlock(ph->right);
	pthread_mutex_unlock(ph->left);
	print_msg(ph, "is sleeping");
	ft_wait(ph->rules->time_sleep);
	print_msg(ph, "is thinking");
}

void	*ft_thread(void *philo)
{
	t_philo	*ph;

	ph = philo;
	pthread_mutex_lock(&ph->rules->time);
	ph->last_meal = get_time() - ph->rules->start_time;
	pthread_mutex_unlock(&ph->rules->time);
	if (ph->id % 2 == 0)
		ft_wait(ph->rules->time_eat);
	while (check_mutex(0, ph))
	{
		pthread_mutex_lock(ph->left);
		print_msg(ph, "has taken a fork");
		if (ph->rules->n_ph == 1)
			break ;
		pthread_mutex_lock(ph->right);
		print_msg(ph, "has taken a fork");
		print_msg(ph, "is eating");
		pthread_mutex_lock(&ph->rules->finish_lock);
		ph->n_eat++;
		ft_thread2(ph);
	}
	return (NULL);
}

void	ft_threadmaker(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	rules->start_time = get_time();
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_create(&philo[i].thread, NULL, ft_thread, &philo[i]);
		i++;
	}
	ft_monitor(rules);
	ft_exit(rules);
}
