/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkModule.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 18:56:47 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 18:56:49 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NetworkModule.hpp"

NetworkModule::NetworkModule() : _moduleName("Network"), _moduleData()
{
	_moduleData.resize(3);
	updateData();
}

NetworkModule::NetworkModule(NetworkModule const & copy) : _moduleName("Network")
{
	_moduleData.resize(3);
	*this = copy;
}

NetworkModule&	NetworkModule::operator=(NetworkModule const & copy)
{
	if (this != &copy)
	{
		_moduleData[0] = copy.getInfo("IP");
		_moduleData[1] = copy.getInfo("packets");
		_moduleData[2] = copy.getInfo("received");
	}

	return (*this);
}

NetworkModule::~NetworkModule() { }

std::string	NetworkModule::getInfo(std::string data) const
{
	if (data == "IP")
		return (_moduleData[0]);
	else if (data == "packets")
		return (_moduleData[1]);
	else if (data == "received")
		return (_moduleData[2]);
	return ("no");
}

void	NetworkModule::updateData()
{
	char				buffer[256];
	std::stringstream	ss;
	FILE*				in;
	size_t				bufferlen = 256;
	int         mib[6];
    char         *lim;
    char         *next;
    size_t         len;
    struct         if_msghdr *ifm;
    long int     ipackets = 0;
    long int     opackets = 0;
    long int     ibytes = 0;
    long int     obytes = 0;

	bufferlen = 256;
	in = popen("ifconfig | awk '/inet / {print $2}' | tr -d '\n' | cut -c10- | tr -d '\n'", "r");
	ss << "Local IP: "; 
	while (fgets(buffer, sizeof(buffer), in) != NULL)
		ss << buffer;
	_moduleData[0] = ss.str();
	ss.str(std::string());

    mib[0]= CTL_NET;// networking subsystem
    mib[1]= PF_ROUTE;// type of information
    mib[2]= 0;// protocol (IPPROTO_xxx)
    mib[3]= 0;// address family
    mib[4]= NET_RT_IFLIST2;// operation
    mib[5]= 0;

    sysctl(mib, 6, NULL, &len, NULL, 0);
    char buf[len];
    sysctl(mib, 6, buf, &len, NULL, 0);

    lim = buf + len;
    for (next = buf; next < lim; ) {
        ifm = (struct if_msghdr *)next;
        next += ifm->ifm_msglen;

        if (ifm->ifm_type == RTM_IFINFO2) {
            struct if_msghdr2 *if2m = (struct if_msghdr2 *)ifm;

            if(if2m->ifm_data.ifi_type!=18) {
                opackets += if2m->ifm_data.ifi_opackets;
                ipackets += if2m->ifm_data.ifi_ipackets;
                obytes   += if2m->ifm_data.ifi_obytes;
                ibytes   += if2m->ifm_data.ifi_ibytes;
            }
        }
    }
    ss << "Packets in: " << ipackets;
    ss << " / Packets out: " << opackets;
    _moduleData[1] = ss.str();
    
    ss.str(std::string());
    ss.precision(2);
    ss.setf(std::ios::fixed);
    ss << "Data received: " << static_cast<double>(ibytes) / 1024 / 1024 / 1024;
    ss << " GB / data sent: " << static_cast<double>(obytes) / 1024 / 1024 / 1024;
    ss << " GB";
    _moduleData[2] = ss.str();
}

