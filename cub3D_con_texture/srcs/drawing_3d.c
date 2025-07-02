/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-ross <ade-ross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:13:01 by redei-ma          #+#    #+#             */
/*   Updated: 2025/07/02 17:12:19 by ade-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



// ========== CALCOLI GEOMETRICI ==========

/**
 * Ottiene il colore base per una specifica orientazione cardinale
 */
//old pre textures
/* static int	get_cardinal_color(int is_vertical, int positive_direction)
{
	if (is_vertical)
	{
		if (positive_direction)
			return (0xFFE66D);  // Giallo - Muro Ovest (raggio va verso Est)
		else
			return (0x95A5A6);  // Grigio - Muro Est (raggio va verso Ovest)
	}
	else
	{
		if (positive_direction)
			return (0xFF6B6B);  // Rosso - Muro Nord (raggio va verso Sud)
		else
			return (0x4ECDC4);  // Ciano - Muro Sud (raggio va verso Nord)
	}
} */

/**
 * Calcola l'altezza della parete sullo schermo
 * Formula: altezza = WIN_HEIGHT / distanza
 */
static int	calculate_wall_height(float wall_distance)
{
	return ((int)(WIN_HEIGHT / wall_distance));
}

/**
 * Calcola i punti di inizio e fine per disegnare la parete
 * Centra la parete verticalmente sullo schermo
 */
static void	calculate_draw_limits(int wall_height, int *draw_start, int *draw_end)
{
	*draw_start = -wall_height / 2 + WIN_HEIGHT / 2;
	*draw_end = wall_height / 2 + WIN_HEIGHT / 2;
	
	// Assicurati che non esca dai bordi dello schermo
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT - 1;
}

/**
 * Calcola il colore del muro basato sui dati DDA precisi
 */
/* // old pre textures
static int	calculate_wall_color(t_data *data)
{
	int		is_vertical;
	int		positive_direction;
	int		base_color;

	is_vertical = (data->last_dda.side == 0);
	if (is_vertical)
		positive_direction = (data->last_dda.ray_dir_x > 0);
	else
		positive_direction = (data->last_dda.ray_dir_y > 0);
	base_color = get_cardinal_color(is_vertical, positive_direction);
	return (base_color);
} */

/**
 * Applica la correzione fish-eye
 * Senza questa correzione, i muri ai lati sembrano curvati
 */
static float	apply_fisheye_correction(float wall_distance, float ray_angle, float player_angle)
{
	return (wall_distance * cos(ray_angle - player_angle));
}

// ========== DISEGNO COMPONENTI ==========

/**
 * Disegna il soffitto per una colonna
 * Dal top dello schermo fino all'inizio della parete
 */
static void	draw_ceiling_column(t_data *data, int x, int ceiling_end)
{
	int	y;

	y = 0;
	while (y < ceiling_end)
	{
		put_pixel_to_image(data->game->img, x, y, data->elements->ceiling_colour);
		y++;
	}
}

/**
 * Disegna la parete per una colonna
 * Dall'inizio alla fine della parete calcolata
 */
/* // old pre textures
static void	draw_wall_column(t_data *data, int x, int wall_start, int wall_end, int color)
{
	int	y;
	
	y = wall_start;
	while (y < wall_end)
	{
		put_pixel_to_image(data->game->img, x, y, color);
		y++;
	}
} */

/**
 * Disegna il pavimento per una colonna  
 * Dalla fine della parete al bottom dello schermo
 */
static void	draw_floor_column(t_data *data, int x, int floor_start)
{
	int	y;

	y = floor_start;
	while (y < WIN_HEIGHT)
	{
		put_pixel_to_image(data->game->img, x, y, data->elements->floor_colour);
		y++;
	}
}

// ========== RENDERING PRINCIPALE ==========

/**
 * Renderizza una singola colonna verticale dello schermo
 * Questa è la funzione che trasforma la distanza in 3D!
 */
/* static void	render_single_column(t_data *data, int x, float wall_distance)
{
	int		wall_height;
	int		draw_start;
	int		draw_end;
	int		wall_color;

	// 1. Calcola altezza della parete sullo schermo
	wall_height = calculate_wall_height(wall_distance);
	
	// 2. Calcola dove disegnare la parete (centrata verticalmente)
	calculate_draw_limits(wall_height, &draw_start, &draw_end);
	
	// 3. Calcola il colore basato sulla distanza
	wall_color = calculate_wall_color(data);
	
	// 4. Disegna i tre componenti della colonna
	draw_ceiling_column(data, x, draw_start);           // Sopra la parete
	draw_wall_column(data, x, draw_start, draw_end, wall_color);  // La parete
	draw_floor_column(data, x, draw_end);               // Sotto la parete
} */

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

/**
 * Calcola l'angolo per una specifica colonna X
 * Distribuisce il FOV su tutta la larghezza dello schermo
 */
static float	calculate_ray_angle(t_data *data, int column_x)
{
	float	angle_step;
	float	start_angle;

	angle_step = FOV_ANGLE / WIN_WIDTH;  // Quanto angolo per ogni pixel
	start_angle = data->player->angle - FOV_ANGLE / 2;  // Angolo più a sinistra
	return (start_angle + column_x * angle_step);
}

/**
 * Funzione principale che renderizza l'intera vista 3D
 * Lancia un raggio per ogni colonna dello schermo
 */
void	draw_3d_to_image(t_data *data)
{
	int		x;
	float	ray_angle;
	float	wall_distance;
	float	corrected_distance;

	x = 0;
	while (x < WIN_WIDTH)
	{
		// 1. Calcola l'angolo per questa colonna
		ray_angle = calculate_ray_angle(data, x);
		// 2. Lancia il raggio e trova la distanza al muro
		wall_distance = cast_ray_dda(data, 
			data->player->x, data->player->y, ray_angle);
		// 3. Applica correzione fish-eye
		corrected_distance = apply_fisheye_correction(wall_distance, 
			ray_angle, data->player->angle);
		// 4. Renderizza questa colonna
		render_single_column_textured(data, x, corrected_distance);
		x++;
	}
}

