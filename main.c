/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caigner <caigner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:18:57 by caigner           #+#    #+#             */
/*   Updated: 2024/06/19 15:56:45 by caigner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	dead_philo(t_philo *p)
{
	long	time;

	time = get_time();
	if (time == -1)
		return (-1);
	pthread_mutex_lock(&p->data->eat_lock);
	if (time - p->last_meal >= (long)p->data->time_die)
	{
		msg_print(p, DEAD);
		pthread_mutex_unlock(&p->data->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(&p->data->eat_lock);
	return (0);
}

void	check_philos(t_data *data)
{
	long long	i;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&data->eat_lock);
		if (data->finished_eating == data->num_philos)
		{
			pthread_mutex_unlock(&data->eat_lock);
			return ;
		}
		pthread_mutex_unlock(&data->eat_lock);
		while (i < data->num_philos)
		{
			if (dead_philo(&data->philos[i]))
				return ;
			i++;
		}
		usleep(300);
	}
}

int	join_threads(t_data *data, int i)
{
	while (i-- > 0)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (0);
	}
	return (1);
}

int	start(t_data *data)
{
	long long	i;

	data->start_time = get_time();
	if (data->start_time == -1)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]))
		{
			join_threads(data, i);
			return (0);
		}
		pthread_mutex_lock(&data->eat_lock);
		data->philos[i].last_meal = get_time();
		if (data->philos[i].last_meal == -1)
			return (0);
		pthread_mutex_unlock(&data->eat_lock);
		i++;
	}
	check_philos(data);
	if (!join_threads(data, data->num_philos))
		return (write(2, "Error joining threads\n", 22), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (write(2, "Error, input has to be 4 or 5 numbers\n", 38), 1);
	if (!input_check(av))
		return (write(2, "Error, check input\n", 19), 1);
	if (!init(&data, ac, av))
		return (write(2, "Error, check input\n", 19), 1);
	if (!start(&data))
		return (destroy_philo(&data)
			, write(2, "Error at start of routine\n", 26), 1);
	destroy_philo(&data);
	return (0);
}
