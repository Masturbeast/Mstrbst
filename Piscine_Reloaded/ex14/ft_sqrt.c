/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atep <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 19:02:41 by atep              #+#    #+#             */
/*   Updated: 2018/11/06 14:45:24 by atep             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int nb)
{
	int n;

	n = 1;
	if (nb < 0 || nb == 0)
		return (0);
	while (n < nb / n)
		n++;
	if (n * n == nb)
		return (n);
	return (0);
}
