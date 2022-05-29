/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:21:05 by ebondi            #+#    #+#             */
/*   Updated: 2022/04/11 18:21:05 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_forks(t_rules *rules)
{
	int	i;
	int	ph;

	ph =  rules->n_ph;
	rules->forks = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * ph);
	i = 0;
	while (i < ph)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
}

void	ft_init(t_rules *rules, char *argv[])
{
	int	i;

	rules->n_ph = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	rules->finish = 0;
	ft_init_forks(rules);
	pthread_mutex_init(&rules->write, NULL);
	pthread_mutex_init(&rules->time, NULL);
	rules->philo = (t_philo *) malloc (sizeof(t_philo) * rules->n_ph);
	i = 0;
	while (i < rules->n_ph)
	{
		rules->philo[i].last_meal = 0;
		rules->philo[i].rules = rules;
		rules->philo[i].id = i + 1;
		rules->philo[i].n_eat = 0;
		rules->philo[i].philo_finish = 0;
		rules->philo[i].rules = rules;
		rules->philo[i].left = &rules->forks[i];
		if (i == rules->n_ph - 1 && rules->n_ph != 1)
			rules->philo[i].right = &rules->forks[0];
		else if (i != rules->n_ph - 1)
			rules->philo[i].right = &rules->forks[i + 1];
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_rules	rules;

	if ((argc != 5 && argc != 6) || ft_isnumeric(argc, argv) == 0)
	{
		ft_error("Arg");
		return (0);
	}
	ft_init(&rules, argv);

	if (argc == 6)
		rules.nb_must_eat = ft_atoi(argv[5]);
	else
		rules.nb_must_eat = -1;
	ft_threadmaker(&rules);
}
