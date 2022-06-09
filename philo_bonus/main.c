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

#include "philo_bonus.h"

sem_t	*ft_semaphore(char *name, int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	return (sem_open(name, O_CREAT, S_IRUSR | S_IWUSR, value));
}

void	ft_init(t_rules *rules, char *argv[])
{
	int	i;

	rules->n_ph = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	rules->forks = ft_semaphore("/forks", rules->n_ph);
	rules->write = ft_semaphore("/write", 1);
	rules->finish = ft_semaphore("/finish", 0);
	rules->must_eat = ft_semaphore("/must_eat", 0);
	rules->philo = (t_philo *) malloc (sizeof(t_philo) * rules->n_ph);
	i = 0;
	while (i < rules->n_ph)
	{
		rules->philo[i].rules = rules;
		rules->philo[i].id = i + 1;
		rules->philo[i].n_eat = 0;
		rules->philo[i].last_meal = 0;
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
	ft_philomaker(&rules);
	exit(0);
}
