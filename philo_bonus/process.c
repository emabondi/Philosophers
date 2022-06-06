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

//void	*eat_monitor(void *ru)
//{
//	t_rules	*rules;
//	int		i;

//	rules = ru;
//	i = 0;
//	while (i < rules->n_ph)
//	{
//		sem_wait(rules->must_eat);
//		i++;
//	}
//	sem_wait(rules->finish);
//	i = -1;
//	while (++i < rules->n_ph)
//		kill(rules->philo[i].pid, SIGKILL);
//	//write (1, "FINITO\n", 7);
//	exit (0);
//}

void	*monitor(void *philo)
{
	t_philo	*ph;

	ph = philo;
	while (!ph->rules->dead)
	{
		if (get_time() - ph->rules->start_time - ph->last_meal > ph->rules->time_death)
		{
			philo_dead(ph);
			break ;
		}
		if (ph->rules->nb_must_eat != -1 && ph->n_eat == ph->rules->nb_must_eat)
		{
			ph->rules->dead = 1;
			if (ph->id != ph->rules->n_ph)
				ft_wait((ph->rules->time_eat + ph->rules->time_sleep) *2);
			break ;
		}
		usleep(100);
	}
	if(ph->rules->dead)
		exit (1);
	else
		exit (0);
	return (NULL);
}

void	*philo_process(t_philo *philo)
{
	pthread_t	thread;
	
	pthread_create(&thread, NULL, monitor, philo);
	if (philo->id == philo->rules->n_ph)
		ft_wait(philo->rules->time_eat - 10);
	while (1)
	{
		sem_wait(philo->rules->forks);
		print_msg(philo, "has taken a fork");
		sem_wait(philo->rules->forks);
		print_msg(philo, "has taken a fork");
		print_msg(philo, "is eating");
		philo->last_meal = get_time() - philo->rules->start_time;
		philo->n_eat++;
		if(philo->n_eat == philo->rules->nb_must_eat)
			sem_post(philo->rules->must_eat);
		ft_wait(philo->rules->time_eat);
		sem_post(philo->rules->forks);
		sem_post(philo->rules->forks);
		print_msg(philo, "is sleeping");
		ft_wait(philo->rules->time_sleep);
		print_msg(philo, "is thinking");
	}
	pthread_join(thread, NULL);
	return (NULL);
}

void	ft_philomaker(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	//pthread_create(&philo->finish_eat, NULL, eat_monitor, rules);
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
