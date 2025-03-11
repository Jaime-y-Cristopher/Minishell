/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:37:10 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/20 10:37:11 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_arrdup(char **src_array)
{
	int		i;
	int		len;
	char	**dup;

	if (!src_array)
		return (NULL);
	len = ft_arrlen(src_array);
	dup = malloc(sizeof(char *) * len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = ft_strdup(src_array[i]);
		if (!dup[i])
			return (ft_freearr(dup), NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
