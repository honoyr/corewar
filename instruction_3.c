#include "corewar.h"

void	exec_sti(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int				value;
	int				delta;
	int				arg_2;
	int				arg_3;

	//del
	// if (process->num == 4 && g_game.cycle == 2535)
	// 	ft_printf("reg[4] = %u\n", process->reg[3]);
	//del
	value = arg_fin(process, arg[0], arg_type[0]);
	arg_2 = arg_fin(process, arg[1], arg_type[1]);
	arg_3 = arg_fin(process, arg[2], arg_type[2]);
	if (arg_type[1] == T_DIR && arg_type[2] == T_DIR)
		delta = (short)arg_2 + (short)arg_3;
	else if (arg_type[1] == T_DIR)
		delta = (short)arg_2 + arg_3;
	else if (arg_type[2] == T_DIR)
		delta = arg_2 + (short)arg_3;
	else
		delta = arg_2 + arg_3;
	store_value(process, value, delta, IDX_MOD);
}

void	exec_fork(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int			delta;
	int			pc;
	t_process	*new;

	new = NULL;
	delta = arg_fin(process, arg[0], arg_type[0]);
	// ft_printf("pc before = %d\n", process->pc);
	// ft_printf("delta = %hd\n", delta);
	pc = (process->pc + ((short)delta % IDX_MOD)) % MEM_SIZE;//???
	// ft_printf("pc after = %d\n", pc);
	new = new_process(NULL, process, pc);
	add_process(&(g_game.proc), new);
}

void	exec_lld(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int		res;

	res = arg_fin(process, arg[0], arg_type[0]);
	process->reg[arg[1] - 1] = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

void	exec_lldi(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	unsigned int	res;
	int				delta;
	int				dst;
	int				arg_1;
	int				arg_2;

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
	res = extract_ind(process, delta, 0);
	process->reg[dst - 1] = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

void	exec_lfork(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int			delta;
	int			pc;
	t_process	*new;

	new = NULL;
	delta = arg_fin(process, arg[0], arg_type[0]);
	pc = (process->pc + (short)delta) % MEM_SIZE;
	new = new_process(NULL, process, pc);
	add_process(&(g_game.proc), new);
}

void	exec_aff(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int		res;

	res = arg_fin(process, arg[0], arg_type[0]);
	res = res % 256;
	ft_printf("%c", res);//???
}
