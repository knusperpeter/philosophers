/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caigner <caigner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:18:55 by caigner           #+#    #+#             */
/*   Updated: 2024/06/12 15:53:49 by caigner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	all_full(t_philo *p)
{
	pthread_mutex_lock(&p->data->eat_lock);
	if (p->data->num_must_eat != -1 && (long)p->times_eaten
		>= p->data->num_must_eat)
	{
		p->data->finished_eating++;
		return (pthread_mutex_unlock(&p->data->eat_lock), 1);
	}
	return (pthread_mutex_unlock(&p->data->eat_lock), 0);
}

void	single_hungry(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	msg_print(philo, FORK);
	pthread_mutex_unlock(philo->right_fork);
	u_sleep(philo->data, philo->data->time_die);
}

void	*routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->data->num_philos == 1)
		return (single_hungry(p), NULL);
	if (p->id % 2 == 0)
		usleep(500);
	while (!dead(p->data))
	{
		eating(p);
		if (all_full(p))
			break ;
		sleeping_thinking(p);
	}
	return (NULL);
}
