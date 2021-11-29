/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:46:29 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/11 14:41:48 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *d)
{
	int		i;

	d->fork = ft_calloc(d->no_philo, sizeof(pthread_mutex_t));
	if (!d->fork)
		return (print_return("run_threads: failed to allocate fork", 1));
	d->ph = ft_calloc(d->no_philo, sizeof(t_philo));
	if (!d->ph)
		return (print_return("run_threads: failed to allocate t_philo", 1));
	if (pthread_mutex_init(&d->lstatus, NULL) != 0)
		return (print_return("init_data: mutex initialization failed", 1));
	d->mutex_check++;
	i = 0;
	while (i < d->no_philo)
	{
		if (pthread_mutex_init(&d->fork[i], NULL) != 0)
			return (print_return("init_data: mutex init failed", 1));
		d->mutex_check++;
		if (pthread_mutex_init(&d->ph[i].leat, NULL) != 0)
			return (print_return("init_data: mutex init failed", 1));
		d->mutex_check++;
		i++;
	}
	return (0);
}

/*
** argv[1] number_of_pihlo:	no of philo, and no of forks
** argv[2] time_to_die:		milliseconds, max time since start last
** 							meal/simulation before death
** argv[3] time_to_eat:		milliseconds, duration to eat (2 forks)
** argv[4] time_to_sleep:	milliseconds, time spend sleeping
** argv[5] number_of_times_\
** each_philosopher_\
** m_eat:				(optional) stop after each philo eats x times
**							(instead of stop on death)
*/

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (parse_args(&data, argc, argv))
		return (1);
	if (init_data(&data))
	{
		destruct_mutex(&data);
		destruct_data(&data);
		return (1);
	}
	if (run_simulation(&data))
	{
		destruct_mutex(&data);
		destruct_data(&data);
		return (1);
	}
	destruct_data(&data);
	return (0);
}
