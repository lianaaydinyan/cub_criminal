/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:08:06 by marihovh          #+#    #+#             */
/*   Updated: 2024/02/21 16:02:28 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../minilibx-linux/mlx.h"


void draw_colors(t_data *data);


int init_win(t_data *data)
{
    data->win_w = 640;
    data->win_h = 480;
	data->mlx->ptr = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->ptr, data->win_w,
       data->win_h, "Cub3d");
    return (0);
}

void draw_colors(t_data *data)
{
    int x = 0, y = 0;
    while (y < data->win_h / 2)
	{
        x = 0;
        while (x < data->win_w)
		{
            my_mlx_pixel_put(data, x, y, data->celling_c);
            x++;
        }
        y++;
    }
    y = data->win_h / 2;
    while (y < data->win_h)
	{
        x = 0;
        while (x < data->win_w)
		{
            my_mlx_pixel_put(data, x, y, data->flooring_c);
            x++;
        }
        y++;
    }
}



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && data->win_w > x && data->win_h > y)
	{
		dst = data->mlx->image.addr + (y * data->mlx->image.line_length + x
				* (data->mlx->image.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
int	ft_raycasting(t_data *data)
{ 
	int i;
	i = 0;
	while (i < screenWidth)
	{
		counting_delta_dist(data,i);
		calculate_step_init_side_dist_before_dd(data);
		ft_dda_algorithm(data);
		camera_frame_counting(data);
		ft_texture_calculation(data);
		textures_drawing(data, i);

		i++;
	}
	return (0);
}

void	coloring(t_data *data)
{
    int x = 0, y = 0;
    while (y < data->win_h / 2)
	{
		x = 0;
		while (x < data->win_w)
		{
			my_mlx_pixel_put(data, x, y, data->celling_c);
            x++;
		}
        y++;
	}
   	y = data->win_h / 2;
	while (y < data->win_h)
	{
			x = 0;
			while (x < data->win_w)
			{
			my_mlx_pixel_put(data, x, y, data->flooring_c);
			x++;
		}
		y++;
	}
}

void	qayl_araj(t_data *data)
{
	if (!(data->map[(int)(data->pos_x + data->dir_x * data->move_speed)][(int)data->pos_y]))
		data->pos_x += data->dir_x * data->move_speed;
	if (!(data->map[(int)data->pos_x][(int)(data->pos_y + data->dir_y * data->move_speed)]))
		data->pos_y += data->dir_y * data->move_speed;
}

void	qayl_het(t_data *data)
{
	printf("\n\nhet gna miqich\n\n");
	if (!(data->map[(int)(data->pos_x - data->dir_x * data->move_speed)][(int)data->pos_y]))
		data->pos_x -=data->dir_x * data->move_speed;
	if (!(data->map[(int)data->pos_x][(int)(data->pos_y - data->dir_y * data->move_speed)]))
		data->pos_y -=data->dir_y * data->move_speed;
}

void	depi_aj(t_data *data)
{
	double old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(-data->rot_speed) - data->dir_y * sin(-data->rot_speed);
	data->dir_y = old_dir_x * sin(-data->rot_speed) + data->dir_y * cos(-data->rot_speed);
	double old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(-data->rot_speed) - data->plane_y * sin(-data->rot_speed);
	data->plane_y = old_plane_x * sin(-data->rot_speed) + data->plane_y * cos(-data->rot_speed);
}

void	depi_dzax(t_data *data)
{
	double old_dir_x = data->dir_x;
	data->dir_x = data->dir_x * cos(data->rot_speed) - data->dir_y * sin(data->rot_speed);
	data->dir_y = old_dir_x * sin(data->rot_speed) + data->dir_y * cos(data->rot_speed);
	double	old_plane_x = data->plane_x;
	data->plane_x = data->plane_x * cos(data->rot_speed) - data->plane_y * sin(data->rot_speed);
	data->plane_y = old_plane_x * sin(data->rot_speed) + data->plane_y * cos(data->rot_speed);
}


void	moving(t_data *data)
{
	if (data->key.wu) // its for  W and up	
			qayl_araj(data);
	else if (data->key.al) // its for A and left
			depi_dzax(data);
	else if (data->key.sd) // its for S and down
			qayl_het(data);
	else if (data->key.dr) // its for D and rigth
			depi_aj(data);
}

int just_do_it(t_data *data)
{
	data->mlx->image.img = mlx_new_image(data->mlx->ptr, screenWidth, screenHeight);
	data->mlx->image.addr = mlx_get_data_addr(data->mlx->image.img , \
	&data->mlx->image.bits_per_pixel, &data->mlx->image.line_length, &data->mlx->image.endian);
	data->celling_c = 0x87CEEB;
    data->flooring_c = 0x0b701a;
    // draw_colors(data);
	ft_raycasting(data);
	moving(data);
	mlx_put_image_to_window(data->mlx->ptr, data->mlx->win, data->mlx->image.img, 0, 0);
	mlx_destroy_image(data->mlx->ptr , data->mlx->image.img);
	return (0);
}