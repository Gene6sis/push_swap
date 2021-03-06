/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortsecond.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 00:10:18 by adben-mc          #+#    #+#             */
/*   Updated: 2022/02/11 05:05:12 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	ft_movetopnb(t_stack	*stack, int nb)
{
	t_stack	*cur;
	int		i;

	i = 0;
	cur = stack;
	while (cur)
	{
		if (nb == cur->number)
		{
			if ((ft_lstsizebis(stack) / 2) >= i)
				return (i);
			else
				return (ft_lstsizebis(stack) - i);
		}
		i++;
		cur = cur->next;
	}
	return (0);
}

static int	ft_link(t_data *data, int valueb)
{
	t_stack	*cur;
	int		minmaj;

	cur = data->stacka;
	minmaj = cur->number;
	while (cur)
	{
		if (cur->number > valueb)
			minmaj = cur->number;
		cur = cur->next;
	}
	cur = data->stacka;
	while (cur)
	{
		if (minmaj > cur->number && cur->number > valueb)
			minmaj = cur->number;
		cur = cur->next;
	}
	return (minmaj);
}

static void	ft_movecheapest(t_data	*data, int a, int b)
{
	while (data->stackb->number != b || data->stacka->number != a)
	{
		if (data->stacka->number != a && ft_scrolldown_worth(data->stacka, a))
			rra(&(data->stacka), data);
		if (data->stackb->number != b && ft_scrolldown_worth(data->stackb, b))
			rrb(&(data->stackb), data);
		if (data->stacka->number != a && !ft_scrolldown_worth(data->stacka, a))
			ra(&(data->stacka), data);
		if (data->stackb->number != b && !ft_scrolldown_worth(data->stackb, b))
			rb(&(data->stackb), data);
	}
	pa(&(data->stackb), &(data->stacka), data);
}

static int	ft_nbmove(t_data *data, t_stack *cur)
{
	return ((ft_movetopnb(data->stacka, ft_link(data, cur->number))
			+ ft_movetopnb(data->stackb, cur->number)));
}

void	ft_sortsecond(t_data *data)
{
	t_stack	*cur;
	int		a;
	int		b;
	int		nb_move;

	cur = data->stackb;
	nb_move = ft_nbmove(data, cur);
	while (cur)
	{
		if (ft_nbmove(data, cur) <= nb_move)
		{
			a = ft_link(data, cur->number);
			b = cur->number;
			nb_move = ft_nbmove(data, cur);
		}
		cur = cur->next;
		if (!cur)
		{
			ft_movecheapest(data, a, b);
			cur = data->stackb;
			if (!cur)
				break ;
			nb_move = ft_nbmove(data, cur);
		}
	}
}
