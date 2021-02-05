/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_two.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 15:51:41 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/05 16:48:28 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <unistd.h>
/* pthread:		thread/mutex
** semaphore.h	sem
** fcntl.h		O_CREAT
** stdlib:		malloc
** stdio:		printf
** sys/time:	gettimeofday
** unistd:		usleep
*/


typedef struct			s_philo {
	int					i_am;
	long				ate_at;
	int					eat_count;
	int					full;
	sem_t				*leat;
	char				*semname;
}						t_philo;

typedef struct			s_data {
	int					no_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	int					no_full;
	sem_t				*fork;
	sem_t				*lstatus;
	int					alive;
	long				start_time;
	int					has_died;
	t_philo				*ph;
}						t_data;

# define PEATD	0
void		eat_debug(t_data *d, t_philo *p);
# define PARGD	1
void		arg_debug(t_data *d);
void		print_forks(t_data *d, int n1, int n);

void					parse_arg(int *res, char *arg, int *fail);
int						parse_args(t_data *d, int argc, char **argv);
int						check_args(t_data *d);

int						init_data(t_data *d);
int						start_threads(t_data *d);
void					manage_threads(t_data *d);
void					end_threads(t_data *d, pthread_t threads[]);

void					*a_philo(void *vstruct);
void					print_status(char *status, long time, int i_am, t_data *d);
void					safe_lock(sem_t *lock, int die);
void					grab_fork(t_data *d, t_philo *p);
void					drop_fork(t_data *d);

int						init_time(t_data *d);
long					elapsed(t_data *d);

int						ft_atoi(const char *str);
void					*ft_calloc(size_t count, size_t size);
void					ft_bzero(void *s, size_t n);
int						print_return(char *str, int ret);
char					*get_semname(int n);
#endif
