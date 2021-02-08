/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   a_philo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 18:16:00 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/05 16:58:52 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

/*
** eating -> sleeping -> thinking
*/

void		safe_lock(sem_t *lock, int *die)
{
	sem_wait(lock);
	if (*die)
		exit(0);
}

void		print_status(char *status, long time, int i_am, t_data *d)
{
	safe_lock(d->lstatus, &d->has_died);
	/*printf("%ld\t%d %s\n", time, i_am, status);*/
	ft_putlong(time);
	write(1, "\t", 1);
	ft_putint(i_am);
	ft_putstr(status);
	write(1, "\n", 1);
	sem_post(d->lstatus);
}

void		drop_fork(t_data *d)
{
	sem_post(d->fork);
	sem_post(d->fork);
}

void		grab_fork(t_data *d, t_philo *p)
{
	if (p->lshare) {
		/*printf("->%d waiting\n", p->i_am);*/
		/*ft_putint(p->i_am);*/
		/*ft_putstr(" waiting\n");*/
		/*sem_wait(p->lshare);*/
		/*printf("->%d done waiting\n", p->i_am);*/
	}
	safe_lock(d->fork, &d->has_died);
	/*print_forks(d, 1, p->i_am);//Debug*/
	print_status(" has taken a fork", elapsed(d) / 1000, p->i_am, d);
	safe_lock(d->fork, &d->has_died);
	sem_wait(p->leat);
	/*print_forks(d, 1, p->i_am);//Debug*/
	p->eat_count++;
	p->ate_at = elapsed(d);
	print_status(" is eating", elapsed(d) / 1000, p->i_am, d);
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
	while (1)
	{
		print_status(" is thinking", elapsed(d) / 1000, p->i_am, d);
		/*eat_debug(d, p);//Debug*/
		grab_fork(d, p);
		/*eat_debug(d, p);//Debug*/
		usleep(d->time_eat);
		drop_fork(d);
		if (p->lshare) {
			/*ft_putint(p->i_am);*/
			/*ft_putstr(" clearing\n");*/
			/*printf("->%d clearing\n", p->i_am);*/
			/*sem_post(p->lshare);*/
			/*printf("->%d cleared\n", p->i_am);*/
		}
		/*print_forks(d, -2, -1 * p->i_am);//Debug*/
		print_status(" is sleeping", elapsed(d) / 1000, p->i_am, d);
		usleep(d->time_sleep);
	}
	return (0);
}

