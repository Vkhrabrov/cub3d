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