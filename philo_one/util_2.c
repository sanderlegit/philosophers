/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:51:23 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/11 12:34:46 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

ssize_t	ft_putstr(char *s)
{
	int		i;
	ssize_t	ret;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	ret = write(1, s, i);
	if (ret == -1)
		return (-1);
	return (0);
}

ssize_t	ft_putint(int i)
{
	int		temp;
	int		pow;
	char	val;
	ssize_t	ret;

	temp = i;
	pow = 1;
	while (temp / 10)
	{
		temp = temp / 10;
		pow = pow * 10;
	}
	while (pow)
	{
		val = '0' + i / pow;
		ret = write(1, &val, 1);
		if (ret == -1)
			return (ret);
		i = i % pow;
		pow = pow / 10;
	}
	return (0);
}

ssize_t	ft_putlong(long i)
{
	long	temp;
	long	pow;
	char	val;
	ssize_t	ret;

	temp = i;
	pow = 1;
	while (temp / 10)
	{
		temp = temp / 10;
		pow = pow * 10;
	}
	while (pow)
	{
		val = '0' + i / pow;
		ret = write(1, &val, 1);
		if (ret == -1)
			return (ret);
		i = i % pow;
		pow = pow / 10;
	}
	return (0);
}

void	destruct_mutex(t_data *d)
{
	int		i;

	d->has_died = 1;
	if (d->mutex_check)
	{
		pthread_mutex_unlock(&d->lstatus);
		pthread_mutex_destroy(&d->lstatus);
		d->mutex_check--;
	}
	i = 0;
	while (i < d->no_philo)
	{
		if (d->fork && d->mutex_check)
		{
			pthread_mutex_unlock(&d->fork[i]);
			pthread_mutex_destroy(&d->fork[i]);
			d->mutex_check--;
		}
		if (d->ph && d->mutex_check)
		{
			pthread_mutex_unlock(&d->ph[i].leat);
			pthread_mutex_destroy(&d->ph[i].leat);
			d->mutex_check--;
		}
		i++;
	}
}

void	destruct_data(t_data *d)
{
	if (d->fork)
	{
		free(d->fork);
		d->fork = NULL;
	}
	if (d->ph)
	{
		free(d->ph);
		d->ph = NULL;
	}
}
