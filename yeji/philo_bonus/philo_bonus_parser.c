/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgang <sgang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:55:33 by sgang             #+#    #+#             */
/*   Updated: 2021/10/22 23:55:34 by sgang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isspace(char ch)
{
	return ((ch >= 9 && ch <= 13) || ch == ' ');
}

static int	ft_isdigit(char ch)
{
	return (ch >= '0' && ch <= '9');
}

static int	ft_atoi(char **num, int sign)
{
	int	ret;

	ret = 0;
	while (ft_isdigit(**num))
	{
		ret = ret * 10 + **num - '0';
		(*num)++;
	}
	if (sign < 0)
		ret = ret * sign;
	return (ret);
}

t_status	*parser(int ac, char **ag, t_status *st)
{
	int		idx;
	char	*iter;

	idx = 0;
	while (++idx < ac)
	{
		iter = *(ag + idx);
		while (ft_isspace(*iter))
			++iter;
		if (!ft_isdigit(*iter))
			return (NULL);
		st->info[idx - 1] = ft_atoi(&iter, 0);
		if (!*(st->info + idx - 1))
			return (NULL);
		while (ft_isspace(*iter))
			++iter;
		if (*iter != '\0')
			return (NULL);
	}
	return (st);
}
