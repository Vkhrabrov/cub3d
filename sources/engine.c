/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vadimhrabrov <vadimhrabrov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:06:48 by vkhrabro          #+#    #+#             */
/*   Updated: 2024/07/03 01:30:05 by vadimhrabro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_pixel(t_data *data, int x, int y, int color) {
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

// void draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
// {
//     int dx = abs(x1 - x0);
//     int dy = -abs(y1 - y0);
//     int sx = (x0 < x1) ? 1 : -1;
//     int sy = (y0 < y1) ? 1 : -1;
//     int err = dx + dy;
//     int e2;

//     while (1)
// 	{
//         put_pixel(data, x0, y0, color);
//         if (x0 == x1 && y0 == y1) break;
//         e2 = 2 * err;
//         if (e2 >= dy)
// 		{
//             err += dy;
//             x0 += sx;
//         }
//         if (e2 <= dx)
// 		{
//             err += dx;
//             y0 += sy;
//         }
//     }
// }


// void cast_ray(t_data *data)
// {
//     int x0 = data->player.x;
//     int y0 = data->player.y;
//     double fov = 33.0 * PI / 180.0; // 33 degrees to radians
//     int num_rays = 180; // Number of rays to cast
//     double angle_step = fov / num_rays;
//     double ray_angle;
//     int minimap_scale = 4;
//     int offset_x = 30;
//     int offset_y = WINDOW_HEIGHT - (data->map.height * (data->cell_size / minimap_scale)) - 20;

//     for (int i = -num_rays / 2; i <= num_rays / 2; i++) {
//         ray_angle = data->player.angle + i * angle_step;
//         double ray_x = x0;
//         double ray_y = y0;
//         double ray_dx = cos(ray_angle);
//         double ray_dy = sin(ray_angle);

//         int ray_length = data->player.ray_length;
//         int j;

//         for (j = 0; j < ray_length; j++) {
//             ray_x += ray_dx;
//             ray_y += ray_dy;

//             int map_x = (int)(ray_x / data->cell_size);
//             int map_y = (int)(ray_y / data->cell_size);

//             // Check if ray is out of bounds
//             if (map_x < 0 || map_x >= (int)data->map.width || map_y < 0 || map_y >= (int)data->map.height) {
//                 break;
//             }

//             // Check if ray hits a wall
//             if (data->map.array[map_y][map_x] == '1') {
//                 draw_line(data, x0 / minimap_scale + offset_x, y0 / minimap_scale + offset_y, (int)ray_x / minimap_scale + offset_x, (int)ray_y / minimap_scale + offset_y, PLAYER_COLOR);
//                 break;
//             }
//         }

//         // If no wall was hit, draw the ray to its maximum length
//         if (j >= ray_length) {
//             draw_line(data, x0 / minimap_scale + offset_x, y0 / minimap_scale + offset_y, (int)ray_x / minimap_scale + offset_x, (int)ray_y / minimap_scale + offset_y, PLAYER_COLOR);
//         }
//     }
// }

// int is_vertical_hit(double ray_x, double ray_y, double ray_dx, double ray_dy, int cell_size) {
//     double next_vertical_grid = (ray_dx > 0) ? ceil(ray_x / cell_size) * cell_size : floor(ray_x / cell_size) * cell_size;
//     double next_horizontal_grid = (ray_dy > 0) ? ceil(ray_y / cell_size) * cell_size : floor(ray_y / cell_size) * cell_size;

//     double vertical_distance = fabs((next_vertical_grid - ray_x) / ray_dx);
//     double horizontal_distance = fabs((next_horizontal_grid - ray_y) / ray_dy);

//     return vertical_distance < horizontal_distance ? 1 : 0; // 1 for vertical, 0 for horizontal
// }

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
            put_pixel(data, x, y, CEILING_COLOR);
            put_pixel(data, x, height - 1 - y, FLOOR_COLOR);
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

		// camera_plane: picture plane where the objects are casted. 
		// It is perpendicular to player's direction,so its unitary size is tan(fov/2)
		// That is, its length grows tan(fov/2) for each unit's displacement of the player's direction
        double plane_x = -ray_dir_y * tan(fov / 2);		// left part of the camera plane (from player's direction to left of screen)
        double plane_y = ray_dir_x * tan(fov / 2);		// right part of the camera plane (from player's direction to right of the screen)
        
		// 1. DERIVATION OF THE PERPENDICULAR VECTOR (see example at main's end)
		// 		For a vector (a, b), a vector perpendicular to it can be derived by swapping the components and changing the sign of one of them. Specifically:
		// 		If the original vector is (ray_dir_x, ray_dir_y), then a perpendicular vector would be (-ray_dir_y, ray_dir_x).
		// 2. Using the Perpendicular Vector to Define the Plane
		//		The camera plane is scaled based on the field of view (FOV). The full width of this plane at a unit distance from the player is determined by tan⁡(FOV/2)tan(FOV/2).
		// 3. Components of the Camera Plane
		//		Plane_X: This component of the camera plane is calculated as -ray_dir_y * tan(FOV / 2).
    	//		Plane_Y: This component of the camera plane is calculated as ray_dir_x * tan(FOV / 2).	

		// direction of the ray to the current column. As camera_x goes from -1 to 1 the ray sweeps the player's view
        double ray_x = ray_dir_x + plane_x * camera_x;	
        double ray_y = ray_dir_y + plane_y * camera_x;

		// convert the player's position to world/pixel coordinates to map grid coordinates
        int map_x = (int)(data->player.x / data->cell_size);	// x component of the map grid coordinates
        int map_y = (int)(data->player.y / data->cell_size);	// y component of the map grid coordinates

		/* ================================================================ *
		 *																	*
		 *  DDA (Digital Differential Analysis) algorithm 					*
		 *																	*
		 *  DDA Incrementally steps along a ray in a grid to determine		* 
		 *	which cells the ray intersects. It does this by calculating the *
		 *	distances to the next grid lines in both the x and y directions	* 
		 *	and advancing the ray step by step.								*         
		 * ================================================================ */

        double	side_dist_x;
		double	side_dist_y; // distance to closest map grid lines

		//	distance (movement units) the ray needs to travel to cross...
        double	delta_dist_x = fabs(1 / ray_x); // ...from one vertical grid line to the next one
												// delta_dist_x = sqrt(1 + (ray_y * ray_y / ray_x * ray_x))
        double	delta_dist_y = fabs(1 / ray_y); // ...from one horizontal grid line to the next one
												// delta_dist_y = sqrt(1 + (pow(ray_x, 2) / pow(ray_y, 2)))

		// steps indicate whether we are moving positively or negatively in the axis
        int step_x;	// positive movement
		int	step_y;	// negative movement
        int hit = 0;
        int side;

		// calculate the initial step, that is, the distance the ray has to travel from player's
		// position to the first horizontal and vertical grid lines
		// !!!!! map_x & map_y are the column and the row in the map the player is currently in
        if (ray_x < 0)	// x component of ray is negative --> player is looking to the left
		{
            step_x = -1;
			// - (player.x / cell_size) converts the player's coordinate from world space to grid space
			// - map_x is the x-coordinate of the grid cell the player is currently in
			// - (player.x / cell_size) - map_x calculates the fraction of the cell the player has already
			//		traversed in the x-direction. It will be always a value between 0 and 1.
			// - delta_dist_x is the distance ALONG THE RAY needed to move from one x-grid line to the next
			// --> the expression calculates the distance ALONG THE RAY to the next vertical grid line (x-side)
            side_dist_x = ((data->player.x / data->cell_size) - map_x) * delta_dist_x;
        }
		else	// x component of ray is positive --> player is looking to the right
		{
            step_x = 1;
			// - (map_x + 1.0) gives us the x-coordinate of the right edgo of the current cell
			// - (player.x / cell_size) converts the player's coordinate from world space to grid space
			// - (map_x + 1.0 - (data->player.x / data->cell_size)) calculates how far the player is
			//		from the right edge of the current cell, as a fraction of a cell width
			// - multiplying by delta_dist_x converts this fraction into the actual distance ALONG THE RAY
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
				// 1. Calculate the horizontal distance from the player's position to the hit wall's grid position along the x-axis
				// 2. Adjustment for the exact hit point within the grid cell:
				//		- if step_x is 1 (moving right), (1 - step_x) / 2 = 0, so no adjustment
				//		- If step_x is -1 (moving left), (1 - step_x) / 2 = 1, adding a full cell width
				//		The addition is necessary because the horizontal distance must be measured always from the player's position
				//		to the left edge of the wall cell that has been hit, so if the distance is negative a cell must be added
				// 3. Divide by ray's direction component to get true distance
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

int key_press(int keycode, t_data *data) {
    if (keycode == 65307) // ESC key code on MacOS
        close_window(data);
    else if (keycode == 65361) // Left arrow key for rotation
        data->player.rotate_left = 1;
    else if (keycode == 65363) // Right arrow key for rotation
        data->player.rotate_right = 1;
    else if (keycode == 65362 || keycode == 119) // Up arrow key or 'w' key
        data->player.move_forward = 1;
    else if (keycode == 65364 || keycode == 115) // Down arrow key or 's' key
        data->player.move_backward = 1;
    else if (keycode == 97) // 'a' key for left strafe
        data->player.strafe_left = 1;
    else if (keycode == 100) // 'd' key for right strafe
        data->player.strafe_right = 1;

    return 0;
}

int key_release(int keycode, t_data *data) {
    if (keycode == 65361) // Left arrow key for rotation
        data->player.rotate_left = 0;
    else if (keycode == 65363) // Right arrow key for rotation
        data->player.rotate_right = 0;
    else if (keycode == 65362 || keycode == 119) // Up arrow key or 'w' key
        data->player.move_forward = 0;
    else if (keycode == 65364 || keycode == 115) // Down arrow key or 's' key
        data->player.move_backward = 0;
    else if (keycode == 97) // 'a' key for left strafe
        data->player.strafe_left = 0;
    else if (keycode == 100) // 'd' key for right strafe
        data->player.strafe_right = 0;

    return 0;
}

void normalize_angle(double *angle) {
    while (*angle < 0) *angle += 2 * PI;
    while (*angle >= 2 * PI) *angle -= 2 * PI;
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
    double delta_time = 0.028135;
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

// int engine_main(t_data *data, t_textures *textures)
// {
//     // t_data data;

//     // Initialize player movement flags

// //     data->player.move_forward = 0;
// //     data->player.move_backward = 0;
// //     data->player.strafe_left = 0;
// //     data->player.strafe_right = 0;
// //     data->player.rotate_left = 0;
// //     data->player.rotate_right = 0;

// //     // // Calculate the cell size based on the map and window dimensions
// //     // int cell_size_width = WINDOW_WIDTH / data->map.width;
// //     // int cell_size_height = WINDOW_HEIGHT / data->map.height;
// //     // data->cell_size = (cell_size_width < cell_size_height) ? cell_size_width : cell_size_height;
// //     // data->player_size = data->cell_size / 2;
// //     // data->player.ray_length = data->cell_size * 100;

// //     data->mlx = mlx_init();
// //     if (data->mlx == NULL) {
// //         fprintf(stderr, "Failed to initialize mlx\n");
// //         return EXIT_FAILURE;
// //     }

// //     data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Grey Background");
// //     if (data->window == NULL) {
// //         fprintf(stderr, "Failed to create window\n");
// //         return EXIT_FAILURE;
// //     }

// //     data->image = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
// //     if (data->image == NULL) {
// //         fprintf(stderr, "Failed to create image\n");
// //         return EXIT_FAILURE;
// //     }

// //     data->addr = mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->line_length, &data->endian);
// //     if (data->addr == NULL) {
// //         fprintf(stderr, "Failed to get image data address\n");
// //         return EXIT_FAILURE;
// //     }

// //     (void)textures;
// //     // Load textures using map struct
// // 	data->north_texture.img = mlx_xpm_file_to_image(data->mlx, *(textures->paths_array[0]), &data->north_texture.width, &data->north_texture.height);
// // 	if (!data->north_texture.img) {
// // 		fprintf(stderr, "Failed to load north texture\n");
// // 		return EXIT_FAILURE;
// // 	}
// // 	data->north_texture.addr = mlx_get_data_addr(data->north_texture.img, &data->north_texture.bits_per_pixel, &data->north_texture.line_length, &data->north_texture.endian);

// //     data->south_texture.img = mlx_xpm_file_to_image(data->mlx, *(textures->paths_array[1]), &data->south_texture.width, &data->south_texture.height);
// //     if (!data->south_texture.img) {
// //         fprintf(stderr, "Failed to load south texture\n");
// //         return EXIT_FAILURE;
// //     }
// //     data->south_texture.addr = mlx_get_data_addr(data->south_texture.img, &data->south_texture.bits_per_pixel, &data->south_texture.line_length, &data->south_texture.endian);

// //     data->west_texture.img = mlx_xpm_file_to_image(data->mlx, *(textures->paths_array[3]), &data->west_texture.width, &data->west_texture.height);
// //     if (!data->west_texture.img) {
// //         fprintf(stderr, "Failed to load west texture\n");
// //         return EXIT_FAILURE;
// //     }
// //     data->west_texture.addr = mlx_get_data_addr(data->west_texture.img, &data->west_texture.bits_per_pixel, &data->west_texture.line_length, &data->west_texture.endian);

// //     data->east_texture.img = mlx_xpm_file_to_image(data->mlx, *(textures->paths_array[2]), &data->east_texture.width, &data->east_texture.height);
// //     if (!data->east_texture.img) {
// //         fprintf(stderr, "Failed to load east texture\n");
// //         return EXIT_FAILURE;
// //     }
// //     data->east_texture.addr = mlx_get_data_addr(data->east_texture.img, &data->east_texture.bits_per_pixel, &data->east_texture.line_length, &data->east_texture.endian);
    
    
// // //     // Calculate the cell size based on the map and window dimensions
// //     int cell_size_width = WINDOW_WIDTH / data->map.width;
// //     int cell_size_height = WINDOW_HEIGHT / data->map.height;
// //     data->cell_size = (cell_size_width < cell_size_height) ? cell_size_width : cell_size_height;
// //     data->player_size = data->cell_size / 2;
// //     data->player.ray_length = data->cell_size * 100;

// //     // Initialize prev_time
// //     // clock_gettime(CLOCK_MONOTONIC, &data->prev_time);
	
// //     render_background(data);
	
// //     mlx_hook(data->window, 17, 0, close_window, &data);
// //     mlx_hook(data->window, 2, 1L<<0, key_press, &data); // Handle key press
// //     mlx_hook(data->window, 3, 1L<<1, key_release, &data); // Handle key release
	

// //     mlx_loop_hook(data->mlx, main_loop, &data); // Main loop

// //     mlx_loop(data->mlx);

//     // Free the map data before exiting
//     // freeMap(&data->map);

//     return 0;
// }

/*
	EXAMPLE: DERIVATION OF THE PERPENDICULAR VECTOR

practical example where:
    ray_dir_x = 1
    ray_dir_y = 0

	The perpendicular vector defining the camera plane would indeed be:
    plane_x = 0
    plane_y = tan(FOV / 2)

Camera Plane Extension
    - Middle Ray: The player is facing directly along the x-axis (ray_dir_x = 1, ray_dir_y = 0).
    - Perpendicular Vector: The vector (-ray_dir_y, ray_dir_x) becomes (0, 1) before scaling.
    - Scaled Vector: After scaling by tan(FOV / 2), the perpendicular vector becomes (0, tan(FOV / 2)).

Interpretation
    - Extent of the Camera Plane: The camera plane extends symmetrically to the left and right of 
		the middle ray, perpendicular to the direction the player is facing. In this setup:
        	- It extends tan(FOV / 2) units upward and downward from the central direction.

Summary
    The camera plane extends equally to the left and right around the middle ray, covering the field
	of view symmetrically. Each side extends by tan(FOV / 2) units from the central direction at a unit
	distance, providing the correct angular coverage for the FOV.
*/
/*
	EXAMPLE WITH RAY COMPONENT VALUES DIFFERENT FROM ZERO

	Let's consider an example where both ray_dir_x and ray_dir_y have non-zero values. Suppose:
    ray_dir_x = 0.6
    ray_dir_y = 0.8

Perpendicular Vector Calculation
	To find the perpendicular vector for the camera plane:

    	Perpendicular Vector: (-ray_dir_y, ray_dir_x) becomes (-0.8, 0.6).

Scaling by FOV
	Assuming the FOV is such that:

    	tan⁡(FOV/2)tan(FOV/2) = 0.5 (this is just an example value)

The scaled components of the camera plane would be:
    	plane_x = −0.8×0.5=−0.4−0.8×0.5=−0.4
    	plane_y = 0.6×0.5=0.30.6×0.5=0.3

Interpretation
    The camera plane extends -0.4 units horizontally (leftward) and 0.3 units vertically (upward) from the center direction.

Direction of Rays
	When rays are cast across the screen:

		Middle Ray Direction: (0.6, 0.8)
		Left Edge of FOV: (0.6 - 0.4, 0.8 + 0.3) = (0.2, 1.1)
		Right Edge of FOV: (0.6 + 0.4, 0.8 - 0.3) = (1.0, 0.5)

	These vectors represent the boundaries of the rays cast from the player's position, covering the full field of view symmetrically around the middle ray.

Summary
	This setup allows each ray direction to be interpolated between the left and right edges, ensuring that the entire FOV is covered. The camera plane’s components help determine these directions accurately, simulating a realistic perspective in the rendered scene.
*/










