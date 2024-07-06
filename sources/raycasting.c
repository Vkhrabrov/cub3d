/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:40:36 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/06/06 20:44:16 by vkhrabro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void calculate_ray_direction(t_ray *ray, double player_angle) {
    ray->x = cos(ray->angle + player_angle);
    ray->y = sin(ray->angle + player_angle);
}

void cast_ray(t_data *data, t_ray *ray) {
    int map_x = (int)data->player.x / data->cell_size;
    int map_y = (int)data->player.y / data->cell_size;
    
    double side_dist_x;
    double side_dist_y;
    
    double delta_dist_x = fabs(1 / ray->x);
    double delta_dist_y = fabs(1 / ray->y);
    double perp_wall_dist;

    int step_x;
    int step_y;
    int hit = 0;
    int side;

    // Calculate step and initial side_dist
    if (ray->x < 0) {
        step_x = -1;
        side_dist_x = (data->player.x / data->cell_size - map_x) * delta_dist_x;
    } else {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - data->player.x / data->cell_size) * delta_dist_x;
    }
    if (ray->y < 0) {
        step_y = -1;
        side_dist_y = (data->player.y / data->cell_size - map_y) * delta_dist_y;
    } else {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - data->player.y / data->cell_size) * delta_dist_y;
    }

    // Perform DDA
    while (hit == 0) {
        // Jump to next map square, either in x-direction or y-direction
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        // Check if ray has hit a wall
        if (data->map.map_data[map_y][map_x] == '1') hit = 1;
    }

    // Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    if (side == 0) perp_wall_dist = (map_x - data->player.x / data->cell_size + (1 - step_x) / 2) / ray->x;
    else          perp_wall_dist = (map_y - data->player.y / data->cell_size + (1 - step_y) / 2) / ray->y;

    ray->distance = perp_wall_dist;
}

void cast_all_rays(t_data *data) {
    int num_rays = WINDOW_WIDTH;
    double fov = M_PI / 3; // 60 degrees field of view
    double angle_step = fov / num_rays;

    for (int i = 0; i < num_rays; i++) {
        t_ray ray;
        ray.angle = (i - num_rays / 2) * angle_step;
        calculate_ray_direction(&ray, data->player.angle);
        cast_ray(data, &ray);
        // Store the distance and other ray properties as needed
    }
}

void render_scene(t_data *data) {
    cast_all_rays(data);
    // Render the 3D scene based on ray distances
}