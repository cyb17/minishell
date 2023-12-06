if (s[i] == '$')
			{
				tmp = expand_value(s, i, envlist);
				i++;
				if (tmp != NULL)
				{
					cpy2 = cpy;
					cpy = my_strjoin(cpy2, tmp);
					if (cpy2)
						free(cpy2);
					i++;
				}
				while ((s[i] >= '0' && s[i] <= '9') || s[i] == '_'
					|| (s[i] >= 'a' && s[i] <= 'z')
					|| (s[i] >= 'A' && s[i] <= 'Z'))
					i++;
			}

if (s[i + 1] == ' ' || s[i + 1] == '\0')
				{
					if (cpy == NULL)
						cpy = ft_strdup_section(s, i, i + 1);
					else
					{
						tmp = ft_strdup_section(s, i, i + 1);
						cpy2 = cpy;
						cpy = my_strjoin(cpy2, tmp);
						if (cpy2)
							free(cpy2);
						if (tmp != NULL)
							free(tmp);
					}
					i++;
				}

"" '$PWD  !'| $? cou'cou' | "$USER" $USE'R'

"" '$PWD  !' < | << $? >> cou'cou' | "$USER" $USE'R'

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = ptr;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!del)
		return ;
	if (lst)
	{
		(*del)(lst -> content);
		free(lst);
	}
}



test  a corriger :

minishell > <infile >outfile
Contenu de section_cmd : < infile outfile id = 1
tkn < : 5,
tkn infile : 3,
tkn outfile : 1,

minishell > "      " " OK"
Contenu de section_cmd :         OK id = 1
tkn OK : 1,

>>> devrait y avoir deux token aux espaces entre guillemets 

<infile<infile2 cat >outfile
1=CMD, 2=W, 3=INFILE, 4=OUTFILE, 5=REDIR_IN, 6=REDIR_OUT
value: < type: 5
value: infile type: 3
value: < type: 5
value: infile2 type: 3
value: cat type: 2
value: outfile type: 2