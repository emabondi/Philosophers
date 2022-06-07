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
	int				eat_flag;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread;
	long long		last_meal;
	struct s_rules	*rules;
}				t_philo;

typedef struct s_rules
{
	int				n_ph;
	int				finish;
	long long		time_death;
	int				time_eat;
	int				time_sleep;
	int				nb_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	time;
	pthread_mutex_t	finish_lock;
	int				finish_flag;
	long long		start_time;
	t_philo			*philo;
}				t_rules;

void		ft_error(char *str);
void		ft_putstr(char *str);
int			ft_isnumeric(int argc, char *argv[]);
int			ft_atoi(const char *str);
void		ft_threadmaker(t_rules *rules);
void		print_msg(t_philo *ph, char *str);
long long	get_time(void);
int			check_mutex(int flag, t_philo *ph);
void		ft_wait(long long wait_time);
void		ft_exit(t_rules *rules);

#endif
