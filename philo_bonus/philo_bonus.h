/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:20:46 by ebondi            #+#    #+#             */
/*   Updated: 2022/05/31 22:45:07 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <semaphore.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				n_eat;
	int				eat_flag;
	long long		last_meal;
	struct s_rules	*rules;
}				t_philo;

typedef struct s_rules
{
	int			n_ph;
	int			finish;
	long long	time_death;
	int			time_eat;
	int			time_sleep;
	int			nb_must_eat;
	long long	start_time;
	sem_t		*forks;
	sem_t		*write;
	sem_t		*finish;
	t_philo		*philo;
}				t_rules;

#endif