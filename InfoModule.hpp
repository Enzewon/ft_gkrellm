/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InfoModule.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 20:05:26 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 20:05:26 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFOMODULE_HPP
# define INFOMODULE_HPP

# include "IMonitorModule.hpp"

class	InfoModule : public IMonitorModule
{

private:

	std::string					_moduleName;
	std::vector<std::string>	_moduleData;

public:

	InfoModule();
	InfoModule(InfoModule const & copy);
	~InfoModule();

	InfoModule&	operator=(InfoModule const & copy);
	std::string	getInfo(std::string) const;
	void		updateData();

};

#endif


