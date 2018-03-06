/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KernelModule.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:21:38 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 16:21:39 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KernelModule.hpp"

KernelModule::KernelModule() : _moduleName("Kernel"), _moduleData()
{
	_moduleData.resize(3);
	updateData();
}

KernelModule::~KernelModule() { }

KernelModule::KernelModule(KernelModule const & copy)
{
	_moduleData.resize(3);
	*this = copy;
}

KernelModule&	KernelModule::operator=(KernelModule const & copy)
{
	if (this != &copy)
	{
		_moduleData[0] = copy.getInfo("OS");
		_moduleData[1] = copy.getInfo("type");
		_moduleData[2] = copy.getInfo("bit");
	}

	return (*this);
}

std::string	KernelModule::getInfo(std::string data) const
{
	if (data == "OS")
		return (_moduleData[0]);
	else if (data == "type")
		return (_moduleData[1]);
	else if (data == "bit")
		return (_moduleData[2]);
	return ("no");
}

void	KernelModule::updateData()
{
	char 				buffer[256];
	std::stringstream	ss;
	FILE				*in;
    size_t				bufferlen;

	in = popen("sw_vers | awk -F':t' '{print $1}' | cut -d$'\t' -f2 | paste -d ' ' - - - | tr -d '\n'", "r");
	ss << "OS Version: "; 
	while (fgets(buffer, sizeof(buffer), in) != NULL)
		ss << buffer;
	_moduleData[0] = ss.str();
	ss.str(std::string());
	bufferlen = 256;
	sysctlbyname("kern.ostype", &buffer, &bufferlen, NULL, 0);
	ss << "OS Type: " << buffer;
	_moduleData[1] = ss.str();
	ss.str(std::string());
	bufferlen = 256;
	sysctlbyname("hw.machine", &buffer, &bufferlen, NULL, 0);
	ss << "Bit System: " << buffer;
	_moduleData[2] = ss.str();
}
