/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elounejj <ounejjarmehdi@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 13:41:35 by elounejj          #+#    #+#             */
/*   Updated: 2022/02/23 11:56:44 by elounejj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*check_death(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	while (1)
	{
		if (env->should_die + 5 <= get_time())
		{
			*(env->args->died) = 1;
			lock_and_print('D', env, env->id);
			return (NULL);
		}
		else if (*env->all_full == env->args->number_of_philos)
			return (NULL);
		usleep(10);
	}
	return (NULL);
}

void	init_death_cases(t_env *env)
{
	env->should_die = get_time() + env->args->time_to_die;
	pthread_create(&env->health, NULL, check_death, env);
	pthread_detach(env->health);
}

void	*routine(void *arg)
{
	t_env	*env;

	env = arg;
	init_death_cases(env);
	while (1)
	{
		pthread_mutex_lock(&env->mutexs.fork[env->id]);
		lock_and_print('F', env, env->id);
		pthread_mutex_lock(&env->mutexs.fork[(env->id + 1) % \
				env->args->number_of_philos]);
		lock_and_print('F', env, env->id);
		lock_and_print('E', env, env->id);
		env->should_die = get_time() + env->args->time_to_die;
		usleep(to_microsec(env->args->time_to_eat));
		if (*env->all_full == env->args->number_of_philos)
			return (NULL);
		pthread_mutex_unlock(&env->mutexs.fork[env->id]);
		pthread_mutex_unlock(&env->mutexs.fork[(env->id + 1) % \
				env->args->number_of_philos]);
		lock_and_print('S', env, env->id);
		usleep(to_microsec(env->args->time_to_sleep));
		lock_and_print('T', env, env->id);
	}
	return (NULL);
}

void	initialize(t_args *args, t_env *env, \
	pthread_mutex_t *print, pthread_mutex_t *fork)
{
	int	i;
	int	died;
	int	all_full;

	i = 0;
	died = 0;
	all_full = 0;
	pthread_mutex_init(print, NULL);
	while (i < args->number_of_philos)
	{
		env[i].eating_count = 0;
		env[i].args = args;
		env[i].id = i;
		env[i].mutexs.fork = fork;
		env[i].mutexs.print = print;
		env[i].args->died = &died;
		env[i].all_full = &all_full;
		pthread_create(&env[i].philo, NULL, routine, &env[i]);
		pthread_detach(env[i].philo);
		usleep(100);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_env			*env;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	int				i;

	i = 0;
	if (!get_arguments(&args, argv, argc))
		return (1);
	env = malloc(sizeof(t_env) * args.number_of_philos);
	fork = malloc(sizeof(pthread_mutex_t) * (args.number_of_philos));
	args.start_time = get_time();
	while (i < args.number_of_philos)
		pthread_mutex_init(&fork[i++], NULL);
	initialize(&args, env, &print, fork);
	while (1)
	{
		if (*(env->args->died) == 1 || \
			*(env->all_full) == args.number_of_philos)
			break ;
		usleep(10);
	}
	destroy_and_free(env, fork, env);
}
