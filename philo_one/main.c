/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:46:29 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/01 17:36:49 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

# include <pthread.h>
/*
** eating -> sleeping -> thinking
*/

void		*a_philo(void *strct)
{
	t_data	*d = strct;
	int		i_am;

	i_am = d->i_am;
	d->i_am++;
	printf("Hi I am philo no.%d\n", i_am);
	return 0;
}

int			init_mutex(t_data *d)
{
    if (pthread_mutex_init(&d->l1, NULL) != 0)
        return print_return("Mutex initialization failed.", 1);
	return 0;
}

int			run_threads(t_data *d)
{
	pthread_t	threads[d->no_of_philo];
	int			i;

	d->i_am = 1;
	/*threads = ft_calloc(d->no_of_philo, sizeof(pthread_t));*/
	/*if (!threads)*/
		/*return print_return("Thread allocation failed", 1);*/

	i = 0;
	while (i < d->no_of_philo)
	{
		if (pthread_create(&threads[i], NULL, a_philo, d))
			return print_return("Failed to create thread", 1);
		i++;
	}
	i = 0;
	while (i < d->no_of_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return 0;
}

/*
** argv[1] number_of_pihlo:	no of philo, and no of forks
** argv[2] time_to_die:		milliseconds, max time since start last meal/simulation before death
** argv[2] time_to_eat:		milliseconds, duration to eat (2 forks)
** argv[2] time_to_sleep:	milliseconds, time spend sleeping
** argv[2] number_of_times_\
** each_philosopher_\
** must_eat:			(optional) stop after each philo eats x times (instead of stop on death)
*/

int			main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(&data, argc, argv))
		return 1;
	if (init_mutex(&data))
		return 1;
	if (run_threads(&data))
		return 1;
	return 0;
}
