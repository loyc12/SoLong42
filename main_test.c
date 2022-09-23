#include "./so_long.h"

//clang -L ./mlx/ -lmlx -framework OpenGL -framework AppKit -lz -Wall -Wextra -Werror *.c *.h

int	findX(int x, int y, t_data d)
{
	int	X;

	X = ((d.aSize * (x - y)) + (d.wWidth - d.aSize)) / 2;
	return (X);
}

int	findY(int x, int y, int z, t_data d)
{
	int	Y;

	Y = ((d.aSize * (x + y)) - (z * d.aSize) + (2 * (d.wHeight - d.aSize)) - (d.aSize * d.bSize)) / 4;
	return (Y);
}

void put_image(int x, int y, int z, t_data d, char *path, mlx_t *mlx)
{
	int X;
	int Y;

	mlx_image_t *image = mlx_texture_to_image(mlx, mlx_load_png(path));	
	X = findX(x, y, d);
	Y = findY(x, y, z, d);
	mlx_image_to_window(mlx, image, X, Y);
}

int	main(void)
{
	t_data	d;
	d.wWidth = 2048;	//window width
	d.wHeight= 1024;	//window height
	d.aSize = 64;		//asset size
	d.bSize = 32;		//board size
	
	mlx_t		*mlx = mlx_init(d.wWidth, d.wHeight, "Test Window", true);
	mlx_image_t	*image = mlx_new_image(mlx, d.wWidth, d.wHeight);
	
	//puts the background colour
	memset(image->pixels, 128, image->width * image->height * sizeof(int32_t));
	mlx_image_to_window(mlx, image, 0, 0);

	//draws a plane of squares
	int	h;
	int	w;
	int X;
	int Y;

	mlx_image_to_window(mlx, mlx_texture_to_image(mlx, mlx_load_png("./Assets/Misc/NamePlate.png")), 0, 0);
	
	mlx_image_t *ground = mlx_texture_to_image(mlx, mlx_load_png("./Assets/Unboxed/Ground.png"));

	for(int y = 0; y < d.bSize; ++y)
	for(int x = 0; x < d.bSize; ++x)
	{
		X = findX(x, y, d);
		Y = findY(x, y, 0, d); //d.bSize - (x + z)
		if (-d.aSize < X && X < d.wWidth)
			if (-d.aSize < Y && Y < d.wHeight)
				mlx_image_to_window(mlx, ground, X, Y);
	}

	//displays a ball
	put_image(4, 2, 2, d,"./Assets/Misc/Ball.png", mlx);

	//displays a ball hole
	put_image(6, 9, 2, d, "./Assets/Misc/Hole.png", mlx);

	mlx_loop(mlx);
    mlx_terminate(mlx);

    return (0);
}
