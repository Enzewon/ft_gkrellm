/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DateModule.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 20:22:15 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 20:22:16 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATEMODULE_HPP
# define DATEMODULE_HPP

# include "IMonitorModule.hpp"

class	DateModule : public IMonitorModule
{

private:

	std::string					_moduleName;
	std::vector<std::string>	_moduleData;

public:

	DateModule();
	DateModule(DateModule const & copy);
	~DateModule();
	DateModule&	operator=(DateModule const & copy);

	std::string	getInfo(std::string) const;
	void		updateData();

};

#endif

