/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:31:57 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/05 21:32:00 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_player		*create_players(void)
{
	t_player		*player;
	t_lst_champs	*tmp;
	int				i;

	i = -1;
	if (!(player = (t_player *)malloc(sizeof(t_player) * g_game.players)))
	{
		perror("malloc() in create_players() failed ");
		error(-1);
	}
	while (++i < g_game.players)
	{
		tmp = g_game.champ;
		player[i].num = i + 1;
		player[i].name = ft_strdup(tmp->name);
		player[i].comment = ft_strdup(tmp->comment);
		player[i].comms = tmp->comms;
		player[i].len = tmp->size;
		player[i].start = (MEM_SIZE / g_game.players) * i;
		player[i].last_live = 0;
		player[i].lives_in_curr = 0;
		player[i].lives_in_curr_all = 0;
		g_game.champ = g_game.champ->next;
		free(tmp);
	}
	return (player);
}

unsigned char	*create_board(t_player *player)
{
	unsigned char	*board;
	int				i;

	i = -1;
	if (!(board = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
	{
		perror("malloc() in create_board() failed ");
		error(-1);
	}
	board = ft_memset(board, 0, MEM_SIZE);
	while (++i < g_game.players)
		ft_memcpy(&board[player[i].start], player[i].comms, player[i].len);
	return (board);
}

void			dump(void)
{
	int				i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
		{
			if (i != 0)
				ft_printf("\n");
			if (i == 0)
				ft_printf("0x0000 : ");
			else
				ft_printf("%#06x : ", i);
		}
		ft_printf("%02x ", g_game.board[i]);
		i++;
	}
	ft_printf("\n");
}

static void		introduce(void)
{
	int			i;
	t_player	*p;

	i = -1;
	p = g_game.player;
	ft_printf("Introducing contestants...\n");
	while (++i < g_game.players)
	{
		ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n", p[i].num, p[i].len, p[i].name, p[i].comment);
	}
}

static void		winner(void)
{
	int num;

	num = g_game.player_last_live;
	if (num >= 1 && num <= g_game.players)
	{
		if (!g_game.visu)
			ft_printf("Contestant %i, \"%s\", has won !\n", num, g_game.player[num - 1].name);
	}
}

void			start_game(void)
{
	g_game.player = create_players();
	g_game.board = create_board(g_game.player);
	g_game.proc = create_process(g_game.player);
	if (g_game.visu)
	{
		g_game.win = visual_init();
		draw_map(g_game.win);
	}
	else
	{
		introduce();
		if (g_game.v && g_game.number_v > 0)
			initialize_verb();
	}
	run_game();
	winner();
	clean_all();
	while (1);//del
	//dump();
	//free(player);
	//free(board);
	//free(change)
}
