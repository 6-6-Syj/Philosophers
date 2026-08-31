/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 18:46:30 by jmagand           #+#    #+#             */
/*   Updated: 2025-04-11 18:46:30 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define INT_MAX 2147483647

# define RST "\033[0m"
# define R "\033[1;31m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define B "\033[1;34m"
# define MGT "\033[1;35m"

# define FAIL_M_INIT "pthread_mutex_init failed"
# define FAIL_M_DESTROY "pthread_mutex_destroy failed"
# define FAIL_M_LOCK "pthread_mutex_lock failed"
# define FAIL_M_UNLOCK "pthread_mutex_unlock failed"

# define FAIL_THR_CREATE "pthread_create failed"
# define FAIL_THR_JOIN "pthread_join failed"

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST,
	TAKE_SECOND,
	DIED,
}						t_status;

typedef enum e_m_op
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
}						t_e_m_op;

typedef struct s_fork
{
	pthread_mutex_t		m_fork;
	int					debug_fork_id;
	bool				available;
	bool				initialized;
}						t_fork;

typedef struct s_params	t_params;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	long				t_last_meal;
	long				meals_count;
	bool				still_hungry;
	bool				is_eating;
	pthread_mutex_t		m_philo;
	bool				m_initialized;
	t_fork				*first_fork;
	t_fork				*second_fork;
	t_params			*params;
}						t_philo;

typedef struct s_params
{
	pthread_t			watcher;
	bool				watcher_created;
	long				x_philos;
	long				x_meals;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				t_start;
	bool				end_simulation;
	bool				philos_ready;
	long				x_philos_rdy;
	long				x_philos_created;
	pthread_mutex_t		m_params;
	pthread_mutex_t		m_print;
	t_fork				*forks;
	t_philo				*philos;
}						t_params;

/* TIME */
long					get_time(void);
long					get_elapsed_time(t_params *p);
void					ft_usleep(t_params *p, long milliseconds);
bool					is_dead(t_philo *philo);

/* PARSING */
bool					check_args(t_params *p, int ac, char **av);
bool					parse_args(t_params *p, char **av);

/* PARSING_UTILS */
int						check_overflow(long nb, int digit);
int						ft_atoi(const char *s);
bool					check_digit(char **av);
bool					ft_isdigit(char c);

/* INIT */
bool					init_params(t_params *p, int i);
bool					init_philo(t_params *p, int i);

/* UTILS */
bool					secure_mutex(pthread_mutex_t *mutex, t_e_m_op op);
void					increment_long(pthread_mutex_t *mutex, long *value);
bool					ft_write(int fd, char *s, bool ret);

/* GETTER_SETER */
bool					get_bool(pthread_mutex_t *mutex, bool *value);
void					set_bool(pthread_mutex_t *mutex, bool *dest,
							bool value);
long					get_long(pthread_mutex_t *mutex, long *value);
void					set_long(pthread_mutex_t *mutex, long *dest,
							long value);
bool					is_simulation_finished(t_params *p);

/* print */
void					print_action(t_philo *philo, t_status status);

/* ACTIONS */
void					lets_eat(t_philo *philo);
void					lets_sleep(t_philo *philo);
void					lets_think(t_philo *philo);
// A BOUGER
bool					start_simulation(t_params *p);

/* PHILOSOPHERS */
bool					create_philosophers(t_params *p, int i);
bool					join_philosophers(t_params *p);

/* WATCHER */
bool					are_all_philos_ready(t_params *p);
bool					create_watcher(t_params *p);

#endif
