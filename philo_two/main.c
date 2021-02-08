/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:46:29 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/05 16:53:21 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			init_data(t_data *d) //TODO This does not clear well during a crash at any point
{
	int		i;

	d->alive = 0;
	d->ph = ft_calloc(d->no_philo, sizeof(t_philo));
	if (!d->ph)
		return (print_return("run_threads: failed to allocate philo pointers", 1));
	sem_unlink("lstatus");
	d->lstatus = sem_open("lstatus", O_CREAT, 666, 1);
	if (!d->lstatus)
		return (print_return("init_data: sem initialization failed", 1));
	sem_unlink("fork");
	d->fork = sem_open("fork", O_CREAT, 666, d->no_philo);
	if (!d->lstatus)
		return (print_return("init_data: sem initialization failed", 1));
	i = 0;
	while (i < d->no_philo)
	{
		d->ph[i].semname = get_semname(i);
		if (!d->ph[i].semname)
			return (print_return("init_data: sem name initialization failed", 1));
		sem_unlink(d->ph[i].semname);
		d->ph[i].leat = sem_open(d->ph[i].semname, O_CREAT, 666, 1);
		if (!d->ph[i].leat)
			return (print_return("init_data: sem initialization failed", 1));
		i++;
	}
	return (0);
}

int			start_threads(t_data *d)
{
	pthread_t	threads[d->no_philo];
	int			i;

	i = 0;
	while (i < d->no_philo)
	{
		d->alive = i;
		if (pthread_create(&threads[i], NULL, a_philo, d))
			return (print_return("run_thread: failed to create thread", 1));
		i += 2;
		usleep(1000);
	}
	i = 1;
	while (i < d->no_philo)
	{
		d->alive = i;
		if (pthread_create(&threads[i], NULL, a_philo, d))
			return (print_return("run_thread: failed to create thread", 1));
		i += 2;
		usleep(1000);
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
			sem_wait(d->ph[i].leat);
			if (d->must_eat != -1 && !d->ph[i].full && d->ph[i].eat_count >= d->must_eat)
			{
				d->no_full++;
				d->ph[i].full = 1;
				if (d->no_full == d->no_philo)
					d->has_died = 1;
				if (d->no_full == d->no_philo)
					sem_wait(d->lstatus);
			}
			if ((elapsed(d) - d->ph[i].ate_at) > d->time_die) {
				print_status(" died", elapsed(d) / 1000, i + 1, d);
				d->has_died = 1;
				sem_wait(d->lstatus);
			}
			sem_post(d->ph[i].leat);
			usleep(7000 / d->no_philo);
			i++;
		}
	}
}

void		end_threads(t_data *d, pthread_t threads[]) //TODO incomplete
{
	int		i;

	sem_post(d->lstatus);		//TODO Split into another function, and call on error during init
	sem_unlink("lstatus");
	i = 0;
	while (i < d->no_philo)
	{
		sem_post(d->ph[i].leat);
		sem_unlink(d->ph[i].semname);
		sem_post(d->fork);
		i++;
	}
	sem_unlink("fork");
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
	int		i;

	ft_bzero(&data, sizeof(t_data));
	if (parse_args(&data, argc, argv))
		return (1);
	if (init_data(&data))
		return (1);
	if (init_time(&data))
		return (1);
	if (start_threads(&data))
		return (1);
	i = 0;
	while (i < data.no_philo)
	{
		free(data.ph[i].semname);
		i++;
	}
	free(data.ph);
	return (0);
}
