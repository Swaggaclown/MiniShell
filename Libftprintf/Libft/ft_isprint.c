/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_isprint.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdesbord <jdesbord@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/08 11:57:30 by jdesbord     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/09 11:33:55 by jdesbord    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}
