/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 18:58:09 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/01 19:57:50 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		print_forks(t_data *d, t_philo *p) {
	if (PFORKS) {
		pthread_mutex_lock(&d->lstatus);
		printf("%ld %d forks:\t", elapsed(d) / 1000, p->i_am);
		for (int i = 0; i < d->no_of_philo; i++) {
			printf("%d|", d->fork_status[i]);
		}
		printf("\n");
		pthread_mutex_unlock(&d->lstatus);
	}
}
