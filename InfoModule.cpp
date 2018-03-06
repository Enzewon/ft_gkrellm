/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InfoModule.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 20:05:23 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 20:05:24 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InfoModule.hpp"

InfoModule::InfoModule() : _moduleName("Network"), _moduleData()
{
	_moduleData.resize(3);
	updateData();
}

InfoModule::~InfoModule() { }

InfoModule::InfoModule(InfoModule const & copy)
{
	_moduleData.resize(3);
	*this = copy;
}

InfoModule&	InfoModule::operator=(InfoModule const & copy)
{
	if (this != &copy)
	{
		_moduleData[0] = copy.getInfo("host");
		_moduleData[1] = copy.getInfo("user");
		_moduleData[1] = copy.getInfo("group");
	}

	return (*this);
}

std::string	InfoModule::getInfo(std::string data) const
{
	if (data == "host")
		return (_moduleData[0]);
	else if (data == "user")
		return (_moduleData[1]);
	else if (data == "group")
		return (_moduleData[2]);
	return ("no");
}

void	InfoModule::updateData()
{
	char 				buffer[256];
	std::stringstream	ss;
	FILE				*in;
    size_t				bufferlen;

	bufferlen = 256;
	sysctlbyname("kern.hostname", &buffer, &bufferlen, NULL, 0);
	ss << "Hostname: " << buffer;
	_moduleData[0] = ss.str();
	ss.str(std::string());
	in = popen("id | cut -d' ' -f1 | cut -d'(' -f2 | cut -d ')' -f1 | tr -d '\n'", "r");
	ss << "User: "; 
	while (fgets(buffer, sizeof(buffer), in) != NULL)
		ss << buffer;
	_moduleData[1] = ss.str();
	ss.str(std::string());
	in = popen("id | cut -d' ' -f2 | cut -d'(' -f2 | cut -d ')' -f1 | tr -d '\n'", "r");
	ss << "Group: "; 
	while (fgets(buffer, sizeof(buffer), in) != NULL)
		ss << buffer;
	_moduleData[2] = ss.str();
	ss.str(std::string());
}
