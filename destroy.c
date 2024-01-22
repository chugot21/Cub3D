/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:15:18 by chugot            #+#    #+#             */
/*   Updated: 2023/12/27 19:15:21 by chugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	closew(t_game *game)
{
	//free(game->texture_one); //probleme pour free invalid pointer
	free(game->map);
	//destroy_all(game);
	write(1, "Don't give up... It's for the weak !\n", 37);
	exit(0);
}
