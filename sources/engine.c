/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vadimhrabrov <vadimhrabrov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:06:48 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/07/06 18:29:47 by vadimhrabro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_pixel(t_data *data, int x, int y, unsigned int color) {
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
        char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

void draw_square(t_data *data, int x, int y, int size, int color) {
    for (int j = y; j < y + size; j++) {
        for (int i = x; i < x + size; i++) {
            put_pixel(data, i, j, color);
        }
    }
}

void draw_player(t_data *data, int x, int y, int size, int color) {
    draw_square(data, x - size / 2, y - size / 2, size, color);
}

void put_texture_pixel(t_data *data, int x, int y, int tex_x, int tex_y, t_textures *texture)
{
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0
		&& y < WINDOW_HEIGHT && tex_x >= 0
		&& tex_x < texture->width
		&& tex_y >= 0 && tex_y < texture->height)
	{
        char *src = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8));
        char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = *(unsigned int*)src;
    }
}

void cell_assignment(t_data *data, size_t i, size_t j, int color)
{
    color = -1;
    if (data->map.array[i][j] == '1')
        color = WALL_COLOR;
    else if (data->map.array[i][j] == '0')
        color = EMPTY_COLOR;
    else if (ft_strchr("NSEW", data->map.array[i][j]))
	{
        data->player.x = j * data->cell_size + data->cell_size / 2;
        data->player.y = i * data->cell_size + data->cell_size / 2;
        color = EMPTY_COLOR;
        if (data->map.array[i][j] == 'N') data->player.angle = 3 * PI / 2;
        if (data->map.array[i][j] == 'S') data->player.angle = PI / 2;
        if (data->map.array[i][j] == 'W') data->player.angle = PI;
        if (data->map.array[i][j] == 'E') data->player.angle = 0;
        data->map.array[i][j] = '0';
    }
    draw_square(data, data->offset_x + j * data->minimap_cell_size, data->offset_y + i * data->minimap_cell_size, data->minimap_cell_size, color);
}

void render_map(t_data *data)
{
    data->minimap_scale = 4; // Scale down the minimap by this factor
    data->minimap_cell_size = data->cell_size / data->minimap_scale;
    data->offset_x = 30; // Position from the left
    data->offset_y = WINDOW_HEIGHT - (data->map.height * data->minimap_cell_size) - 20; // Position from the bottom

    for (size_t i = 0; i < data->map.height; i++)
	{
        for (size_t j = 0; j < data->map.width; j++) 
		{
            if (j < ft_strlen(data->map.array[i]))
            {
                int color = -1;
                cell_assignment(data, i, j, color);
            }
        }
    }
}

int is_vertical_hit(double ray_dx, double ray_dy) {
    return fabs(ray_dx) > fabs(ray_dy);
}

