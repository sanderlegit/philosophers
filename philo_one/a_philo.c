/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   a_philo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 18:16:00 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/02 11:44:58 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** eating -> sleeping -> thinking
*/

void		print_status(char *status, long time, int i_am, t_data *d)
{
	pthread_mutex_lock(&d->lstatus);
	if (d->ph[i_am - 1].has_died != 1)
		printf("%ld\t\t%d %s\n", time, i_am, status);
	pthread_mutex_unlock(&d->lstatus);
}

void		drop_fork(t_data *d, t_philo *p)
{
	pthread_mutex_unlock(&d->fork_lock[p->i_am - 1]);
	if (p->i_am - 2 < 0)
		pthread_mutex_unlock(&d->fork_lock[d->no_of_philo - 1]);
	else
		pthread_mutex_unlock(&d->fork_lock[p->i_am - 2]);

	d->fork_status[p->i_am - 1] = 0;//Debug
	if (p->i_am - 2 < 0)//Debug
		d->fork_status[d->no_of_philo - 1] = 0;//Debug
	else//Debug
		d->fork_status[p->i_am - 2] = 0;//Debug
	print_forks(d, p);
}

void		grab_fork(t_data *d, t_philo *p)
{
	/*int		ready;*/

	/*pthread_mutex_lock(&d->lforks);*/
	/*ready = 0;*/
	/*if (d->fork_status[p->i_am - 1] == 0) {*/
		/*if (p->i_am - 2 < 0)*/
		/*{*/
			/*if (d->fork_status[d->no_of_philo - 1] == 0)*/
				/*ready = 1;*/
		/*}*/
		/*else*/
			/*if (d->fork_status[p->i_am - 2] == 0)*/
				/*ready = 1;*/
	/*}*/
	/*if (ready)*/
	/*{*/
		/*print_forks(d, p);*/
		pthread_mutex_lock(&d->fork_lock[p->i_am - 1]);
		print_status("has taken a fork", elapsed(d) / 1000, p->i_am, d);
		if (p->i_am - 2 < 0)
			pthread_mutex_lock(&d->fork_lock[d->no_of_philo - 1]);
		else
			pthread_mutex_lock(&d->fork_lock[p->i_am - 2]);
		print_status("has taken a fork", elapsed(d) / 1000, p->i_am, d);

		d->fork_status[p->i_am - 1] = p->i_am;//Debug
		if (p->i_am - 2 < 0)//Debug
			d->fork_status[d->no_of_philo - 1] = p->i_am;//Debug
		else//Debug
			d->fork_status[p->i_am - 2] = p->i_am;//Debug
		/*p->has_fork = 1;*/
	/*}*/
	/*pthread_mutex_unlock(&d->lforks);*/
}

void		*a_philo(void *vstruct)
{
	t_data	*d;
	t_philo	*p;

	d = vstruct;
	p = &d->ph[d->alive];
	d->alive++;
	p->i_am = d->alive;
	p->ate_at = elapsed(d);
	print_status("was born", elapsed(d) / 1000, p->i_am, d);
	while (!p->has_died)
	{
		print_status("is thinking", elapsed(d) / 1000, p->i_am, d);
		/*while (!p->has_fork)*/
		/*{*/
			grab_fork(d, p);
			/*if (p->has_died)*/
				/*break;*/
		/*}*/
		if (p->has_died)
			break;
		print_forks(d, p);
		/*print_status("has taken a fork", elapsed(d) / 1000, p->i_am, d);*/
		print_status("is eating", elapsed(d) / 1000, p->i_am, d);
		p->eat_count++;
		if (PEATD) {//Debug
			pthread_mutex_lock(&d->lstatus);//Debug
			printf("\t\t%d has eaten %d times, last %ld d%d\n", p->i_am, p->eat_count, (elapsed(d) - p->ate_at) / 1000, p->has_died);//Debug
			pthread_mutex_unlock(&d->lstatus);//Debug
		}//Debug
		p->ate_at = elapsed(d);
		usleep(d->time_eat);
		drop_fork(d, p);
		if (d->must_eat != -1 && p->eat_count >= d->must_eat)
			break;
		print_status("is sleeping", elapsed(d) / 1000, p->i_am, d);
		usleep(d->time_sleep);
	}
	/*if (d->no_of_philo == d->alive)*/
		/*print_status("died", elapsed(d) / 1000, p->i_am, d);*/
	if (PEATD) {//Debug
		pthread_mutex_lock(&d->lstatus);//Debug
		printf("\t\t%d has eaten %d times, last %ld\n", p->i_am, p->eat_count, (elapsed(d) - p->ate_at) / 1000);//Debug
		pthread_mutex_unlock(&d->lstatus);//Debug
	}//Debug
	d->alive--;
	return (0);
}

