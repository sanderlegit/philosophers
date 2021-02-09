/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 18:58:09 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/02 13:13:45 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		arg_debug(t_data *d)
{
	if (PARGD) {
		printf("no_philo: %d\n time_die: %d\n time_eat: %d\n time_sleep: %d\n must_eat: %d\n", d->no_philo, d->time_die, d->time_eat, d->time_sleep, d->must_eat);//Debug
	}
}

void		create_fork_debug(t_data *d)
{
	d->fork_status = ft_calloc(d->no_philo, sizeof(char));
}

void		eat_debug(t_data *d, t_philo *p)
{
	if (PEATD) {
		pthread_mutex_lock(&d->lstatus);
		printf("\t%d has eaten %d times, last %ld\n", p->i_am, p->eat_count, (elapsed(d->start_time) - p->ate_at) / 1000);
		pthread_mutex_unlock(&d->lstatus);
	}
}

void		fork_debug(t_data *d, t_philo *p, int n)
{
	d->fork_status[p->i_am - 1] = n;
	if (p->i_am - 2 < 0)
		d->fork_status[d->no_philo - 1] = n;
	else
		d->fork_status[p->i_am - 2] = n;
	print_forks(d, p);
}

void		print_forks(t_data *d, t_philo *p)
{
	if (PFORKS) {
		pthread_mutex_lock(&d->lstatus);
		printf("%d forks\t", p->i_am);
		for (int i = 0; i < d->no_philo; i++) {
			printf("%d|", d->fork_status[i]);
		}
		printf("\n");
		pthread_mutex_unlock(&d->lstatus);
	}
}
