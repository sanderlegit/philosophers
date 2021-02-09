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

void		print_status(char *status, int i_am, t_data *d)
{
	/*safe_lock(d->lstatus, &d->has_died);*/
	sem_wait(d->lstatus);
	if (d->has_died)
		exit(0);
	ft_putlong(elapsed(d->start_time) / 1000);
	write(1, "\t", 1);
	ft_putint(i_am);
	ft_putstr(status);
	write(1, "\n", 1);
	sem_post(d->lstatus);
}

/*void		drop_fork(sem_t *fork)*/
/*{*/
	/*sem_post(fork);*/
	/*sem_post(fork);*/
/*}*/

/*void		grab_fork(t_data *d, t_philo *p)*/
/*{*/
	/*[>safe_lock(d->fork, &d->has_died);<]*/
	/*sem_wait(d->fork);*/
	/*if (d->has_died)*/
		/*exit(0);*/
	/*print_status(FORK, p->i_am, d);*/
	/*safe_lock(d->fork, &d->has_died);*/
	/*sem_wait(d->fork);*/
	/*if (d->has_died)*/
		/*exit(0);*/
	/*sem_wait(p->leat);*/
	/*p->eat_count++;*/
	/*p->ate_at = elapsed(d->start_time);*/
	/*print_status(EAT, p->i_am, d);*/
	/*sem_post(p->leat);*/
/*}*/

void		simulate(t_data *d, t_philo *p)
{
	while (1)
	{
		print_status(THINK, p->i_am, d);
		/*grab_fork(d, p);*/
		/*safe_lock(d->fork, &d->has_died);*/
		sem_wait(d->fork);
		if (d->has_died)
			exit(0);
		print_status(FORK, p->i_am, d);
		/*safe_lock(d->fork, &d->has_died);*/
		sem_wait(d->fork);
		if (d->has_died)
			exit(0);
		sem_wait(p->leat);
		p->eat_count++;
		p->ate_at = elapsed(d->start_time);
		print_status(EAT, p->i_am, d);
		sem_post(p->leat);
		usleep(d->time_eat);
		/*drop_fork(d->fork);*/
		sem_post(d->fork);
		sem_post(d->fork);
		print_status(SLEEP, p->i_am, d);
		usleep(d->time_sleep);
	}
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
	p->ate_at = elapsed(d->start_time);
	simulate(d, p);
	return (0);
}

