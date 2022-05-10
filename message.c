/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 23:31:21 by ebondi            #+#    #+#             */
/*   Updated: 2022/05/10 02:42:01 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint16_t	get_time(void)
{
	struct timeval timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * (uint16_t)1000) + (timeval.tv_usec / (uint16_t)1000));

void	print_msg(uint16_t start_time, int id, pthread_mutex_t	*write, char *str)
{
	pthread_mutex_lock(write);
	printf ("%llu %d %s\n",  get_time() - start_time, id, str);
	pthread_mutex_unlock(write);
}