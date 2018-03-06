/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkModule.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 18:56:50 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 18:56:51 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NETWORKMODULE_HPP
# define NETWORKMODULE_HPP

# include "IMonitorModule.hpp"

class	NetworkModule : public IMonitorModule
{

private:

	std::string					_moduleName;
	std::vector<std::string>	_moduleData;

public:

	NetworkModule();
	NetworkModule(NetworkModule const & copy);
	~NetworkModule();
	NetworkModule&	operator=(NetworkModule const & copy);

	std::string	getInfo(std::string) const;
	void		updateData();

};

#endif

