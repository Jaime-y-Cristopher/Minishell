/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrdelchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:23:32 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/13 15:41:32 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_ptrdelchar(char *str, const char *chars)
{
	int		i;
	int		j;

	if (!str || !chars)
		return ;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!ft_strchr(chars, str[i]))
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}
