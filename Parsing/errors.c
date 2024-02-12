/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:37:34 by mgourlai          #+#    #+#             */
/*   Updated: 2024/02/08 18:37:35 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error_frees(t_game *game, int n)
{
	if (n >= 1)
	{
		if (!game->info_map.file)
			return ;
		free_map(game->info_map.file);
	}
	if (n >= 2)
	{
		if (!game->info_map.map)
			return ;
		free_map(game->info_map.map);
	}
	if (n >= 3)
	{
		if (!game->info_map.copy)
			return ;
		free_map(game->info_map.copy);
	}
	if (n >= 4)
	{
		if (!game->minimap)
			return ;
		free(game->minimap);
	}
}
