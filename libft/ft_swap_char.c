/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 09:54:56 by rzero             #+#    #+#             */
/*   Updated: 2018/12/13 18:49:46 by rzero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap_char(char **w1, char **w2)
{
	char *temp;

	temp = *w1;
	*w1 = *w2;
	*w2 = temp;
}
