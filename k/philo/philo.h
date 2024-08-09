/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:11:44 by inkahar           #+#    #+#             */
/*   Updated: 2024/08/01 11:37:35 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RE "\033[0m"
# define BLACK "\033[30m"
# define W "\033[37m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define CYAN "\033[36m" 
# define MAGENTA "\033[35m"

# define DEBUG_MODE 0

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}						t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;
typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_c;
	bool				full;
	long				last_meal;
	t_fork				*one_fork;
	t_fork				*two_fork;
	pthread_t			thread_id;
	t_mtx				philo_mutex;
	t_table				*table;
}						t_philo;

struct					s_table
{
	long				philo_number;
	long				time_to_die;
	long				time_to_sleep;
	long				time_to_eat;
	long				limit_meals;
	long				start_sim;
	long				threads_run_nbr;
	pthread_t			monitor;
	bool				end_sim;
	bool				all_threads_ready_syn;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
	t_fork				*forks;
	t_philo				*philo;
};

size_t					ft_strlen(const char *str);
bool					parse(t_table *table, char **av);
void					*safe(size_t bytes);
void					start(t_table *table);
void					dataq_inti(t_table *table);
void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					get_bool(t_mtx *mutex, bool *value);
long					get_long(t_mtx *mutex, long *value);
void					set_long(t_mtx *mutex, long *dest, long value);
bool					simul_finished(t_table *table);
long					gettime(t_time_code time_code);
void					clean(t_table *table);
void					thinking(t_philo *philo, bool pre);
void					*dinner_sim(void *data);
void					wait_all_thread(t_table *table);
void					write_status(t_philo_status status, t_philo *philo,
							bool debug);
void					increase_long(t_mtx *mutex, long *value);
bool					safe_mutex(t_mtx *mutex, t_opcode opceode);
bool					safe_thread(pthread_t *thread, void *(*foo)(void *),
							void *data, t_opcode code);
void					precise_usleep(long usec, t_table *table);
bool					all_threads_runnig(t_mtx *mutex, long *threads,
							long philo_nbr);
void					*monitor_dine(void *data);
void					*lone_philo(void *arg);
void					de_syn_philo(t_philo *philo);
bool					ft_puterr(const char *error);
bool					valid_input(const char *str);
#endif