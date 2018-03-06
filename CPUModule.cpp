/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPUModule.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:18:06 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 15:18:07 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CPUModule.hpp"

CPUModule::CPUModule() : _moduleName("CPU"), _moduleData()
{
	char 				buffer[256];
	std::stringstream	ss;
	size_t				cache_size = 0;
	size_t				size = 0;
    size_t				bufferlen = 256;

	_previousIdleTicks = 0;
	_previousTotalTicks = 0;
	_moduleData.resize(5);
	bufferlen = 256;
	sysctlbyname("machdep.cpu.brand_string", &buffer, &bufferlen, NULL, 0); // Какой процессор
	ss << "Processor: " << buffer;
	_moduleData[0] = ss.str();
	ss.str(std::string());
	bufferlen = 256;
	sysctlbyname("hw.l3cachesize", &cache_size, &bufferlen, NULL, 0); // Размер Хеша
	ss << "Cache size: " << (cache_size >> 10)  << " KB";
	_moduleData[3] = ss.str();
	ss.str(std::string());
	bufferlen = 256;
	sysctlbyname("machdep.cpu.core_count", &size, &bufferlen, NULL, 0); // Количество ЯДЕР
	ss << "Number of cores: " << size;
	_moduleData[2] = ss.str();
	updateData();
}

CPUModule::CPUModule(CPUModule const & copy)
{
	_moduleData.resize(5);
	*this = copy;
}

CPUModule&	CPUModule::operator=(CPUModule const & copy)
{
	if (this != &copy)
	{
		_moduleData[0] = copy.getInfo("name");
		_moduleData[1] = copy.getInfo("load");
		_moduleData[2] = copy.getInfo("cores");
		_moduleData[3] = copy.getInfo("cache");
		_moduleData[4] = copy.getInfo("freq");
	}

	return (*this);
}

CPUModule::~CPUModule() { }

std::string	CPUModule::getInfo(std::string data) const
{
	if (data == "name")
		return (_moduleData[0]);
	else if (data == "load")
		return (_moduleData[1]);
	else if (data == "cores")
		return (_moduleData[2]);
	else if (data == "cache")
		return (_moduleData[3]);
	else if (data == "freq")
		return (_moduleData[4]);
	return ("no");
}

void	CPUModule::updateData()
{
	std::stringstream	ss;

	ss << "CPU overload: " << GetCPULoad() * 100.0f; // Загруженность CPU
	_moduleData[1] = ss.str();
	ss.str(std::string());
	ss << "CPU frequency: " << GetCPUFreq() << " MHz"; // Загруженность CPU
	_moduleData[4] = ss.str();
}

float	CPUModule::CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
  unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
  unsigned long long idleTicksSinceLastTime  = idleTicks - _previousIdleTicks;
  float ret = 1.0f-((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime)/totalTicksSinceLastTime : 0);
  _previousTotalTicks = totalTicks;
  _previousIdleTicks  = idleTicks;
  return (ret);
}

uint64_t	CPUModule::GetCPUFreq()
{
    uint64_t freq = 0;
    size_t size = sizeof(freq);

    if (sysctlbyname("hw.cpufrequency", &freq, &size, NULL, 0) < 0)
        perror("sysctl");
    return (freq / 1000000);
}

float CPUModule::GetCPULoad()
{
	host_cpu_load_info_data_t cpuinfo;
	mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
	if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpuinfo, &count) == KERN_SUCCESS)
	{
		unsigned long long totalTicks = 0;
		for(int i = 0; i < CPU_STATE_MAX; i++) totalTicks += cpuinfo.cpu_ticks[i];
		return (CalculateCPULoad(cpuinfo.cpu_ticks[CPU_STATE_IDLE], totalTicks));
	}
	else
		return (-1.0f);
}
