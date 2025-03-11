/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rearroc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:59:00 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/14 10:59:02 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	freearr(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

char	**ft_rearroc(char **arr, size_t size_of, size_t cur_s, size_t new_s)
{
	char	**new_arr;
	size_t	i;

	if (new_s == 0)
		return (freearr(arr), NULL);
	new_arr = malloc(new_s * size_of);
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < cur_s && i < new_s)
	{
		new_arr[i] = arr[i];
		i++;
	}
	while (i < new_s)
		new_arr[i++] = NULL;
	free(arr);
	return (new_arr);
}
