/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:24:07 by ebondi            #+#    #+#             */
/*   Updated: 2022/04/11 18:24:07 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isnumeric(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while ((argv[i][j] >= 9 && argv[i][j] <= 13) || argv[i][j] == 32)
			j++;
		if (argv[i][j] == '+')
			j++;
		if (argv[i][j] == '\0')
			return (0);
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	res;

	i = 0;
	s = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			s *= -1;
		i += 1;
	}
	if (str[i] == 43 || str[i] == 45)
		return (0);
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = ((res * 10) + (str[i] - 48));
		i++;
	}
	return (res * s);
}

int	check_mutex(int flag, t_philo *ph)
{
	int	temp;

	temp = 0;
	if (flag == 0)
	{
		pthread_mutex_lock(&ph->rules->finish_lock);
		temp = ph->rules->finish_flag;
		pthread_mutex_unlock(&ph->rules->finish_lock);
	}
	else if (flag == 1)
	{
		pthread_mutex_lock(&ph->eat_lock);
		temp = ph->eat_flag;
		pthread_mutex_unlock(&ph->eat_lock);
	}
	return (temp);
}

void	ft_wait(long long wait_time)
{
	long long	start_time;

	start_time = get_time();
	usleep(wait_time * 1000 - 20000);
	while (get_time() < start_time + wait_time)
		continue ;
}

void	ft_exit(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
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
