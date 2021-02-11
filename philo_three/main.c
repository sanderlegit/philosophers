/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:46:29 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/11 14:55:59 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	init_data(t_data *d, int i)
{
	d->ph = ft_calloc(d->no_philo, sizeof(t_philo));
	if (!d->ph)
		return (print_return("run_threads: failed to allocate t_philo", 1));
	sem_unlink("lstatus");
	d->lstatus = sem_open("lstatus", O_CREAT, 666, 1);
	if (!d->lstatus)
		return (print_return("init_data: sem initialization failed", 1));
	sem_unlink("fork");
	d->fork = sem_open("fork", O_CREAT, 666, d->no_philo);
	if (!d->fork)
		return (print_return("init_data: sem initialization failed", 1));
	i = 0;
	while (i < d->no_philo)
	{
		d->ph[i].semname = get_semname(i);
		if (!d->ph[i].semname)
			return (print_return("init_data: sem name init failed", 1));
		sem_unlink(d->ph[i].semname);
		d->ph[i].leat = sem_open(d->ph[i].semname, O_CREAT, 666, 1);
		if (!d->ph[i].leat)
			return (print_return("init_data: sem init failed", 1));
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
	int		i;

	ft_bzero(&data, sizeof(t_data));
	if (parse_args(&data, argc, argv))
		return (1);
	i = 0;
	if (init_data(&data, i))
	{
		destruct_sem(&data);
		destruct_data(&data);
		return (1);
	}
	if (run_simulation(&data))
	{
		destruct_sem(&data);
		destruct_data(&data);
		return (1);
	}
	destruct_data(&data);
	return (0);
}
