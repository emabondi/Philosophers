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

void	*ft_thread(void *philo)
{
	printf("ciao\n");
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
}