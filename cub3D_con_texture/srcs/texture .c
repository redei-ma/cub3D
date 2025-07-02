#include "cub3D.h"

// ========== CARICAMENTO TEXTURE ==========
//MESSO
static int	load_single_texture_file(t_data *data, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	return (1);
}

int	init_all_texture_files(t_data *data)
{
	if (!load_single_texture_file(data, &data->elements->north,
			data->elements->north_texture))
		return (0);
	if (!load_single_texture_file(data, &data->elements->south,
			data->elements->south_texture))
		return (0);
	if (!load_single_texture_file(data, &data->elements->west,
			data->elements->west_texture))
		return (0);
	if (!load_single_texture_file(data, &data->elements->east,
			data->elements->east_texture))
		return (0);
	return (1);
}

// ========== SELEZIONE TEXTURE ==========

static t_texture	*get_wall_texture(t_data *data)
{
	if (data->last_dda.side == 1)
	{
		if (data->last_dda.ray_dir_y > 0)
			return (&data->elements->north);
		else
			return (&data->elements->south);
	}
	else
	{
		if (data->last_dda.ray_dir_x > 0)
			return (&data->elements->west);
		else
			return (&data->elements->east);
	}
}

// ========== CALCOLO COORDINATE TEXTURE ==========

static float	calc_wall_hit_position(t_data *data)
{
	float	wall_x;

	if (data->last_dda.side == 0)
		wall_x = data->player->y + data->last_dda.perp_wall_dist
			* data->last_dda.ray_dir_y;
	else
		wall_x = data->player->x + data->last_dda.perp_wall_dist
			* data->last_dda.ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	get_texture_pixel_x(t_texture *tex, float wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

static float	calc_texture_step(t_texture *tex, int wall_height)
{
	return ((float)tex->height / wall_height);
}

static float	calc_initial_texture_pos(int wall_start, int wall_height,
		float step)
{
	return ((wall_start - WIN_HEIGHT / 2 + wall_height / 2) * step);
}

// ========== LETTURA PIXEL TEXTURE ==========

static int	read_texture_pixel(t_texture *tex, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0 || tex_x >= tex->width
		|| tex_y < 0 || tex_y >= tex->height)
		return (0);
	pixel = tex->addr + (tex_y * tex->line_length
			+ tex_x * (tex->bits_per_pixel / 8));
	return (*(int *)pixel);
}

// ========== RENDERING TEXTURE ==========

static void	draw_texture_column_pixels(t_data *data, t_texture *tex,
		int screen_x, t_tex_render_data render_data)
{
	int		y;
	int		tex_y;
	int		color;
	float	tex_pos;

	y = render_data.wall_start;
	tex_pos = render_data.tex_pos;
	while (y < render_data.wall_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		tex_pos += render_data.step;
		color = read_texture_pixel(tex, render_data.tex_x, tex_y);
		put_pixel_to_image(data->game->img, screen_x, y, color);
		y++;
	}
}

void	draw_textured_wall_stripe(t_data *data, int screen_x, int wall_start,
		int wall_end, int wall_height)
{
	t_texture			*tex;
	t_tex_render_data	render_data;
	float				wall_x;

	tex = get_wall_texture(data);
	wall_x = calc_wall_hit_position(data);
	render_data.tex_x = get_texture_pixel_x(tex, wall_x);
	render_data.step = calc_texture_step(tex, wall_height);
	render_data.tex_pos = calc_initial_texture_pos(wall_start,
			wall_height, render_data.step);
	render_data.wall_start = wall_start;
	render_data.wall_end = wall_end;
	draw_texture_column_pixels(data, tex, screen_x, render_data);
}

// ========== CLEANUP ==========
//MESSO
void	free_all_texture_files(t_data *data)
{
	if (data->elements->north.img)
		mlx_destroy_image(data->game->mlx, data->elements->north.img);
	if (data->elements->south.img)
		mlx_destroy_image(data->game->mlx, data->elements->south.img);
	if (data->elements->west.img)
		mlx_destroy_image(data->game->mlx, data->elements->west.img);
	if (data->elements->east.img)
		mlx_destroy_image(data->game->mlx, data->elements->east.img);
}

/* ************************************************************************** */
/*                                                                            */
/*   MODIFICHE A dda.c - AGGIUNGI ALLA FINE DI cast_ray_dda                  */
/*                                                                            */
/* ************************************************************************** */

// Sostituisci la funzione cast_ray_dda con questa versione:
float	cast_ray_dda(t_data *data, float start_x, float start_y, float angle)
{
	t_dda	dda;
	int		hit;
	float	distance;

	init_dda_ray(&dda, start_x, start_y, angle);
	calc_delta_dist(&dda);
	calc_step_and_side_dist(&dda, start_x, start_y);
	hit = 0;
	while (!hit)
	{
		perform_dda_step(&dda);
		hit = is_wall_hit(data, dda.map_x, dda.map_y);
	}
	// Calcola distanza perpendicolare per texture
	if (dda.side == 0)
		dda.perp_wall_dist = (dda.map_x - start_x + (1 - dda.step_x) / 2)
			/ dda.ray_dir_x;
	else
		dda.perp_wall_dist = (dda.map_y - start_y + (1 - dda.step_y) / 2)
			/ dda.ray_dir_y;
	distance = dda.perp_wall_dist;
	data->last_dda = dda;
	return (distance);
}

/* ************************************************************************** */
/*                                                                            */
/*   MODIFICHE A drawing_3d.c - SOSTITUISCI draw_wall_column                 */
/*                                                                            */
/* ************************************************************************** */

// Sostituisci la funzione draw_wall_column con questa:
static void	draw_wall_column(t_data *data, int x, int wall_start, 
		int wall_end, int wall_height)
{
	draw_textured_wall_stripe(data, x, wall_start, wall_end, wall_height);
}

// E modifica render_single_column per passare wall_height:
static void	render_single_column(t_data *data, int x, float wall_distance)
{
	int		wall_height;
	int		draw_start;
	int		draw_end;

	wall_height = calculate_wall_height(wall_distance);
	calculate_draw_limits(wall_height, &draw_start, &draw_end);
	draw_ceiling_column(data, x, draw_start);
	draw_wall_column(data, x, draw_start, draw_end, wall_height);
	draw_floor_column(data, x, draw_end);
}







// ========== AGGIUNTE AL cub3D.h ==========

// Aggiungi questa struttura dopo le altre:
typedef struct s_tex_render_data
{
	int		tex_x;
	int		wall_start;
	int		wall_end;
	float	step;
	float	tex_pos;
}	t_tex_render_data;

// Modifica il t_dda per aggiungere perp_wall_dist:
typedef struct s_dda
{
	int		map_x;
	int		map_y;
	float	ray_dir_x;
	float	ray_dir_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	float	perp_wall_dist;  // <-- AGGIUNGI QUESTA LINEA
}	t_dda;

// Aggiungi questi prototipi alla fine:

// ========== TEXTURES.C ==========
int		init_all_texture_files(t_data *data);
void	draw_textured_wall_stripe(t_data *data, int screen_x, int wall_start,
			int wall_end, int wall_height);
void	free_all_texture_files(t_data *data);






/* ************************************************************************** */
/*                                                                            */
/*   main.c - VERSIONE MODIFICATA                                            */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char *argv[])
{
	t_data				data;
	t_basic_elements	elements_struct;
	t_player			player;

	if (handle_parsing(argc, argv, &elements_struct, &player) == 0)
		return (0);
	data.game = init_game();
	if (!data.game)
		return (1);
	data.player = &player;
	data.map = elements_struct.map;
	data.elements = &elements_struct;
	
	// INIZIALIZZA LE TEXTURE
	if (!init_all_texture_files(&data))
	{
		printf("Error: Failed to load textures\n");
		close_window(&data);
		return (1);
	}
	
	data.mini = init_minimap(data.map);
	draw_image(&data);

	mlx_hook(data.game->win, 17, 0, close_window, &data);
	mlx_hook(data.game->win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.game->win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.game->mlx, game_loop, &data);

	mlx_loop(data.game->mlx);
}



