/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 16:57:08 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/09/07 19:45:46 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static WINDOW	*win_create(void)
{
	WINDOW		*win;

	win = newwin(70, 64 * 4 + 4, 0, 0);
	wrefresh(win);
	return (win);
}

WINDOW			*visual_init(void)
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
	start_color();
	curs_set(0);
	init_color(COLOR_WHITE, 400, 400, 400);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	return (win_create());
}
