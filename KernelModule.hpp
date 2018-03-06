/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KernelModule.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 16:21:42 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 16:21:44 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNELMODULE_HPP
# define KERNELMODULE_HPP

# include "IMonitorModule.hpp"

class	KernelModule : public IMonitorModule
{

private:

	std::string					_moduleName;
	std::vector<std::string>	_moduleData;

public:

	KernelModule();
	KernelModule(KernelModule const & copy);
	~KernelModule();

	KernelModule&	operator=(KernelModule const & copy);

	std::string	getInfo(std::string) const;
	void		updateData();

};

#endif

