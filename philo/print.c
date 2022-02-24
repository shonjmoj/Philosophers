/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elounejj <ounejjarmehdi@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:31:54 by elounejj          #+#    #+#             */
/*   Updated: 2022/02/22 16:44:12 by elounejj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	printf_message(char *message, int time, int id)
{
	printf("%d ms %d %s", time, id + 1, message);
}

void	lock_and_print(char p, t_env *env, int id)
{
	pthread_mutex_lock(env->mutexs.print);
	if (p == 'F')
		printf_message("has taken a fork\n", \
			get_time() - env->args->start_time, id);
	else if (p == 'E')
	{
		printf_message("is eating\n", get_time() - env->args->start_time, id);
		env->eating_count += 1;
		if (env->args->number_of_times_must_eat == env->eating_count)
			*(env->all_full) += 1;
	}
	else if (p == 'S')
		printf_message("is sleeping\n", get_time() - env->args->start_time, id);
	else if (p == 'T')
		printf_message("is thinking\n", get_time() - env->args->start_time, id);
	else if (p == 'D')
	{
		printf_message("died\n", get_time() - env->args->start_time, id);
		return ;
	}
	pthread_mutex_unlock(env->mutexs.print);
}
