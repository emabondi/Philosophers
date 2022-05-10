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

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				n_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread;
	uint64_t		last_meal;
	struct s_rules	*rules;
}				t_philo;

typedef struct s_rules
{
	int				n_ph;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				nb_must_eat;
	int				finish;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	uint16_t		start_time;
	pthread_t		monitoring_thread;
	t_philo			*philo;
}				t_rules;

void		ft_error(char *str);
void		ft_putstr(char *str);
int			ft_isnumeric(int argc, char *argv[]);
int			ft_atoi(const char *str);
void		ft_threadmaker(t_rules *rules);
void		print_msg(uint16_t start_time, int id, pthread_mutex_t	*write, char *str);
uint16_t	get_time(void);
#endif