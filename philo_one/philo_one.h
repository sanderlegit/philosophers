/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:51:41 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/01 17:51:49 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct		s_data {
	int				no_of_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	char			*fork_status;
	pthread_mutex_t l1;
	int				i_am;
}					t_data;

int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
int					print_return(char *str, int ret);
void				ft_bzero(void *s, size_t n);

void				parse_arg(int *res, char *arg, int *fail);
int					parse_args(t_data *d, int argc, char **argv);
void				*a_philo(void *vstruct);

#endif
