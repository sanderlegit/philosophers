/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:46:29 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/05 13:24:53 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <pthread.h>

int			init_data(t_data *d)
{
	int		i;

	create_fork_debug(d);//Debug
	d->alive = 0;
	d->fork = ft_calloc(d->no_philo, sizeof(pthread_mutex_t));
	if (!d->fork)
		return (print_return("run_threads: failed to allocate fork", 1));
	d->ph = ft_calloc(d->no_philo, sizeof(t_philo));
	if (!d->ph) {
		free(d->fork);
		return (print_return("run_threads: failed to allocate philo pointers", 1));
	}
	if (pthread_mutex_init(&d->lstatus, NULL) != 0)
		return (print_return("init_data: mutex initialization failed", 1));
	i = 0;
	while (i < d->no_philo)
	{
		if (pthread_mutex_init(&d->fork[i], NULL) != 0)
			return (print_return("init_data: mutex initialization failed", 1));
		if (pthread_mutex_init(&d->ph[i].leat, NULL) != 0)
			return (print_return("init_data: mutex initialization failed", 1));
		i++;
	}
	return (0);
}

int			start_threads(t_data *d)
{
	pthread_t	threads[d->no_philo];
	int			i;

	i = 0;
	if (init_time(d))
		return (1);
	while (i < d->no_philo)
	{
		if (pthread_create(&threads[i], NULL, a_philo, d))
			return (print_return("run_thread: failed to create thread", 1));
		/*pthread_detach(threads[i]);*/
		i++;
	}
	manage_threads(d);
	end_threads(d, threads);
	return (0);
}

void		manage_threads(t_data *d)
{
	int		i;

	while (!d->has_died) {
		i = 0;
		while (!d->has_died && i < d->no_philo)
		{
			pthread_mutex_lock(&d->ph[i].leat);
			if (d->must_eat != -1 && !d->ph[i].full && d->ph[i].eat_count >= d->must_eat)
			{
				d->no_full++;
				d->ph[i].full = 1;
				if (d->no_full == d->no_philo)
					d->has_died = 1;
				if (d->no_full == d->no_philo)
					pthread_mutex_lock(&d->lstatus);
			}
			if ((elapsed(d) - d->ph[i].ate_at) > d->time_die) {
				print_status("died", elapsed(d) / 1000, i + 1, d);
				d->has_died = 1;
				pthread_mutex_lock(&d->lstatus);
			}
			pthread_mutex_unlock(&d->ph[i].leat);
			i++;
		}
	}
}

void		end_threads(t_data *d, pthread_t threads[])
{
	int		i;

	free(d->fork);
	pthread_mutex_unlock(&d->lstatus);
	pthread_mutex_destroy(&d->lstatus);
	i = 0;
	while (i < d->no_philo)
	{
		pthread_mutex_unlock(&d->fork[i]);
		pthread_mutex_unlock(&d->ph[i].leat);
		pthread_mutex_destroy(&d->fork[i]);
		pthread_mutex_destroy(&d->ph[i].leat);
		i++;
	}
	i = 0;
	while (i < d->no_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

/*
** argv[1] number_of_pihlo:	no of philo, and no of forks
** argv[2] time_to_die:		milliseconds, max time since start last
** 							meal/simulation before death
** argv[2] time_to_eat:		milliseconds, duration to eat (2 forks)
** argv[2] time_to_sleep:	milliseconds, time spend sleeping
** argv[2] number_of_times_\
** each_philosopher_\
** must_eat:				(optional) stop after each philo eats x times
**							(instead of stop on death)
*/

int			main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (parse_args(&data, argc, argv))
		return (1);
	if (init_data(&data))
		return (1);
	if (start_threads(&data))
		return (1);
	free(data.fork_status);//Debug
	free(data.ph);
	return (0);
}
