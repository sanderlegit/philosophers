/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destructor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 13:06:48 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/11 14:37:48 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pthread_unlock_destroy(pthread_mutex_t *mutex)
{
	pthread_mutex_unlock(mutex);
	pthread_mutex_destroy(mutex);
}

void	destruct_mutex(t_data *d)
{
	int		i;

	d->has_died = 1;
	if (d->mutex_check)
	{
		pthread_unlock_destroy(&d->lstatus);
		d->mutex_check--;
	}
	i = 0;
	while (i < d->no_philo)
	{
		if (d->fork && d->mutex_check)
		{
			pthread_unlock_destroy(&d->fork[i]);
			d->mutex_check--;
		}
		if (d->ph && d->mutex_check)
		{
			pthread_unlock_destroy(&d->ph[i].leat);
			d->mutex_check--;
		}
		i++;
	}
}

void	destruct_data(t_data *d)
{
	if (d->fork)
	{
		free(d->fork);
		d->fork = NULL;
	}
	if (d->ph)
	{
		free(d->ph);
		d->ph = NULL;
	}
	if (d->threads)
	{
		free(d->threads);
		d->threads = NULL;
	}
}
