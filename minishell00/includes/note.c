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