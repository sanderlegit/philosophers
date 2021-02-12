/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: averheij <averheij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/11 14:45:36 by averheij      #+#    #+#                 */
/*   Updated: 2021/02/12 14:10:35 by averheij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	run_simulation(t_data *d)
{
	d->is_parent = 1;
	d->pids = ft_calloc(d->no_philo, sizeof(int));
	if (!d->pids)
		return (print_return("run_simulation: failed to allocate pids", 1));
	d->threads = ft_calloc(d->no_philo, sizeof(pthread_t));
	if (!d->threads)
		return (print_return("run_simulation: failed to allocate threads", 1));
	if (init_time(d))
		return (1);
	if (start_threads(d))
		return (1);
	/*manage_threads(d);*/
	end_threads(d);
	return (0);
}

int	start_threads(t_data *d)
{
	int			i;

	/*i = 0;*/
	/*while (i < d->no_philo)*/
	/*{*/
		/*d->alive = i;*/
		/*if (pthread_create(&threads[i], NULL, a_philo, d))*/
			/*return (print_return("run_thread: failed to create thread", 1));*/
		/*i += 2;*/
		/*usleep(1000);*/
	/*}*/
	/*i = 1;*/
	/*while (i < d->no_philo)*/
	/*{*/
		/*d->alive = i;*/
		/*if (pthread_create(&threads[i], NULL, a_philo, d))*/
			/*return (print_return("run_thread: failed to create thread", 1));*/
		/*i += 2;*/
		/*usleep(1000);*/
	/*}*/
	i = 0;
	while (i < d->no_philo)
	{
		d->alive = i;
		d->pids[i] = fork();
		if (d->pids[i] == 0)
		{
			/*perror("I am kiddo");*/
			d->is_parent = 0;
			d->ph.i_am = i + 1;
			if (pthread_create(&d->threads[i], NULL, a_philo, d))
				return (print_return("run_thread: failed to create thread", 1));
			manage_threads(d); //rename to manage_thread
			destruct_data(d);
			perror("byebye");
			exit(0);
		}
		else if (d->pids[i] < 0)
			return (print_return("start_threads: failed to fork", 1));
		/*perror("made a bby");*/
		usleep(1000);
		i++;
	}
	return (0);
}

void	death(t_data *d)
{
	(void)d;
}

void	manage_threads(t_data *d)
{
	/*int		i;*/

	/*perror("i am manager :|");*/
	while (!d->has_died)
	{
		/*perror("yeet");*/
		/*i = 0;*/
		/*while (!d->has_died && i < d->no_philo)	//Same loop, but dont iterate over all children, end the process when death occurs*/
		/*{*/
		/*printf("waiting on this one %d\n", d->ph.i_am);*/
			sem_wait(d->ls[d->ph.i_am - 1].leat);
		/*perror("doing the food thing");*/
			if (d->m_eat != -1 && d->ph.eat_count >= d->m_eat)
			{
				/*d->no_full++;*/
				/*d->ph[i].full = 1;*/
				/*if (d->no_full == d->no_philo)*/
				/*perror("fat death :(");*/
				d->has_died = 1;
			}
			if ((elapsed(d->start_time) - d->ph.ate_at) > d->time_die)
			{
				/*perror("death :(");*/
				print_status(DIED, d->ph.i_am, d);
				d->has_died = 1;
			}
			sem_post(d->ls[d->ph.i_am - 1].leat);
			/*usleep(5000);*/
			/*i++;*/
		/*}*/
	}
}

void	end_threads(t_data *d)
{
	int		i;
	int		tmp;

	i = 0;
	while (i < d->no_philo)
	{
		/*perror("waiting on one");*/
		/*pthread_join(threads[i], NULL);*/
		waitpid(d->pids[i], &tmp, 0);
		d->pids[i] = 0;
		i++;
	}
	/*perror("done waiting");*/
	destruct_sem(d);
}
