/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_correct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 01:39:59 by tjung             #+#    #+#             */
/*   Updated: 2022/03/04 01:51:24 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bcmd		: argument vector 0 번 index 값 - 빌트인 명령어 부분
// comp		: 비교할 빌트인 명령어 (const)
// comp_len	: 널문자 포함한 comp 문자열 길이
// return (1) - 올바른 빌트인 명령
// return (0) - 잘못된 빌트인 명령
int	ms_correct_builtin_cmd(char *bcmd, char *comp)
{
	int	comp_len;

	comp_len = ft_strlen(comp) + 1;
	if (!ft_strncmp(bcmd, comp, comp_len))
		return (1);
	return (0);
}
