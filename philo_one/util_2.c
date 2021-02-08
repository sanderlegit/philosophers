/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:51:23 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/05 16:26:03 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_putstr(char *s)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(1, s, i);
}

void	ft_putint(int i)
{
	int		temp;
	int		pow;
	char	val;

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
		write(1, &val, 1);
		i = i % pow;
		pow = pow / 10;
	}
}

void	ft_putlong(long i)
{
	long	temp;
	long	pow;
	char	val;

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
		write(1, &val, 1);
		i = i % pow;
		pow = pow / 10;
	}
}
