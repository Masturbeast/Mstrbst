/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atep <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 18:48:07 by atep              #+#    #+#             */
/*   Updated: 2018/11/05 19:01:08 by atep             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_recursive_factorial(int nb)
{
	int n;

	if (nb == 0)
		return (1);
	if (nb < 0 || nb > 12)
		return (0);
	else
	{
		n = nb * ft_recursive_factorial(nb - 1);
	}
	return (n);
}
