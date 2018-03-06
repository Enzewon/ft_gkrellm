/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMonitorModule.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 14:57:06 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 14:57:07 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMONITORMODULE_HPP
# define IMONITORMODULE_HPP

# include <iostream>
# include <vector>
# include <sstream>
# include <sys/types.h>
# include <sys/sysctl.h>
# include <stdio.h>

# include <mach/mach.h>
# include <mach/mach_init.h>
# include <mach/mach_error.h>
# include <mach/mach_host.h>
# include <mach/vm_map.h>
# include <mach/vm_statistics.h>
# include <mach/mach_types.h>
# include <net/if.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/socket.h>
# include "net/if.h"
# include <sys/sysctl.h>
# include <ifaddrs.h>
# include <net/if_dl.h>
# include <math.h>

# include <sys/ioctl.h>
# include <unistd.h>

# define RTM_IFINFO2	0x12


class	IMonitorModule
{

public:

	virtual std::string	getInfo(std::string) const = 0;
	virtual void		updateData() = 0;

};

#endif
