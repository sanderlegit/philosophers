/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 17:16:45 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/05 14:21:41 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			check_args(t_data *d)
{
	if (d->no_philo < 2 || d->no_philo > 200)
		return (1);
	if (d->time_die < 60000 || d->time_eat < 60000 || d->time_sleep < 60000)
		return (1);
	if (d->must_eat != -1 && d->must_eat <= 0)
		return (1);
	return (0);
}

void		parse_arg(int *res, char *arg, int *fail)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			*fail = 1;
		i++;
	}
	*res = ft_atoi(arg);
}

int			parse_args(t_data *d, int argc, char **argv)
{
	int		fail;

	if (argc >= 5 && argc <= 6)
	{
		fail = 0;
		parse_arg(&d->no_philo, argv[1], &fail);
		parse_arg(&d->time_die, argv[2], &fail);
		d->time_die *= 1000;
		parse_arg(&d->time_eat, argv[3], &fail);
		d->time_eat *= 1000;
		parse_arg(&d->time_sleep, argv[4], &fail);
		d->time_sleep *= 1000;
		if (argc == 6)
			parse_arg(&d->must_eat, argv[5], &fail);
		else
			d->must_eat = -1;
	}
	if ((argc != 5 && argc != 6) || fail || check_args(d))
		return (print_return("parse_args: invalid arguments", 1));
	return (0);
}
