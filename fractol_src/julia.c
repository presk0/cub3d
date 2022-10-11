/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/05/31 18:01:08 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static unsigned int	julia_pix_color(t_pt pt_parser, t_imgg *img)
{
	int		n;
	t_pt	zn;
	double	tmp;

	zn.x = pt_parser.x;
	zn.y = pt_parser.y;
	n = 0;
	while (n++ < img->quality && pow(zn.x, 2) + pow(zn.y, 2) < 4)
	{
		tmp = zn.x;
		zn.x = pow(zn.x, 2) - pow(zn.y, 2) + img->julia_coef.x;
		zn.y = 2 * tmp * zn.y + img->julia_coef.y;
	}
	if (n != img->quality)
		return (color_render(n * 255.0 / img->quality, img));
	return (0);
}

void	julia(t_imgg *img)
{
	t_pix	parser;
	t_pt	pt_parser;

	parser.x = 0;
	parser.y = 0;
	while (parser.y < (int)img->size[1] && parser.x < (int)img->size[0])
	{
		pt_parser = convert_pix_to_pt(img, parser, img->center);
		put_pix(img, parser, julia_pix_color(pt_parser, img));
		(parser.x)++;
		if (parser.x == (int)img->size[0])
		{
			parser.x = 0;
			(parser.y)++;
		}
	}
}
