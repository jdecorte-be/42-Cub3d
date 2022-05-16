#include "../inc/cub3d.h"

void    find_spawn(char **map, t_data *data)
{
    int i = 0;
    int j;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
            {
                data->map->dirSpawn = map[i][j];
                data->pl->posX = i;
                data->pl->posY = j;
                break;
            }
            j++;
        }
        i++;
    }
}

void    init_var(t_data *data, int fd)
{
    char *str;
    char **s_str;
    while((str = get_next_line(fd)) != NULL)
    {
        s_str = ft_split(str, " ");
        if(ft_strcmp(str, "NO") == 0)
            data->map->NO = s_str[1];
        if(ft_strcmp(str, "SO") == 0)
            data->map->SO = s_str[1];
        if(ft_strcmp(str, "WE") == 0)
            data->map->WE = s_str[1];
        if(ft_strcmp(str, "EA") == 0)
            data->map->EA = s_str[1];
        if(ft_strcmp(str, "F") == 0)
            data->map->F = s_str[1];
        if(ft_strcmp(str, "C") == 0)
            data->map->T = s_str[1];
    }
}

char **parse_map(t_data *data, int fd)
{
    char *str;
    int i = 0;
    int len;
    int j;
    // data->map->NO = "./texture/WALL46.xpm";
    // data->map->SO = "./texture/WALL2.xpm";
    // data->map->WE = "./texture/WALL0.xpm";
    // data->map->EA = "./texture/WALL4.xpm";
	init_texture(data, 1, "./texture/wall0.xpm");
	init_texture(data, 2, "./texture/wall0.xpm");
	init_texture(data, 3, "./texture/wall0.xpm");
	init_texture(data, 4, "./texture/wall0.xpm");
	init_texture(data, 5, "./texture/potion.xpm");
	init_texture(data, 6, "./texture/door.xpm");



    // init_var(data);
    char **map = malloc(sizeof(char *) * (15 + 1)); // change len
    while((str = get_next_line(fd)))
    {
        j = 0;
        map[i] = malloc(sizeof(char) * (ft_strlen(str) + 1));
        ft_strlcpy(map[i], str, ft_strlen(str));
        i++;
    }
    map[i] = 0;
    // data->n_sprites = count_sprites(map);
    find_spawn(map, data);
    set_plane(data, data->map->dirSpawn);
    return map;
}