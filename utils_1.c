/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caigner <caigner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:18:46 by caigner           #+#    #+#             */
/*   Updated: 2024/06/15 22:11:43 by caigner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == 0)
		return (0);
	sign = 1;
	result = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		if ((result > 2147483647 && sign == 1) || sign == -1)
			return (-1);
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}

void	*ft_protect(void *ptr1, void *ptr2, void *ptr3, void *ptr4)
{
	if (ptr1)
		return (ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	if (ptr4)
		free(ptr4);
	return (NULL);
}

int	input_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		if (!av[i][0])
			return (0);
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (write(2, "gettimeofday failed\n", 20), -1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead == 1)
		return (pthread_mutex_unlock(&data->dead_lock), 1);
	return (pthread_mutex_unlock(&data->dead_lock), 0);
}
