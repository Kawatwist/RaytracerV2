#include "rt.h"

int         initialize_cam(t_data *data)
{
    data->obj.camera.pos.origin = fill_vec(0, 0, 0);
    data->obj.camera.pos.direction = fill_vec(0, 0, 1);
    data->obj.camera.sc = fill_vec(-0.5, -0.5, 1.0);
    data->obj.camera.x = fill_vec(1.0 / data->window.xscreen, 0, 0);
    data->obj.camera.y = fill_vec(0, 1.0 / data->window.yscreen, 0);
    return (0);
}