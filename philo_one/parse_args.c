/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 17:16:45 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/01 17:51:15 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
		parse_arg(&d->no_of_philo, argv[1], &fail);
		parse_arg(&d->time_die, argv[2], &fail);
		parse_arg(&d->time_eat, argv[3], &fail);
		parse_arg(&d->time_sleep, argv[4], &fail);
		if (argc == 6)
			parse_arg(&d->must_eat, argv[5], &fail);
		else
			d->must_eat = -1;
	}
	if ((argc != 5 && argc != 6) || fail)
		return (print_return("parse_args: invalid arguments", 1));
	printf("no_of_philo: %d\n time_die: %d\n time_eat: %d\n time_sleep: %d\n must_eat: %d\n", d->no_of_philo, d->time_die, d->time_eat, d->time_sleep, d->must_eat);
	return (0);
}
