/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elounejj <ounejjarmehdi@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 18:41:28 by elounejj          #+#    #+#             */
/*   Updated: 2022/02/22 17:16:14 by elounejj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_args
{
	int		number_of_philos;
	int		time_to_eat;
	int		time_to_sleep;
	int		time_to_die;
	int		number_of_times_must_eat;
	int		start_time;
	int		*died;
}			t_args;

typedef struct s_mutexs
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
}			t_mutexs;

typedef struct s_env
{
	int			*all_full;
	int			id;
	pthread_t	philo;
	int			eating_count;
	pthread_t	health;
	t_args		*args;
	t_mutexs	mutexs;
	int			should_die;
}			t_env;

int		ft_atoi(const char *str);
int		to_microsec(int time);
int		eating_time(t_args *philo);
int		get_time(void);
void	printf_message(char *message, int time, int id);
void	lock_and_print(char p, t_env *env, int id);
int		mutex_lock_failed(int mutex);
int		mutex_unlock_failed(int mutex);
int		get_arguments(t_args *args, char **argv, int argc);
void	destroy_and_free(void *ptr1, void *ptr2, t_env *env);

#endif