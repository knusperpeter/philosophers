/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caigner <caigner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:18:34 by caigner           #+#    #+#             */
/*   Updated: 2024/06/12 15:54:31 by caigner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define FORK 0
# define EAT 1
# define SLEEP 3
# define THINK 4
# define DEAD 5
# define FINISHED 6

typedef struct s_philo	t_philo;

typedef struct s_data
{
	long long		num_philos;
	long long		time_die;
	long long		time_eat;
	long long		time_sleep;
	long long		num_must_eat;
	int				dead;
	long long		finished_eating;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
}				t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	long long		last_meal;
	long long		times_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}				t_philo;

//utils.c
int			ft_atoi(const char *str);
void		*ft_protect(void *ptr1, void *ptr2, void *ptr3, void *ptr4);
long long	get_time(void);
void		u_sleep(t_data *data, long long time);
int			msg_print(t_philo *ph, int id);
void		destroy_philo(t_data *data);
int			dead(t_data *data);

//init.c
int			input_check(char **av);
int			init(t_data *philo, int ac, char **av);

//tasks.c
void		eating(void *philo);
void		sleeping_thinking(void *philo);

//routine.c
void		*routine(void *philo);

#endif
