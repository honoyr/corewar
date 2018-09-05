/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:29:57 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/05 21:29:59 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	exec_and(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int		res;

	//ft_printf("I'm here!\n");
	res = arg_fin(process, arg[0], arg_type[0]) & arg_fin(process, arg[1], arg_type[1]);
	process->reg[arg[2] - 1] = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

void	exec_or(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int		res;

	res = arg_fin(process, arg[0], arg_type[0]) | arg_fin(process, arg[1], arg_type[1]);
	process->reg[arg[2] - 1] = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

void	exec_xor(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int		res;

	res = arg_fin(process, arg[0], arg_type[0]) ^ arg_fin(process, arg[1], arg_type[1]);
	process->reg[arg[2] - 1] = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

void	exec_zjmp(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	if (process && arg && arg_type)
		return ;
}

void	exec_ldi(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	unsigned int	res;
	int				delta;
	int				arg_1;
	int				arg_2;
	int				dst;

	res = 0;
	delta = 0;
	dst = arg[2];
	arg_1 = arg_fin(process, arg[0], arg_type[0]);
	arg_2 = arg_fin(process, arg[1], arg_type[1]);
	if (arg_type[0] == T_DIR && arg_type[1] == T_DIR)
		delta = (short)arg_1 + (short)arg_2;
	else if (arg_type[0] == T_DIR)
		delta = (short)arg_1 + arg_2;
	else if (arg_type[1] == T_DIR)
		delta = arg_1 + (short)arg_2;
	else
		delta = arg_1 + arg_2;
	res = extract_ind(process, delta, IDX_MOD);
	
	//del
	// if (g_game.cycle == 2510)
	// {
	// 	ft_printf("process->pc = %d, delta = %d, reg_dst = %d\n", process->pc, delta, dst);
	// 	ft_printf("res = %d\n", res);
	// }
	//del
	process->reg[dst - 1] = res;
}
