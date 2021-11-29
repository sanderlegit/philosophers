/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 14:29:29 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/11 14:49:00 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_simulation(t_data *d)
{
	d->threads = ft_calloc(d->no_philo, sizeof(pthread_t));
	if (!d->threads)
		return (print_return("run_simulation: failed to allocate threads", 1));
	if (init_time(d))
		return (1);
	if (start_threads(d, d->threads))
		return (1);
	manage_threads(d);
	end_threads(d, d->threads);
	return (0);
}

int	start_threads(t_data *d, pthread_t *threads)
{
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
	return (0);
}

void	death(t_data *d)
{
	d->has_died = 1;
	pthread_mutex_lock(&d->lstatus);
}

void	manage_threads(t_data *d)
{
	int		i;

	while (!d->has_died)
	{
		i = 0;
		while (!d->has_died && i < d->no_philo)
		{
			pthread_mutex_lock(&d->ph[i].leat);
			if (d->m_eat != -1 && !d->ph[i].full && d->ph[i].eat_c >= d->m_eat)
			{
				d->no_full++;
				d->ph[i].full = 1;
				if (d->no_full == d->no_philo)
					death(d);
			}
			if ((elapsed(d->start_time) - d->ph[i].ate_at) > d->time_die)
			{
				print_status(DIED, i + 1, d);
				death(d);
			}
			pthread_mutex_unlock(&d->ph[i].leat);
			usleep(7000 / d->no_philo);
			i++;
		}
	}
}

void	end_threads(t_data *d, pthread_t *threads)
{
	int		i;

	destruct_mutex(d);
	i = 0;
	while (i < d->no_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
