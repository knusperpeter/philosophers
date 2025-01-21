/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caigner <caigner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:18:53 by caigner           #+#    #+#             */
/*   Updated: 2024/06/12 15:58:53 by caigner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	take_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->left_fork);
		pthread_mutex_lock(p->right_fork);
		msg_print(p, FORK);
		msg_print(p, FORK);
	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(p->left_fork);
		msg_print(p, FORK);
		msg_print(p, FORK);
	}
}

void	drop_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
	}
	else
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
	}
}

void	eating(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	take_forks(p);
	pthread_mutex_lock(&p->data->eat_lock);
	if (p->last_meal == -1)
		return ;
	p->last_meal = get_time();
	pthread_mutex_unlock(&p->data->eat_lock);
	msg_print(p, EAT);
	u_sleep(p->data, p->data->time_eat);
	drop_forks(p);
	if (usleep(50) == -1)
		write(2, "usleep failed\n", 14);
	if (p->data->num_must_eat != -1)
	{
		pthread_mutex_lock(&p->data->eat_lock);
		p->times_eaten++;
		pthread_mutex_unlock(&p->data->eat_lock);
	}
	if (usleep(50) == -1)
		write(2, "usleep failed\n", 14);
}

void	sleeping_thinking(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	msg_print(p, SLEEP);
	u_sleep(p->data, p->data->time_sleep);
	if (usleep(50) == -1)
		write(2, "usleep failed\n", 14);
	if (p->data->time_eat + p->data->time_sleep <= p->data->time_die)
	{
		msg_print(p, THINK);
		if (p->data->time_eat >= p->data->time_sleep)
		{
			u_sleep(p->data, p->data->time_eat - p->data->time_sleep);
			if (usleep(500) == -1)
				write(2, "usleep failed\n", 14);
		}
		if (p->data->time_eat < p->data->time_sleep)
		{
			u_sleep(p->data, p->data->time_sleep - p->data->time_eat);
			if (usleep(500) == -1)
				write(2, "usleep failed\n", 14);
		}
	}
}
