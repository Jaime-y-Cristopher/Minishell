/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:41:02 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/22 12:44:43 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_getenv(char *str, char **env)
{
	size_t	len;

	if (!str || !env)
		return (NULL);
	len = ft_strlen(str);
	while (*env)
	{
		if (ft_strncmp(*env, str, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}
