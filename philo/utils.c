/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elounejj <ounejjarmehdi@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:12:54 by elounejj          #+#    #+#             */
/*   Updated: 2022/02/22 13:47:49 by elounejj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	to_microsec(int time)
{
	time *= 1000;
	return (time);
}

int	get_arguments(t_args *args, char **argv, int argc)
{
	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) <= 0 \
		|| ft_atoi(argv[2]) <= 59 \
		|| ft_atoi(argv[3]) <= 59 \
		|| ft_atoi(argv[4]) <= 59)
		return (0);
	args->number_of_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		args->number_of_times_must_eat = ft_atoi(argv[5]);
	return (1);
}

void	destroy_and_free(void *ptr1, void *ptr2, t_env *env)
{
	int	i;

	i = 0;
	while (i < env->args->number_of_philos)
		pthread_mutex_destroy(&env->mutexs.fork[i++]);
	pthread_mutex_destroy(env->mutexs.print);
	free(ptr1);
	free(ptr2);
}
