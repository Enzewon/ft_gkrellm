/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RAMModule.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:54:09 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 17:54:10 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAMMODULE_HPP
# define RAMMODULE_HPP

# include "IMonitorModule.hpp"

class	RAMModule : public IMonitorModule
{

private:

	std::string					_moduleName;
	std::vector<std::string>	_moduleData;

public:

	RAMModule();
	RAMModule(RAMModule const & copy);
	~RAMModule();
	RAMModule&	operator=(RAMModule const & copy);

	std::string	getInfo(std::string) const;
	void		updateData();

	float	GetSystemMemoryUsagePercentage() const;

};

#endif
