/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libhelper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:19:17 by kczichow          #+#    #+#             */
/*   Updated: 2023/03/29 18:09:23 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* compares two strings */
int	ft_my_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) >= ft_strlen(s2))
	{
		while (i <= ft_strlen(s2) && s1 && s2 && (s1[i] || s2[i]))
		{
			if ((unsigned char) s1[i] - (unsigned char) s2[i] != 0)
				return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
		}
	}
	else if (ft_strlen(s1) < ft_strlen(s2))
	{
		while (i <= ft_strlen(s1) && s1 && s2 && (s1[i] || s2[i]))
		{
			if ((unsigned char) s1[i] - (unsigned char) s2[i] != 0)
				return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
		}
	}
	return (0);
}

/* joins two strings and a char */
char	*ms_multijoin(char const *s1, char c, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || ! s2)
		return (NULL);
	len = ft_strlen(s1) + 1 + ft_strlen(s2) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy(str + ft_strlen(s1), &c, 1);
	ft_memcpy(str + ft_strlen(s1) + 1, s2, ft_strlen(s2));
	*(str + ft_strlen(s1) + 1 + ft_strlen(s2)) = '\0';
	return (str);
}

// t_token	*ft_splitlst(t_token *tkn, t_env **env)
// {
// 	t_token	*echo;
// 	int		i;
// 	int		j;

// 	while (tkn->str && tkn->str[i])
// 	{
// 		i++;
// 		if (!(tkn->c_sta & SOME_Q) && ft_flag(tkn->str[i]) != tkn->c_sta)
// 		{
// 			if (tkn->str[i] & DOLLAR)
// 				&& ft_flag(tkn->str[i + 1]) & CHAR)
// 			{
// 				i++;
// 				while (ft_flag(tkn->str[i]) & CHAR)
// 					i++;
// 			}
// 			ft_go(tkn);
// 		}
// 		else if ((tkn->c_sta & SOME_Q) && ((tkn->c_sta & SOME_Q) == (ft_flag(tkn->str[tkn->curr]) & SOME_Q)))
// 			tkn->c_sta ^= (ft_flag(tkn->str[tkn->curr]) & SOME_Q);
// 		if (str[i] == '|')
// 		{
// 			ft_lstadd_back(&echo, ft_lstnew(ft_substr(str, j, i - j)));
// 			j = i;
// 		}
// 		i++;
// 	}
// 	if (i != j)
// 		ft_lstadd_back(&echo, ft_lstnew(ft_substr(str, j, i - j)));
// 	tmp_prtlst2(echo);
// 	return (echo);
// }