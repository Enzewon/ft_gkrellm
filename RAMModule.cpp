/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RAMModule.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:54:05 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 17:54:06 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RAMModule.hpp"

RAMModule::RAMModule() : _moduleName("RAM"), _moduleData()
{
	char 				buffer[256];
	std::stringstream	ss;
	FILE				*in;

	_moduleData.resize(3);
	in = popen("sysctl -n hw.memsize | awk '{print $0/1073741824}' | tr -d '\n'", "r");
	while (fgets(buffer, sizeof(buffer), in) != NULL)
		ss << "Total RAM Amount: " << buffer << " GB";
	_moduleData[0] = ss.str();
	updateData();
}

RAMModule::RAMModule(RAMModule const & copy) : _moduleName("RAM")
{
	_moduleData.resize(3);
	*this = copy;
}

RAMModule&	RAMModule::operator=(RAMModule const & copy)
{
	if (this != &copy)
	{
		_moduleData[0] = copy.getInfo("total");
		_moduleData[1] = copy.getInfo("now");
	}

	return (*this);
}

RAMModule::~RAMModule() { }

std::string	RAMModule::getInfo(std::string data) const
{
	if (data == "total")
		return (_moduleData[0]);
	else if (data == "now")
		return (_moduleData[1]);
	else if (data == "usage")
		return (_moduleData[2]);
	return ("no");
}

static double ParseMemValue(const char * b)
{
   while((*b)&&(isdigit(*b) == false)) b++;
   return isdigit(*b) ? atof(b) : -1.0;
}

// Returns a number between 0.0f and 1.0f, with 0.0f meaning all RAM is available, and 1.0f meaning all RAM is currently in use
float	RAMModule::GetSystemMemoryUsagePercentage() const
{
   FILE * fpIn = popen("/usr/bin/vm_stat", "r");
   if (fpIn)
   {
      double pagesUsed = 0.0, totalPages = 0.0;
      char buf[512];
      while(fgets(buf, sizeof(buf), fpIn) != NULL)
      {
         if (strncmp(buf, "Pages", 5) == 0)
         {
            double val = ParseMemValue(buf);
            if (val >= 0.0)
            {
               if ((strncmp(buf, "Pages wired", 11) == 0) || (strncmp(buf, "Pages active", 12) == 0)) pagesUsed += val;
               totalPages += val;
            }
         }
         else if (strncmp(buf, "Mach Virtual Memory Statistics", 30) != 0) break;  // Stop at "Translation Faults", we don't care about anything at or below that
      }
      pclose(fpIn);

      if (totalPages > 0.0) return (float) (pagesUsed/totalPages);
   }
   return -1.0f;  // indicate failure
}

void	RAMModule::updateData()
{
	vm_size_t page_size;
	mach_port_t mach_port;
	mach_msg_type_number_t count;
	vm_statistics64_data_t vm_stats;
	std::stringstream	ss;
	
	mach_port = mach_host_self();
	count = sizeof(vm_stats) / sizeof(natural_t);
	if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
		KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
										(host_info64_t)&vm_stats, &count))
	{
		long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;

		long long used_memory = ((int64_t)vm_stats.active_count +
								 (int64_t)vm_stats.inactive_count +
								 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
		ss << "Memory: " << (used_memory / 1000000) << "/" << (free_memory / 1000000) << " MB";
		_moduleData[1] = ss.str();
	}
	ss.str(std::string());
	ss << GetSystemMemoryUsagePercentage();
	_moduleData[2] = ss.str();
}