/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CPUModule.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 15:18:09 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 15:18:10 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPUMODULE_HPP
# define CPUMODULE_HPP

# include "IMonitorModule.hpp"

class	CPUModule : public IMonitorModule
{

private:

	unsigned long long	_previousTotalTicks;
	unsigned long long	_previousIdleTicks;

	std::string					_moduleName;
	std::vector<std::string>	_moduleData;

public:

	CPUModule();
	CPUModule(CPUModule const & copy);
	~CPUModule();

	CPUModule&	operator=(CPUModule const & copy);

	std::string	getInfo(std::string) const;
	void		updateData();

	float		CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
	uint64_t	GetCPUFreq();
	float		GetCPULoad();

};

#endif
