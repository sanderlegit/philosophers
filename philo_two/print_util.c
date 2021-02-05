/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 18:58:09 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/05 16:41:38 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		arg_debug(t_data *d)
{
	if (PARGD) {
		printf("no_philo: %d\n time_die: %d\n time_eat: %d\n time_sleep: %d\n must_eat: %d\n", d->no_philo, d->time_die, d->time_eat, d->time_sleep, d->must_eat);//Debug
	}
}

void		print_forks(t_data *d, int n1, int n)
{
	int i;
	sem_getvalue(d->fork, &i);
	printf("fork: %d\t%d-->%d\n", n, i + n1, i);
}

void		eat_debug(t_data *d, t_philo *p)
{
	if (PEATD) {
		/*pthread_mutex_lock(d->lstatus);*/
		sem_wait(d->lstatus);
		printf("\t%d has eaten %d times, last %ld\n", p->i_am, p->eat_count, (elapsed(d) - p->ate_at) / 1000);
		/*pthread_mutex_unlock(d->lstatus);*/
		sem_post(d->lstatus);
	}
}
