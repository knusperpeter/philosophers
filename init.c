/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caigner <caigner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:18:49 by caigner           #+#    #+#             */
/*   Updated: 2024/06/19 15:53:18 by caigner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	allocation_data(t_data *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (0);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_philos);
	if (!data->forks)
		return (free(data->philos), 0);
	return (1);
}

int	init_forks(t_data *data)
{
	long long	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (i-- > 0)
			{
				pthread_mutex_destroy(&data->forks[i]);
			}
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].right_fork = &data->forks[i];
		data->philos[i].left_fork = &data->forks[(i + 1) % data->num_philos];
		i++;
	}
	return (1);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->num_philos = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_must_eat = ft_atoi(av[5]);
	else
		data->num_must_eat = -1;
	if (data->num_philos < 1 || data->time_die < 0 || data->time_eat < 0
		|| data->time_sleep < 0 || (ac == 6 && data->num_must_eat <= 0))
		return (0);
	data->dead = 0;
	data->finished_eating = 0;
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (0);
	if (pthread_mutex_init(&data->dead_lock, NULL))
		return (pthread_mutex_destroy(&data->write_lock), 0);
	if (pthread_mutex_init(&data->eat_lock, NULL))
		return (pthread_mutex_destroy(&data->write_lock),
			pthread_mutex_destroy(&data->dead_lock), 0);
	return (1);
}

void	init_philos(t_data *data)
{
	long long	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = 0;
		data->philos[i].times_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
}

int	init(t_data *data, int ac, char **av)
{
	if (!init_data(data, ac, av))
		return (0);
	if (!allocation_data(data))
		return (0);
	if (!init_forks(data))
		return (0);
	init_philos(data);
	return (1);
}
