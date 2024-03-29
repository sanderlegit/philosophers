/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   util_1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:51:23 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/11 13:05:55 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long int	res;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
		if (res > 2147483647UL && sign == 1)
			return (-1);
		else if (res > 2147483648UL && sign == -1)
			return (0);
	}
	return (sign * (int)res);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*us;
	size_t			i;

	us = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		us[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void		*block;

	block = (void *)malloc(count * size);
	if (!block)
		return (NULL);
	ft_bzero(block, count * size);
	return (block);
}

int	print_return(char *str, int ret)
{
	printf("philo: %s\n", str);
	return (ret);
}
