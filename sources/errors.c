#include "../includes/lemin.h"

static void     ft_error_3(int error_index, int *error)
{
    if (error_index == 551)
    {
        ft_putendl_fd("Error! Start room input is wrong!", 2);
        *error = 1;
    }
    else if (error_index == 552)
    {
        ft_putendl_fd("Error! End room input is wrong!", 2);
        *error = 1;
    }
    else if (error_index == 66)
    {
        ft_putendl_fd("Error! Link input is wrong!", 2);
        *error = 1;
    }
}

static void		ft_error_2(int error_index, int *error)
{
    if (error_index == 22)
    {
        ft_putendl_fd("Error! More than one start room is found!", 2);
        *error = 1;
    }
    else if (error_index == 33)
    {
        ft_putendl_fd("Error! More than one end room is found!", 2);
        *error = 1;
    }
    else if (error_index == 44)
    {
        ft_putendl_fd("Error! Wrong room or link!", 2);
        *error = 1;
    }
    else if (error_index == 55)
    {
        ft_putendl_fd("Room coordinates are not integers!", 2);
        *error = 1;
    }
    else
        ft_error_3(error_index, error);
}

int			ft_error(int error_index)
{
    int		error;

    error = 0;
    if (error_index == 1)
    {
        ft_putendl_fd("Error! Wrong amount of ants!", 2);
        error = 1;
    }
    else if (error_index == 2)
    {
        ft_putendl_fd("Error! Start room is not found!", 2);
        error = 1;
    }
    else if (error_index == 3)
    {
        ft_putendl_fd("Error! End room is not found!", 2);
        error = 1;
    }
    else
        ft_error_2(error_index, &error);
    return (error);
}