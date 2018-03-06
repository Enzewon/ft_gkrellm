/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DateModule.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 20:22:11 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 20:22:12 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DateModule.hpp"

DateModule::DateModule() : _moduleName("Date"), _moduleData()
{
	_moduleData.resize(2);
	updateData();
}

DateModule::DateModule(DateModule const & copy) : _moduleName("Date")
{
	_moduleData.resize(2);
	*this = copy;
}

DateModule&	DateModule::operator=(DateModule const & copy)
{
	if (this != &copy)
	{
		_moduleData[0] = copy.getInfo("date");
		_moduleData[1] = copy.getInfo("time");
	}

	return (*this);
}

DateModule::~DateModule() { }

std::string	DateModule::getInfo(std::string data) const
{
	if (data == "date")
		return (_moduleData[0]);
	else if (data == "time")
		return (_moduleData[1]);
	return ("no");
}

void	DateModule::updateData()
{
	std::stringstream	ss;
	time_t t = time(0);
	struct tm * now = localtime(&t);

    ss << "Date: " << std::to_string(now->tm_mday) + "/" +
           std::to_string(now->tm_mon + 1) + "/" +
		   std::to_string(now->tm_year + 1900);
	_moduleData[0] = ss.str();
	ss.str(std::string());
	ss << "Time: " << std::to_string(now->tm_hour) + ":";
	if (now->tm_min <= 9)
		ss << "0" << std::to_string(now->tm_min) + ":";
	else
		ss << std::to_string(now->tm_min) + ":";
	if (now->tm_sec <= 9)
		ss << "0" << std::to_string(now->tm_sec);
	else
		ss << std::to_string(now->tm_sec);
	_moduleData[1] = ss.str();
}
