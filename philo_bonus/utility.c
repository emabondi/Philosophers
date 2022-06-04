/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <ebondi@student.42roma.it>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 18:24:07 by ebondi            #+#    #+#             */
/*   Updated: 2022/04/11 18:24:07 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_dead(t_philo *ph)
{
	sem_wait(ph->rules->write);
	printf ("%llu %d dead\n",  get_time() - ph->rules->start_time, ph->id);
	ph->rules->dead = 1;
}

int	ft_isnumeric(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while ((argv[i][j] >= 9 && argv[i][j] <= 13) || argv[i][j] == 32)
			j++;
		if (argv[i][j] == '+')
			j++;
		if (argv[i][j] == '\0')
			return (0);
		while (argv[i][j] != '\0')
		{
			if(argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_error(char *str)
{
	printf("%s error\n", str);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	res;

	i = 0;
	s = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			s *= -1;
		i += 1;
	}
	if (str[i] == 43 || str[i] == 45)
		return (0);
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = ((res * 10) + (str[i] - 48));
		i++;
	}
	return (res * s);
}
