/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   a_philo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 18:16:00 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/05 16:28:23 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

/*
** eating -> sleeping -> thinking
*/

void		safe_lock(sem_t *lock, int die)
{
	/*pthread_mutex_lock(lock);*/
	sem_wait(lock);
	if (die)
		exit(0);
}

void		print_status(char *status, long time, int i_am, t_data *d)
{
	/*safe_lock(&d->lstatus, d->has_died);*/
	safe_lock(d->lstatus, d->has_died);
	printf("%ld\t%d %s\n", time, i_am, status);
	/*pthread_mutex_unlock(&d->lstatus);*/
	sem_post(d->lstatus);
}

void		drop_fork(t_data *d)
{
	/*pthread_mutex_unlock(p->fork[0]);*/
	/*pthread_mutex_unlock(p->fork[1]);*/
	sem_post(d->fork);
	sem_post(d->fork);
}

void		grab_fork(t_data *d, t_philo *p)
{
	/*safe_lock(p->fork[0], d->has_died);*/
	safe_lock(d->fork, d->has_died);
	print_status("has taken a fork", elapsed(d) / 1000, p->i_am, d);
	safe_lock(d->fork, d->has_died);
	/*pthread_mutex_lock(&p->leat);*/
	sem_wait(p->leat);
	p->eat_count++;
	p->ate_at = elapsed(d);
	print_status("is eating", elapsed(d) / 1000, p->i_am, d);
	/*pthread_mutex_unlock(&p->leat);*/
	sem_post(p->leat);
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
	/*p->fork[0] = p->i_am - 2 < 0 ? &d->fork[d->no_philo - 1] : &d->fork[p->i_am - 2];*/
	/*p->fork[1] = &d->fork[p->i_am - 1];*/
	while (1)
	{
		print_status("is thinking", elapsed(d) / 1000, p->i_am, d);
		eat_debug(d, p);//Debug
		grab_fork(d, p);
		eat_debug(d, p);//Debug
		usleep(d->time_eat);
		drop_fork(d);
		print_status("is sleeping", elapsed(d) / 1000, p->i_am, d);
		usleep(d->time_sleep);
	}
	return (0);
}

