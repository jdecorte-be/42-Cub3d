#include "../inc/cub3d.h"

void	update_fps(t_data *data)
{
	data->t->oldtime = data->t->time;
	// data->t->time = getTicks();
	double frametime = (data->t->time - data->t->oldtime ) / 1000.0;
	// printf("%f\n", 1.0 / frametime);
	data->t->ms = frametime * 5.0;
	data->t->rotspeed = frametime * 3.0;
}