📋 Riassunto delle Modifiche Necessarie:
1. Creare textures.c

Usa tutto il codice del primo artifact

2. Modificare cub3D.h

Aggiungi t_tex_render_data
Aggiungi perp_wall_dist a t_dda
Aggiungi i prototipi delle funzioni texture

3. Modificare dda.c

Sostituisci cast_ray_dda con la versione che calcola perp_wall_dist

4. Modificare drawing_3d.c

Sostituisci draw_wall_column per usare le texture
Modifica render_single_column per passare wall_height

5. Modificare main.c

Aggiungi chiamata a init_all_texture_files()

6. Modificare events.c

Aggiungi free_all_texture_files() in close_window

🎯 Cosa Succederà:

Caricamento: Le texture .xpm verranno caricate all avvio
Selezione: Per ogni raggio, verrà scelta la texture corretta (N/S/E/W)
Mapping: La posizione del muro verrà mappata sulla texture
Rendering: Ogni colonna dello schermo mostrerà la texture appropriata

Il tuo codice è già molto ben strutturato, queste modifiche si integreranno perfettamente! 🚀







FUNZIONE PIU SEMPLICE

// ========== CARICAMENTO TEXTURE ==========

/**
 * Carica una singola texture da file
 */
int load_texture(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->game->mlx, path, 
										&texture->width, &texture->height);
	if (!texture->img)
		return (0);
	
	texture->addr = mlx_get_data_addr(texture->img, 
									 &texture->bits_per_pixel,
									 &texture->line_length, 
									 &texture->endian);
	return (1);
}

