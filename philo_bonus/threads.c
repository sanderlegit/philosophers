/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 14:45:36 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/12 14:30:08 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	run_simulation(t_data *d)
{
	d->is_parent = 1;
	d->pids = ft_calloc(d->no_philo, sizeof(int));
	if (!d->pids)
		return (print_return("run_simulation: failed to allocate pids", 1));
	d->threads = ft_calloc(d->no_philo, sizeof(pthread_t));
	if (!d->threads)
		return (print_return("run_simulation: failed to allocate threads", 1));
	if (init_time(d))
		return (1);
	if (start_philo(d))
		return (1);
	end_processes(d);
	return (0);
}

int	start_philo(t_data *d)
{
	int			i;

	i = 0;
	while (i < d->no_philo)
	{
		d->alive = i;
		d->pids[i] = fork();
		if (d->pids[i] == 0)
		{
			d->is_parent = 0;
			d->ph.i_am = i + 1;
			if (pthread_create(&d->threads[i], NULL, a_philo, d))
				return (print_return("run_thread: failed to create thread", 1));
			manage_thread(d);
			destruct_data(d);
			exit(0);
		}
		else if (d->pids[i] < 0)
			return (print_return("start_philo: failed to fork", 1));
		usleep(1000);
		i++;
	}
	return (0);
}

void	death(t_data *d)
{
	(void)d;
}

void	manage_thread(t_data *d)
{
	while (!d->has_died)
	{
		sem_wait(d->ls[d->ph.i_am - 1].leat);
		if (d->m_eat != -1 && d->ph.eat_count >= d->m_eat)
			d->has_died = 1;
		if ((elapsed(d->start_time) - d->ph.ate_at) > d->time_die)
		{
			print_status(DIED, d->ph.i_am, d);
			d->has_died = 1;
		}
		sem_post(d->ls[d->ph.i_am - 1].leat);
	}
}

void	end_processes(t_data *d)
{
	int		i;
	int		tmp;

	i = 0;
	while (i < d->no_philo)
	{
		waitpid(d->pids[i], &tmp, 0);
		d->pids[i] = 0;
		i++;
	}
	destruct_sem(d);
}
