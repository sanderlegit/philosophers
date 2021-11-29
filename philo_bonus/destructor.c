/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destructor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/12 13:19:34 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/12 14:21:02 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destruct_sem(t_data *d)
{
	int		i;

	d->has_died = 1;
	if (d->lstatus)
		sem_post(d->lstatus);
	sem_unlink("lstatus");
	i = 0;
	while (i < d->no_philo)
	{
		if (d->ls && d->ls[i].leat)
		{
			sem_post(d->ls[i].leat);
			sem_unlink(d->ls[i].semname);
		}
		if (d->fork)
			sem_post(d->fork);
		i++;
	}
	sem_unlink("fork");
}

void	kill_processes(t_data *d)
{
	int		i;

	i = 0;
	while (i < d->no_philo)
	{
		if (d->pids[i])
		{
			kill(d->pids[i], SIGTERM);
			d->pids[i] = 0;
		}
		i++;
	}
}

void	destruct_data(t_data *d)
{
	int		i;

	if (d->ls)
	{
		i = 0;
		while (i < d->no_philo)
		{
			if (d->ls[i].semname)
			{
				free(d->ls[i].semname);
				d->ls[i].semname = NULL;
			}
			i++;
		}
		free(d->ls);
	}
	if (d->pids)
	{
		free(d->pids);
		d->pids = NULL;
	}
}
