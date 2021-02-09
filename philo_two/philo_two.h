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
/* pthread:		thread 
** semaphore.h	sem
** fcntl.h		O_CREAT
** stdlib:		malloc
** stdio:		printf
** sys/time:	gettimeofday
** unistd:		usleep, write
*/

# define FORK	" has taken a fork"
# define EAT	" is eating"
# define SLEEP	" is sleeping"
# define THINK	" is thinking"
# define DIED	" has died"

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

void					parse_arg(int *res, char *arg, int *fail);
int						parse_args(t_data *d, int argc, char **argv);
int						check_args(t_data *d);

int						init_data(t_data *d);
int						start_threads(t_data *d);
void					manage_threads(t_data *d);
void					end_threads(t_data *d, pthread_t threads[]);

void					*a_philo(void *vstruct);
void					print_status(char *status, int i_am, t_data *d);
void					simulate(t_data *d, t_philo *p);
//void					safe_lock(sem_t *lock, int *die);
//void					grab_fork(t_data *d, t_philo *p);
//void					drop_fork(sem_t *fork);

int						init_time(t_data *d);
long					elapsed(long start_time);

int						ft_atoi(const char *str);
void					*ft_calloc(size_t count, size_t size);
void					ft_bzero(void *s, size_t n);
int						print_return(char *str, int ret);
char					*get_semname(int n);

void					ft_putstr(char *s);
void					ft_putlong(long i);
void					ft_putint(int i);
void					destruct_sem(t_data *d);
void					destruct_data(t_data *d);
#endif
