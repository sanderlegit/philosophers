/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:51:41 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/01 20:01:51 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
/* pthread:		thread/mutex
** stdlib:		malloc
** stdio:		printf
** sys/time:	gettimeofday
** unistd:		usleep
*/

# define PFORKS	1
# define PEATD	1

typedef struct		s_data {
	//pthread_mutex_t lforks;
	int				no_of_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	char			*fork_status;
	pthread_mutex_t lstatus;
	int				i_am;
	long			start_time;
	int				has_died;
}					t_data;

typedef struct		s_philo {
	int				i_am;
	long			ate_at;
	char			has_fork;
	int				eat_count;
}					t_philo;

void		print_forks(t_data *d, t_philo *p);





int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
int					print_return(char *str, int ret);
void				ft_bzero(void *s, size_t n);

int					init_time(t_data *d);
long				elapsed(t_data *d);

void				parse_arg(int *res, char *arg, int *fail);
int					parse_args(t_data *d, int argc, char **argv);

void				print_status(char *status, long time, int i_am, t_data *d);
void				*a_philo(void *vstruct);

#endif
