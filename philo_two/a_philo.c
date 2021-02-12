/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   a_philo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 18:16:00 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/12 13:30:08 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

/*
** eating -> sleeping -> thinking
*/

ssize_t	ft_putchar(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (0);
}

void	print_status(char *status, int i_am, t_data *d)
{
	ssize_t		ret;

	sem_wait(d->lstatus);
	if (d->has_died)
		exit(0);
	ret = ft_putlong(elapsed(d->start_time) / 1000);
	ret += ft_putchar('\t');
	ret += ft_putint(i_am);
	ret += ft_putstr(status);
	ret += write(1, "\n", 1);
	if (ret < 0)
	{
		destruct_sem(d);		//TODO this doesnt seem right
		destruct_data(d);
		exit(1);
	}
	sem_post(d->lstatus);
}

void	simulate(t_data *d, t_philo *p)
{
	while (1)
	{
		print_status(THINK, p->i_am, d);
		sem_wait(d->fork);
		if (d->has_died)
			exit(0);
		print_status(FORK, p->i_am, d);
		sem_wait(d->fork);
		if (d->has_died)
			exit(0);
		sem_wait(p->leat);
		p->eat_count++;
		p->ate_at = elapsed(d->start_time);
		print_status(EAT, p->i_am, d);
		sem_post(p->leat);
		usleep(d->time_eat);
		sem_post(d->fork);
		sem_post(d->fork);
		print_status(SLEEP, p->i_am, d);
		usleep(d->time_sleep);
	}
}

void	*a_philo(void *vstruct)
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
