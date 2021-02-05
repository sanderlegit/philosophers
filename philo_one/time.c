/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 17:59:08 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/05 15:31:20 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			init_time(t_data *d)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) == -1)
		return (print_return("init_time: failed to get time", 1));
	d->start_time = (tp.tv_sec * 1000000) + tp.tv_usec;
	return (0);
}

long		elapsed(t_data *d)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) == -1)
		return (print_return("elapsed: failed to get time", 1));
	return (((tp.tv_sec * 1000000) + (tp.tv_usec)) - d->start_time);
}
