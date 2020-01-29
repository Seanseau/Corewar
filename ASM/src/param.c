#include "../includes/asm.h"
#include <stdio.h>

int 	lexer_param(t_file *file, t_tab *tab, char *str)
{
	int 	i;

	printf("%s\n", str);
	i = 0;
	if (str[0] == 'r')
	{
		if (ft_atoi_2(str) <= REG_NUMBER)
		{
			if ((ft_strlen(str) == 3 && ft_atoi_2(str) >= 10) || (ft_strlen(str) == 2 && ft_atoi_2(str) < 10))
			{
				tab->info_ins[file->j].registre = ft_atoi_2(str);
				return (T_REG);
			}
			else
				return (ERROR_PARAM);
		}
		else
			return (ERROR_PARAM);
	}
	else if (str[0] == DIRECT_CHAR)
	{
		i = 2;
		if (str[1] == LABEL_CHAR)
		{
			if ((file->error = check_label(tab, &str[i])) < 1)
				return (file->error);
			if (!(tab->info_ins[file->j].direct_str = ft_strdup(&str[i])))
				return (ERROR_MALLOC);
			return (T_DIR);
		}
		i = 1;
		if (ft_atoi(&str[i]) || (ft_atoi(&str[i]) == 0 && ft_strchr(&str[i], '0')))
		{
			tab->info_ins[file->j].direct = ft_atoi(&str[i]);
			return (T_DIR);
		}
		else
			return (ERROR_PARAM);
	}
	else if (str[0] == LABEL_CHAR)
	{
		i = 1;
		if ((file->error = check_label(tab, &str[i])) < 1)
			return (file->error);
		if (!(tab->info_ins[file->j].indirect_str = ft_strdup(&str[i])))
			return (ERROR_MALLOC);
		return (T_IND);
	}
	else if (ft_atoi(&str[i]) || (ft_atoi(&str[i]) == 0 && ft_strchr(&str[i], '0')))
	{
		tab->info_ins[file->j].indirect = ft_atoi(&str[i]);
		return (T_IND);
	}
	return (ERROR_PARAM);
}

int 	ft_check_type(int d_type, int type)
{
	if (d_type == T_REG)
		if (type == T_REG)
			return (SUCCES);
	if (d_type == T_IND)
		if (type == T_IND)
			return (SUCCES);
	if (d_type == T_DIR)
		if (type == T_DIR)
			return (SUCCES);
	if (d_type == (T_REG + T_DIR))
		if (type == T_REG || type == T_DIR)
			return (SUCCES);
	if (d_type == (T_IND + T_DIR))
		if (type == T_IND || type == T_DIR)
			return (SUCCES);
	if (d_type == (T_IND + T_REG))
		if (type == T_IND || type == T_REG)
			return (SUCCES);
	if (d_type == (T_REG + T_DIR + T_IND))
		if (type == T_REG || type == T_DIR || type == T_IND)
			return (SUCCES);
	return (FAILURE);
}

int 	define_param(t_tab *tab, t_file *file)
{
	file->j = -1;
	while (++file->j < tab->nb_instruction)
	{
		//file->ligne_error = file->j add + real file
		file->i = -1;
		//printf("---[%d]\n", tab->info_ins[file->j].nb_parameter);

		while (++file->i < tab->info_ins[file->j].nb_parameter)
		{
			if ((file->type = lexer_param(file, tab, tab->info_ins[file->j].parameter[file->i])) < 1)
			{
				file->error = file->type; 
				return (file->error);
			}
			printf("ret = [%d]", file->type);
			if ((file->error = ft_check_type(file->op[tab->info_ins[file->j].id_inst - 1].params_type[file->i], file->type)) < 1)
				return (file->error);
			tab->info_ins[file->j].type_param[file->i] = file->type;
			printf("=[%d]\n", file->op[tab->info_ins[file->j].id_inst - 1].params_type[file->i]);
		}
		printf("\n");
	}
	return (SUCCES);
}