/**
 * Carica tutte le texture dal parsing
 */
int load_all_textures(t_data *data)
{
	if (!load_texture(data, &data->textures[0], data->elements->north_texture))
		return (0);
	if (!load_texture(data, &data->textures[1], data->elements->south_texture))
		return (0);
	if (!load_texture(data, &data->textures[2], data->elements->west_texture))
		return (0);
	if (!load_texture(data, &data->textures[3], data->elements->east_texture))
		return (0);
	return (1);
}

// ========== CALCOLO COORDINATE TEXTURE ==========

/**
 * Calcola quale texture usare basandosi sulla direzione del muro
 */
static int get_texture_index(t_data *data)
{
	if (data->last_dda.side == 1)  // Muro verticale
	{
		if (data->last_dda.ray_dir_y > 0)
			return (0);  // North texture
		else
			return (1);  // South texture
	}
	else  // Muro orizzontale
	{
		if (data->last_dda.ray_dir_x > 0)
			return (2);  // West texture
		else
			return (3);  // East texture
	}
}

/**
 * Calcola la coordinata X sulla texture (0.0 - 1.0)
 */
static float calculate_wall_x(t_data *data)
{
	float wall_x;
	
	if (data->last_dda.side == 0)  // Muro verticale
		wall_x = data->player->y + data->last_dda.perp_wall_dist * data->last_dda.ray_dir_y;
	else  // Muro orizzontale
		wall_x = data->player->x + data->last_dda.perp_wall_dist * data->last_dda.ray_dir_x;
	
	wall_x -= floor(wall_x);  // Mantieni solo la parte decimale
	return (wall_x);
}

/**
 * Ottiene il colore di un pixel dalla texture
 */
static int get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char    *pixel;
	
	if (tex_x < 0 || tex_x >= texture->width || 
		tex_y < 0 || tex_y >= texture->height)
		return (0);
	
	pixel = texture->addr + (tex_y * texture->line_length + 
							tex_x * (texture->bits_per_pixel / 8));
	return (*(int*)pixel);
}

// ========== RENDERING CON TEXTURE ==========

/**
 * Disegna una colonna di muro con texture
 */
static void draw_textured_wall_column(t_data *data, int x, int wall_start, 
									 int wall_end, int wall_height)
{
	t_texture   *texture;
	int         tex_index;
	float       wall_x;
	int         tex_x;
	int         tex_y;
	float       step;
	float       tex_pos;
	int         y;
	int         color;
	
	// 1. Determina quale texture usare
	tex_index = get_texture_index(data);
	texture = &data->textures[tex_index];
	
	// 2. Calcola coordinata X sulla texture
	wall_x = calculate_wall_x(data);
	tex_x = (int)(wall_x * texture->width);
	
	// 3. Calcola step per la coordinata Y
	step = (float)texture->height / wall_height;
	tex_pos = (wall_start - WIN_HEIGHT / 2 + wall_height / 2) * step;
	
	// 4. Disegna ogni pixel della colonna
	y = wall_start;
	while (y < wall_end)
	{
		tex_y = (int)tex_pos % texture->height;
		tex_pos += step;
		
		color = get_texture_color(texture, tex_x, tex_y);
		put_pixel_to_image(data->game->img, x, y, color);
		y++;
	}
}

// ========== MODIFICA AL RENDERING PRINCIPALE ==========

/**
 * Versione aggiornata della render_single_column con texture
 */
static void render_single_column_textured(t_data *data, int x, float wall_distance)
{
	int     wall_height;
	int     draw_start;
	int     draw_end;
	
	// 1. Calcola altezza della parete sullo schermo
	wall_height = calculate_wall_height(wall_distance);
	
	// 2. Calcola dove disegnare la parete
	calculate_draw_limits(wall_height, &draw_start, &draw_end);
	
	// 3. Disegna i componenti
	draw_ceiling_column(data, x, draw_start);
	draw_textured_wall_column(data, x, draw_start, draw_end, wall_height);  // <- TEXTURE!
	draw_floor_column(data, x, draw_end);
}

// ========== CLEANUP ==========

/**
 * Libera le texture alla chiusura
 */
void cleanup_textures(t_data *data)
{
	int i;
	
	i = 0;
	while (i < 4)
	{
		if (data->textures[i].img)
			mlx_destroy_image(data->game->mlx, data->textures[i].img);
		i++;
	}
}



