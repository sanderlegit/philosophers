/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:46:29 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/01 19:57:53 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			init_mutex(t_data *d)
{
	if (pthread_mutex_init(&d->lstatus, NULL) != 0)
		return (print_return("init_mutex: mutex initialization failed", 1));
	/*if (pthread_mutex_init(&d->lforks, NULL) != 0)*/
		/*return (print_return("init_mutex: mutex initialization failed", 1));*/
	return (0);
}

int			run_threads(t_data *d)
{
	pthread_t	threads[d->no_of_philo];
	int			i;

	d->i_am = 1;
	d->fork_status = ft_calloc(d->no_of_philo, sizeof(char));
	if (!d->fork_status)
		return (print_return("run_threads: failed to allocate fork_status ", 1));
	i = 0;
	if (init_time(d))
		return (1);
	while (i < d->no_of_philo)
	{
		if (pthread_create(&threads[i], NULL, a_philo, d))
			return (print_return("run_thread: failed to create thread", 1));
		i++;
	}
	i = 0;
	while (i < d->no_of_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(d->fork_status);
	return (0);
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
	if (init_mutex(&data))
		return (1);
	if (run_threads(&data))
		return (1);
	return (0);
}
