/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caigner <caigner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:18:44 by caigner           #+#    #+#             */
/*   Updated: 2024/06/15 22:09:08 by caigner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	u_sleep(t_data *data, long long time)
{
	long long	start;

	start = get_time();
	if (start == -1)
		return ;
	while (get_time() - start < time)
	{
		if (dead(data))
			break ;
		if (usleep(50) == -1)
			write(2, "usleep failed\n", 14);
	}
}

int	msg_print(t_philo *ph, int id)
{
	long long	time;

	pthread_mutex_lock(&ph->data->write_lock);
	if (!dead(ph->data))
	{
		time = get_time() - ph->data->start_time;
		if (id == FORK)
			printf("%ld %d has taken a fork\n", (long)time, ph->id);
		else if (id == EAT)
			printf("%ld %d is eating\n", (long)time, ph->id);
		else if (id == SLEEP)
			printf("%ld %d is sleeping\n", (long)time, ph->id);
		else if (id == THINK)
			printf("%ld %d is thinking\n", (long)time, ph->id);
		else if (id == DEAD)
		{
			pthread_mutex_lock(&ph->data->dead_lock);
			ph->data->dead = 1;
			pthread_mutex_unlock(&ph->data->dead_lock);
			printf("%ld %d died\n", (long)time, ph->id);
		}
		else if (id == FINISHED)
			printf("%ld %d\n", (long)time, ph->id);
	}
	return (pthread_mutex_unlock(&ph->data->write_lock), 1);
}

void	destroy_philo(t_data *data)
{
	long long	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->eat_lock);
	free(data->philos);
	free(data->forks);
}
