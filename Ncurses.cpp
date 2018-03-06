/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ncurses.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 23:13:18 by dvdovenk          #+#    #+#             */
/*   Updated: 2018/03/06 20:12:35 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ncurses.hpp"

void Ncurses::init_visualisation() const
{
	noecho();
	signal(SIGWINCH, nullptr);
	curs_set(0);
	start_color();
	keypad(_menu, true);
	keypad(_data, true);
	keypad(stdscr, true);
	nodelay(_menu, true);
	nodelay(stdscr, true);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	init_pair(3, COLOR_WHITE, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_RED, COLOR_BLACK);
}

Ncurses::~Ncurses()
{
	endwin();
}


void Ncurses::UserInfo()
{
	wattron(_data, COLOR_PAIR(3));
	mvwaddstr(_data, 2, 4, _info.getInfo("user").c_str());
	mvwaddstr(_data, 3, 4, _info.getInfo("host").c_str());
	mvwaddstr(_data, 4, 4, _date.getInfo("date").c_str());
	mvwaddstr(_data, 5, 4, _date.getInfo("time").c_str());
	wattrset(_data, A_NORMAL);
}

void Ncurses::Memory(){
	mvwaddstr(_data, 2, 4, _ram.getInfo("total").c_str());
	mvwaddstr(_data, 3, 4, _ram.getInfo("now").c_str());
}

void Ncurses::Network(){
	 mvwaddstr(_data, 2, 4, _network.getInfo("IP").c_str());
	 mvwaddstr(_data, 3, 4, _network.getInfo("packets").c_str());
	 mvwaddstr(_data, 4, 4, _network.getInfo("received").c_str());
}

void Ncurses::CPU(){
	mvwaddstr(_data, 2, 4, _cpu.getInfo("name").c_str());
	mvwaddstr(_data, 3, 4, _cpu.getInfo("cores").c_str());
	mvwaddstr(_data, 4, 4, _cpu.getInfo("load").c_str());
	mvwaddstr(_data, 5, 4, _cpu.getInfo("cache").c_str());
	mvwaddstr(_data, 6, 4, _cpu.getInfo("freq").c_str());
	wattron(_data, COLOR_PAIR(6));
	int l = static_cast<int>(_cpu.GetCPULoad() * 100.0f);
	mvwprintw(_data, 8, 3, "[");
	l = (l * 50) / 100;
	for (int i = 0; i < l && i < 53; i++)
		mvwprintw(_data, 8, 4 + i, "#");
	mvwprintw(_data, 8, 60, "]");
	wattrset(_data, A_NORMAL);

}

void Ncurses::OS()
{
	mvwaddstr(_data, 2, 4, _kernel.getInfo("OS").c_str());
	mvwaddstr(_data, 3, 4, _kernel.getInfo("type").c_str());
	mvwaddstr(_data, 4, 4, _kernel.getInfo("bit").c_str());
}

void Ncurses::initplugin(){
	this->f[0] = &Ncurses::UserInfo;
	this->f[1] = &Ncurses::Memory;
	this->f[2] = &Ncurses::OS;
	this->f[3] = &Ncurses::CPU;
	this->f[4] = &Ncurses::Network;
}

void Ncurses::reload()
{
	_cpu.updateData();
	_ram.updateData();
	_network.updateData();
	_date.updateData();
}

void Ncurses::allplugins()
{
	int ch = 1;
	initplugin();
	while (ch != 27)
	{
		werase(_data);
		werase(_menu);
		(this->*f[numb])();
		ch = getch();
		if (ch == 258) {
			setNumb(numb + 1);
		}
		if (ch == 259) {
			setNumb(numb - 1);
		}
		if (ch == KEY_RESIZE) {
			printmenu();
			wrefresh(_data);
			wrefresh(_menu);
			refresh();
		}
		printmenu();
		wrefresh(_data);
		wrefresh(_menu);
		refresh();
		usleep(CLOCKS_PER_SEC / 10);
		if (clock() % 3000000000000000000)
		   reload();
	}
}

int Ncurses::getNumb() const {
	return numb;
}

void Ncurses::setNumb(int numb) {
	if (numb < 0)
		Ncurses::numb = 4;
	else if (numb > 4)
		Ncurses::numb = 0;
	else
		Ncurses::numb = numb;
}


void Ncurses::initStrMenu() {
	men[0] = const_cast<char *>("	USER INFO");
	men[1] = const_cast<char *>("	RAM INFO");
	men[2] = const_cast<char *>("	OS INFO");
	men[3] = const_cast<char *>("	CPU INFO");
	men[4] = const_cast<char *>("	NETWORK INFO");
}


void Ncurses::printLeft() {
	int x = 1;
	int y = 1;
	mvwprintw(_menu, y, x, "__________________________");
	y += 4;
	for (int i = 0; i < 5; i++) {
		mvwprintw(_menu, y - 2, x, "%s", men[i]);
		mvwprintw(_menu, y, x, "__________________________");
		y += 4;
	}
	wattron(_menu, COLOR_PAIR(4));
	y = numb * 4 + 1;
	mvwprintw(_menu, y+1, x, "                          ");
	mvwprintw(_menu, y+2, x, "                          ");
	mvwprintw(_menu, y+3, x, "                          ");
	mvwprintw(_menu, y+4, x, "__________________________");
	mvwprintw(_menu, y + 2, x, "%s", men[numb]);
	wattrset(_menu, A_NORMAL);
}

void Ncurses::printmenu()
{
	wattron(_menu, COLOR_PAIR(1) | A_BOLD);
	wattron(_data, COLOR_PAIR(1) | A_BOLD);
	for (int y = 0; y < 23; y++)
	{
		mvwaddch(_menu, y, 0, ' ');
		mvwaddch(_menu, y, 27, ' ');
		mvwaddch(_data, y, 99, ' ');
	}
	for (int x = 0; x < 28; x++)
	{
		mvwaddch(_menu, 0, x, ' ' | A_BOLD);
		mvwaddch(_menu, 22, x, ' '| A_BOLD);
	}
	for (int x = 0; x < 100; x++)
	{
		mvwaddch(_data, 0, x, ' ' | A_BOLD);
		mvwaddch(_data, 22, x, ' '| A_BOLD);
	}
	wattrset(_menu, A_NORMAL);
	wattrset(_data, A_NORMAL);
	printLeft();
	wrefresh(_menu);
	wrefresh(_data);
	refresh();
}

Ncurses::Ncurses()
{
	numb = 0;
	initscr();
	initStrMenu();
	_menu = newwin(23, 28, 0, 0);
	_data = newwin(23, 100, 0, 28);
	init_visualisation();
	printmenu();
}

Ncurses::Ncurses(Ncurses const & copy)
{
	*this = copy;
}

Ncurses const &Ncurses::operator=(Ncurses const & copy) {
	if (this != &copy)
	{
		_cpu = copy.getCPU();
		_kernel = copy.getKernel();
		_ram = copy.getRAM();
		_date = copy.getDate();
		_info = copy.getInfo();
		_network = copy.getNetwork();
		_menu = copy.getMenu();
		numb = copy.getNumb();
	}

	return *this;
}

InfoModule const &   Ncurses::getInfo() const
{
	return (_info);
}

KernelModule const &   Ncurses::getKernel() const
{
	return (_kernel);
}

WINDOW*   Ncurses::getMenu() const
{
	return (_menu);
}

CPUModule const &   Ncurses::getCPU() const
{
	return (_cpu);
}

NetworkModule const &   Ncurses::getNetwork() const
{
	return (_network);
}

DateModule const &   Ncurses::getDate() const
{
	return (_date);
}

RAMModule const &   Ncurses::getRAM() const
{
	return (_ram);
}
