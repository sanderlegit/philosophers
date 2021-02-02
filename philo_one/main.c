/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:46:29 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/02 11:45:54 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <pthread.h>

int			init_data(t_data *d)
{
	int		i;

	d->fork_status = ft_calloc(d->no_of_philo, sizeof(char));//Debug
	if (!d->fork_status)//Debug
		return (print_return("run_threads: failed to allocate fork_status", 1));//Debug

	d->alive = 0;
	d->fork_lock = ft_calloc(d->no_of_philo, sizeof(pthread_mutex_t));
	if (!d->fork_lock)
		return (print_return("run_threads: failed to allocate fork_lock", 1));
	d->ph = ft_calloc(d->no_of_philo, sizeof(t_philo));
	if (!d->ph) {
		free(d->fork_lock);
		return (print_return("run_threads: failed to allocate philo pointers", 1));
	}
	if (pthread_mutex_init(&d->lstatus, NULL) != 0)
		return (print_return("init_data: mutex initialization failed", 1));
	if (pthread_mutex_init(&d->lforks, NULL) != 0)
		return (print_return("init_data: mutex initialization failed", 1));
	i = 0;
	while (i < d->no_of_philo)
	{
		if (pthread_mutex_init(&d->fork_lock[i], NULL) != 0)
			return (print_return("init_data: mutex initialization failed", 1));
		i++;
	}
	return (0);
}

int			run_threads(t_data *d)
{
	pthread_t	threads[d->no_of_philo];
	int			i;

	i = 0;
	if (init_time(d))
		return (1);
	while (i < d->no_of_philo)
	{
		if (pthread_create(&threads[i], NULL, a_philo, d))
			return (print_return("run_thread: failed to create thread", 1));
		pthread_detach(threads[i]);
		i++;
	}
	//Continiously check if a philosopher has died, by checking p->ate_at 
	while (d->alive != 0) {
		i = 0;
		while (i < d->no_of_philo)
		{
			/*if (PEATD) {//Debug*/
				/*pthread_mutex_lock(&d->lstatus);//Debug*/
				/*printf("\t\t%d has eaten %d times, last %ld\n", i + 1, d->ph[i].eat_count, (elapsed(d) - d->ph[i].ate_at) / 1000);//Debug*/
				/*pthread_mutex_unlock(&d->lstatus);//Debug*/
			/*}//Debug*/
			if (d->ph[i].has_died != 1 && (elapsed(d) - d->ph[i].ate_at) > d->time_die) {
				print_status("died", elapsed(d) / 1000, i + 1, d);
				d->ph[i].has_died = 1;
				printf("still alive: %d\n", d->alive);
			}
			/*pthread_join(threads[i], NULL);*/
			i++;
		}
	}
	i = 0;
	while (i < d->no_of_philo)
	{
		if (pthread_mutex_destroy(&d->fork_lock[i]) != 0)
			print_return("run_threads: mutex destroy failed", 1);
		i++;
	}
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
	if (init_data(&data))
		return (1);
	if (run_threads(&data))
		return (1);
	free(data.fork_status);
	free(data.ph);
	return (0);
}
