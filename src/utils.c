/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camurill <camurill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:45:08 by joanavar          #+#    #+#             */
/*   Updated: 2024/12/03 20:01:26 by joanavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//#include "paquito.h"

int ft_strcmp(char *src, char *s)
{
	int i;

	i = 0;
	while (src[i] && src[i] == s[i])
		i++;
	if (src[i] == '\0' && s[i] == '\0')
		return (1);
	return (0);
}

int change_malloc_token(t_token *str, t_env *env, int measure)
{
	int i;
	int j;
	int total;
	int res;

	i = ft_strlen(str->content);
	j = ft_strlen(env->content);
	if (measure > j)
	{
		res = measure - j;
		total = i - res;
	}
	else if (measure < j)
	{
		res = j - measure;
		total = i + res;
	}
	else 
		total = i;
	return (total);



}

/*int main ()
{
	const char *src = "PATH";
	char *s = "USER";
	if (ft_strcmp(src, s))
		printf("Son iguales");
	else if (!ft_strcmp(src, s))
		printf("No son iguales");
	else 
		printf("Algo va mal");
	return (0);
}
*/

