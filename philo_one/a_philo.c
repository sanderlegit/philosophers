/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   a_philo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 18:16:00 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/01 20:10:41 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** eating -> sleeping -> thinking
*/

void		print_status(char *status, long time, int i_am, t_data *d)
{
	pthread_mutex_lock(&d->lstatus);
	printf("%ld\t\t%d %s\n", time, i_am, status);
	pthread_mutex_unlock(&d->lstatus);
}

void		drop_fork(t_data *d, t_philo *p)
{
	d->fork_status[p->i_am - 1] = 0;
	if (p->i_am - 2 < 0)
		d->fork_status[d->no_of_philo - 1] = 0;
	else
		d->fork_status[p->i_am - 2] = 0;
	p->has_fork = 0;
	print_forks(d, p);
}

void		grab_fork(t_data *d, t_philo *p)
{
	int		ready;

	pthread_mutex_lock(&d->lforks);
	ready = 0;
	if (d->fork_status[p->i_am - 1] == 0) {
		if (p->i_am - 2 < 0)
		{
			if (d->fork_status[d->no_of_philo - 1] == 0)
				ready = 1;
		}
		else
			if (d->fork_status[p->i_am - 2] == 0)
				ready = 1;
	}
	if (ready)
	{
		print_forks(d, p);
		d->fork_status[p->i_am - 1] = p->i_am;
		if (p->i_am - 2 < 0)
			d->fork_status[d->no_of_philo - 1] = p->i_am;
		else
			d->fork_status[p->i_am - 2] = p->i_am;
		p->has_fork = 1;
	}
	pthread_mutex_unlock(&d->lforks);
}

void		*a_philo(void *vstruct)
{
	t_data	*d;
	t_philo	p;

	ft_bzero(&p, sizeof(t_philo));
	d = vstruct;
	p.i_am = d->i_am;
	d->i_am++;
	p.ate_at = elapsed(d);
	print_status("was born", elapsed(d) / 1000, p.i_am, d);
	while (!d->has_died)
	{
		print_status("is thinking", elapsed(d) / 1000, p.i_am, d);
		while (!p.has_fork)
		{
			grab_fork(d, &p);
			if ((elapsed(d) - p.ate_at) > d->time_die)
				break;
		}
		if ((elapsed(d) - p.ate_at) > d->time_die)
			break;
		print_forks(d, &p);
		print_status("has taken a fork", elapsed(d) / 1000, p.i_am, d);
		print_status("is eating", elapsed(d) / 1000, p.i_am, d);
		p.eat_count++;
		if (PEATD) {
			pthread_mutex_lock(&d->lstatus);
			printf("\t\t%d has eaten %d times, last %ld\n", p.i_am, p.eat_count, (elapsed(d) - p.ate_at) / 1000);
			pthread_mutex_unlock(&d->lstatus);
		}
		p.ate_at = elapsed(d);
		usleep(d->time_eat);
		drop_fork(d, &p);
		if (d->must_eat != -1 && p.eat_count >= d->must_eat)
			break;
		print_status("is sleeping", elapsed(d) / 1000, p.i_am, d);
		usleep(d->time_sleep);
	}
	if (!d->has_died)
		print_status("died", elapsed(d) / 1000, p.i_am, d);
	if (PEATD) {
		pthread_mutex_lock(&d->lstatus);
		printf("\t\t%d has eaten %d times, last %ld\n", p.i_am, p.eat_count, (elapsed(d) - p.ate_at) / 1000);
		pthread_mutex_unlock(&d->lstatus);
	}
	d->has_died = 1;
	return (0);
}

