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
	pthread_t		death;
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
	sem_t			*forks;
	sem_t			*write;
	sem_t			*must_eat;
	t_philo			*philo;
}				t_rules;

int			ft_isnumeric(int argc, char *argv[]);
void		ft_error(char *str);
int			ft_atoi(const char *str);
void		ft_philomaker(t_rules *rules);
long long	get_time(void);
void		print_msg(t_philo *ph, char *str);
void		ft_exit(t_rules *rules);

#endif
