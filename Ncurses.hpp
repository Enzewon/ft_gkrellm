/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ncurses.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 23:13:27 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/03/06 20:12:26 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSES_HPP
# define NCURSES_HPP

# include <curses.h>
# include <signal.h>
# include "IMonitorDisplay.hpp"
# include "CPUModule.hpp"
# include "KernelModule.hpp"
# include "RAMModule.hpp"
# include "DateModule.hpp"
# include "NetworkModule.hpp"
# include "InfoModule.hpp"

class Ncurses : public IMonitorDisplay
{

public:
	Ncurses();
	~Ncurses();
	Ncurses(Ncurses const &);
	Ncurses const&operator=(Ncurses const &);
	void    allplugins();

	CPUModule const &		getCPU() const;
	DateModule const &		getDate() const;
	KernelModule const &	getKernel() const;
	InfoModule const &		getInfo() const;
	RAMModule const &		getRAM() const;
	NetworkModule const &	getNetwork() const;
	WINDOW* 		        getMenu() const;
	int         		    getNumb() const;
	void    				setNumb(int);

	void	UserInfo();
	void    Memory();
	void    CPU();
	void    initplugin();
	void    OS();
	void    reload();
	void    printLeft();
	void    initStrMenu();
	void    printGr(int, int);
	void    Network();

private:

	CPUModule		_cpu;
	DateModule		_date;
	RAMModule		_ram;
	NetworkModule	_network;
	KernelModule	_kernel;
	InfoModule		_info;
	char *men[5];

	WINDOW *_menu;
	WINDOW *_data;
	int		numb;
	void ((Ncurses::*f[5]))();
	void init_visualisation() const;
	void printmenu();
};


#endif
