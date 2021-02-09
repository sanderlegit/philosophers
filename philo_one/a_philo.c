/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   a_philo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 18:16:00 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/05 14:10:21 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** eating -> sleeping -> thinking
*/

void		safe_lock(pthread_mutex_t *lock, int *die)
{
	pthread_mutex_lock(lock);
	if (*die)
		exit(0);
}

void		print_status(char *status, int i_am, t_data *d)
{
	/*safe_lock(&d->lstatus, &d->has_died);*/
	pthread_mutex_lock(&d->lstatus);
	if (d->has_died)
		exit(0);
	/*printf("%ld\t%d %s\n", time, i_am, status);*/
	ft_putlong(elapsed(d) / 1000);
	write(1, "\t", 1);
	ft_putint(i_am);
	ft_putstr(status);
	write(1, "\n", 1);
	pthread_mutex_unlock(&d->lstatus);
}

void		drop_fork(t_philo *p)
{
	pthread_mutex_unlock(p->fork[0]);
	pthread_mutex_unlock(p->fork[1]);
}

void		grab_fork(t_data *d, t_philo *p)
{
	safe_lock(p->fork[0], &d->has_died);
	print_status(FORK, p->i_am, d);
	safe_lock(p->fork[1], &d->has_died);
	pthread_mutex_lock(&p->leat);
	p->eat_count++;
	p->ate_at = elapsed(d);
	print_status(EAT, p->i_am, d);
	pthread_mutex_unlock(&p->leat);
	/*fork_debug(d, p, p->i_am);//Debug*/
}

void		*a_philo(void *vstruct)
{
	t_data	*d;
	t_philo	*p;
	int		i;

	d = vstruct;
	i = d->alive;
	p = &d->ph[i];
	p->i_am = i + 1;
	p->ate_at = elapsed(d);
	p->fork[0] = p->i_am - 2 < 0 ? &d->fork[d->no_philo - 1] : &d->fork[p->i_am - 2];
	p->fork[1] = &d->fork[p->i_am - 1];
	while (1)
	{
		print_status(THINK, p->i_am, d);
		/*eat_debug(d, p);//Debug*/
		/*grab_fork(d, p);*/
			/*safe_lock(p->fork[0], &d->has_died);*/
				pthread_mutex_lock(p->fork[0]);
				if (d->has_died)
					exit(0);
			print_status(FORK, p->i_am, d);
			/*safe_lock(p->fork[1], &d->has_died);*/
				pthread_mutex_lock(p->fork[1]);
				if (d->has_died)
					exit(0);
			pthread_mutex_lock(&p->leat);
			p->eat_count++;
			p->ate_at = elapsed(d);
			print_status(EAT, p->i_am, d);
			pthread_mutex_unlock(&p->leat);
		/*eat_debug(d, p);//Debug*/
		usleep(d->time_eat);
		/*drop_fork(p);*/
			pthread_mutex_unlock(p->fork[0]);
			pthread_mutex_unlock(p->fork[1]);
		/*fork_debug(d, p, 0);//Debug*/
		print_status(SLEEP, p->i_am, d);
		usleep(d->time_sleep);
	}
	return (0);
}

