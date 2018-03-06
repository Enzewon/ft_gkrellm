/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMonitorDisplay.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 14:57:11 by dvdovenk          #+#    #+#             */
/*   Updated: 2017/11/12 14:57:12 by dvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMONITORDISPLAY_HPP
# define IMONITORDISPLAY_HPP

# include "CPUModule.hpp"
# include "KernelModule.hpp"
# include "InfoModule.hpp"
# include "NetworkModule.hpp"
# include "RAMModule.hpp"
# include "DateModule.hpp"

class	IMonitorDisplay
{

public:

	virtual	CPUModule const &		getCPU() const = 0;
	virtual DateModule const &		getDate() const = 0;
	virtual	KernelModule const &	getKernel() const = 0;
	virtual	InfoModule const &		getInfo() const = 0;
	virtual	RAMModule const &		getRAM() const = 0;
	virtual	NetworkModule const &	getNetwork() const = 0;

};

#endif
