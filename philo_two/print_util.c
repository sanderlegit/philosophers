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
