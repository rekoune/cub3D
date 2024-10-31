#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_directions{
	char *north;
	char *south;
	char *west;
	char *east;
} t_directions;

typedef struct s_colors{
	int	floor[3];
	int ceiling[3];
}t_colors;

typedef struct s_map_lst{
	char *content;
	struct s_map_lst *next;
}t_map_lst;

typedef struct s_map{
	t_directions directions;
	t_colors colors;
	t_map_lst *map_lst;
}t_map;


enum	e_type{
	DIRECTION,
	COLOR,
	MAP
};

//checking_map.c
t_map		*checking_map(char *map_file);

//utils.c
bool		str_comp(char *s1, char *s2);
int			str_len(char *str, char c);
int			ft_write (char *str, int rtrn);
char		*str_dup(char *str, int start, int size);
char		*str_join(char *s1, char *s2);
int			str_count(char **str);
long		ft_atoi(char *str);
void		free_2d(char **str, char *str2);
void		free_resources(t_map *map);

//ft_split.c
char		**ft_split(char *s, char c);

//linked_list.c
void		add_back(t_map_lst **head, t_map_lst *new_node);
t_map_lst	*new_node(char *str);

//check_map_utils.c
int			check_map_file(char *str);
bool		is_empty(char *str);
bool		is_last(t_map *map);
void		is_last_line(int map_fd);


#endif