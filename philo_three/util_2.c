/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:51:23 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/12 13:19:51 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
