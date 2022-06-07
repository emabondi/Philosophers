/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:31:21 by ebondi            #+#    #+#             */
/*   Updated: 2022/06/07 23:50:47 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	print_msg(t_philo *ph, char *str)
{
	sem_wait(ph->rules->write);
	printf ("%llu %d %s\n", get_time() - ph->rules->start_time, ph->id, str);
	sem_post(ph->rules->write);
}
