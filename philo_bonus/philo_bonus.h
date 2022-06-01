/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 11:23:43 by ebondi            #+#    #+#             */
/*   Updated: 2022/04/25 11:23:43 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_philo
{
	int				id;
	int				n_eat;
	pid_t			pid;
	long long		last_meal;
	struct s_rules	*rules;
}				t_philo;

typedef struct s_rules
{
	int				n_ph;
	long long		time_death;
	int				time_eat;
	int				time_sleep;
	int				nb_must_eat;
	long long		start_time;
	sem_t			*fork;
	sem_t			write;
	t_philo			*philo;
}				t_rules;

#endif