void render_3d_view(t_data *data) {
    int width = WINDOW_WIDTH;
    int height = WINDOW_HEIGHT;
    double fov = 60.0 * PI / 180.0;
    int num_rays = width;
    
    // Fill ceiling and floor
    for (int y = 0; y < height / 2; y++) {
        for (int x = 0; x < width; x++) {
            put_pixel(data, x, y, data->colors.hex_ceiling);
            put_pixel(data, x, height - 1 - y, data->colors.hex_floor);
        }
    }

    // Render walls
    for (int x = 0; x < num_rays; x++) 
	{
		// coordinate x on the camera_plane (the screen column) the ray is pointing to (from -1 to 1)
        double camera_x = 2 * (x / (double)width) - 1;

		// player vector
        double ray_dir_x = cos(data->player.angle);
        double ray_dir_y = sin(data->player.angle);

        double plane_x = -ray_dir_y * tan(fov / 2);		// left part of the camera plane (from player's direction to left of screen)
        double plane_y = ray_dir_x * tan(fov / 2);		// right part of the camera plane (from player's direction to right of the screen)

        double ray_x = ray_dir_x + plane_x * camera_x;	
        double ray_y = ray_dir_y + plane_y * camera_x;

		// convert the player's position to world/pixel coordinates to map grid coordinates
        int map_x = (int)(data->player.x / data->cell_size);	// x component of the map grid coordinates
        int map_y = (int)(data->player.y / data->cell_size);	// y component of the map grid coordinates

        double	side_dist_x;
		double	side_dist_y; // distance to closest map grid lines

        double	delta_dist_x = fabs(1 / ray_x); // ...from one vertical grid line to the next one
												// delta_dist_x = sqrt(1 + (ray_y * ray_y / ray_x * ray_x))
        double	delta_dist_y = fabs(1 / ray_y); // ...from one horizontal grid line to the next one
												// delta_dist_y = sqrt(1 + (pow(ray_x, 2) / pow(ray_y, 2)))

		// steps indicate whether we are moving positively or negatively in the axis
        int step_x;	// positive movement
		int	step_y;	// negative movement
        int hit = 0;
        int side;

        if (ray_x < 0)	// x component of ray is negative --> player is looking to the left
		{
            step_x = -1;
            side_dist_x = ((data->player.x / data->cell_size) - map_x) * delta_dist_x;
        }
		else	// x component of ray is positive --> player is looking to the right
		{
            step_x = 1;
            side_dist_x = (map_x + 1.0 - (data->player.x / data->cell_size)) * delta_dist_x;
        }
        if (ray_y < 0)	// y component of ray is negative --> player is looking down
		{
            step_y = -1;
            side_dist_y = ((data->player.y / data->cell_size) - map_y) * delta_dist_y;
        }
		else	// y component of ray is negative --> player is looking up
		{
            step_y = 1;
            side_dist_y = (map_y + 1.0 - (data->player.y / data->cell_size)) * delta_dist_y;
        }

		// loop where we keep incrementing the length of the ray until a wall is hit or the ray goes out of bounds 
        while (hit == 0) 
		{
			// ray hit a vertical grid line
            if (side_dist_x < side_dist_y)
			{
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
			else // ray has hit a horizontal line
			{
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
			// check if ray is out of bounds
            if (map_x < 0 || map_y < 0 || map_x >= (int)data->map.width || map_y >= (int)data->map.height)
				break;
			// check the current map cell value, the loop goes on until the ray hits a wall
            if (data->map.array[map_y][map_x] == '1') hit = 1;
        }
	// calculating the height and position of the wall segment to be drawn on the screen after a ray has hit a wall
        if (hit == 1)
		{
			// store the perpendicular distance from the player to the wall, to avoid the fisheye effect.
            double perp_wall_dist;
            if (side == 0) // vertical wall hit
				perp_wall_dist = (map_x - data->player.x / data->cell_size + (1 - step_x) / 2) / ray_x;
            else // horizontal wall hit
				perp_wall_dist = (map_y - data->player.y / data->cell_size + (1 - step_y) / 2) / ray_y;

            int line_height = (int)(height / perp_wall_dist);

            int draw_start = -line_height / 2 + height / 2;
            if (draw_start < 0) draw_start = 0;
            int draw_end = line_height / 2 + height / 2;
            if (draw_end >= height) draw_end = height - 1;

            t_textures *texture;
            if (side == 0)
			{
                if (step_x > 0)
					texture = &data->west_texture;
				else
					texture = &data->east_texture;
            }
			else
			{
                if(step_y > 0)
					texture = &data->north_texture;
				else
					texture = &data->south_texture;
            }

            double wall_x;
            if (side == 0) wall_x = data->player.y / data->cell_size + perp_wall_dist * ray_y;
            else           wall_x = data->player.x / data->cell_size + perp_wall_dist * ray_x;
            wall_x -= floor(wall_x);

            int tex_x = (int)(wall_x * (double)texture->width);
            if (side == 0 && ray_x > 0) tex_x = texture->width - tex_x - 1;
            if (side == 1 && ray_y < 0) tex_x = texture->width - tex_x - 1;

            double step = 1.0 * texture->height / line_height;
            double tex_pos = (draw_start - height / 2 + line_height / 2) * step;
            for (int y = draw_start; y < draw_end; y++) {
                int tex_y = (int)tex_pos & (texture->height - 1);
                tex_pos += step;
                put_texture_pixel(data, x, y, tex_x, tex_y, texture);
            }
        }
    }
}

int render_background(t_data *data) {
    render_3d_view(data); // Render the 3D view
    render_map(data); // Render the minimap (keeping your existing minimap rendering code)
    draw_player(data, data->player.x / 4 + 20, data->player.y / 4 + WINDOW_HEIGHT - (data->map.height * (data->cell_size / 4)) - 20, data->player_size / 4, PLAYER_COLOR); // Render the player on the minimap
    // cast_ray(data); // Cast rays for the minimap

    mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
    return 0;
}

int close_window(t_data *data) {
    mlx_destroy_window(data->mlx, data->window);
    exit(0);
}

//	Carlos Office mac key codes
int key_press(int keycode, t_data *data) {
    if (keycode == 53) // ESC key code on MacOS
        close_window(data);
    else if (keycode == 123) // Left arrow key for rotation
        data->player.rotate_left = 1;
    else if (keycode == 124) // Right arrow key for rotation
        data->player.rotate_right = 1;
    else if (keycode == 126 || keycode == 13) // Up arrow key or 'w' key
        data->player.move_forward = 1;
    else if (keycode == 125 || keycode == 1) // Down arrow key or 's' key
        data->player.move_backward = 1;
    else if (keycode == 0) // 'a' key for left strafe
        data->player.strafe_left = 1;
    else if (keycode == 2) // 'd' key for right strafe
        data->player.strafe_right = 1;

    return 0;
}

//	Carlos Office mac key codes
int key_release(int keycode, t_data *data) {
    if (keycode == 123) // Left arrow key for rotation
        data->player.rotate_left = 0;
    else if (keycode == 124) // Right arrow key for rotation
        data->player.rotate_right = 0;
    else if (keycode == 126 || keycode == 13) // Up arrow key or 'w' key
        data->player.move_forward = 0;
    else if (keycode == 125 || keycode == 1) // Down arrow key or 's' key
        data->player.move_backward = 0;
    else if (keycode == 0) // 'a' key for left strafe
        data->player.strafe_left = 0;
    else if (keycode == 2) // 'd' key for right strafe
        data->player.strafe_right = 0;

    return 0;
}

void normalize_angle(double *angle) {
    while (*angle < 0) *angle += 2 * PI;
    while (*angle >= 2 * PI) *angle -= 2 * PI;
}

int is_wall(t_data *data, double x, double y) {
    int map_x = (int)(x / data->cell_size);
    int map_y = (int)(y / data->cell_size);
    
    if (map_x < 0 || map_x >= data->map.width || 
        map_y < 0 || map_y >= data->map.height) {
        return 1;  // Treat out of bounds as a wall
    }
    
    return (data->map.array[map_y][map_x] == '1');
}

void side_movements(t_data *data, double move_speed)
{
    double cos_angle = cos(data->player.angle);
    double sin_angle = sin(data->player.angle);

    if (data->player.move_forward) 
    {
        data->player.x += move_speed * cos_angle;
        data->player.y += move_speed * sin_angle;
    }
    if (data->player.move_backward) 
    {
        data->player.x -= move_speed * cos_angle;
        data->player.y -= move_speed * sin_angle;
    }
    if (data->player.strafe_left) 
    {
        data->player.x += move_speed * cos(data->player.angle - PI / 2);
        data->player.y += move_speed * sin(data->player.angle - PI / 2);
    }
    if (data->player.strafe_right) 
    {
        data->player.x += move_speed * cos(data->player.angle + PI / 2);
        data->player.y += move_speed * sin(data->player.angle + PI / 2);
    }
}

void bounds_check(t_data *data, double original_x, double original_y)
{
    double half_size = data->player_size / 2.0;
    int left_x = ((data->player.x - half_size) / data->cell_size);
    int right_x = ((data->player.x + half_size) / data->cell_size);
    int top_y = ((data->player.y - half_size) / data->cell_size);
    int bottom_y = ((data->player.y + half_size) / data->cell_size);
    // Ensure the new position is not within a wall
    if (left_x >= 0 && right_x < (int)data->map.width &&
        top_y >= 0 && bottom_y < (int)data->map.height &&
        data->map.array[top_y][left_x] != '1' &&
        data->map.array[top_y][right_x] != '1' &&
        data->map.array[bottom_y][left_x] != '1' &&
        data->map.array[bottom_y][right_x] != '1') {
        // New position is valid, nothing to revert
    } else {
        // Revert to original position if new position is invalid
        data->player.x = original_x;
        data->player.y = original_y;
    }
}

void update_player(t_data *data) 
{
    double delta_time = 0.00855;
    double move_speed = data->cell_size * 15.0 * delta_time; // speed adjust
    double rot_speed = PI / 2.0 * delta_time; // rotation speed adjust
    // saving the original position
    double original_x = data->player.x;
    double original_y = data->player.y;
    if (data->player.rotate_left) 
    {
        data->player.angle -= rot_speed;
        normalize_angle(&data->player.angle);
    }
    if (data->player.rotate_right) 
    {
        data->player.angle += rot_speed;
        normalize_angle(&data->player.angle);
    }
    side_movements(data, move_speed);
    bounds_check(data, original_x, original_y);
}

int main_loop(t_data *data) {
    update_player(data);
    render_background(data);
    return 0;
}