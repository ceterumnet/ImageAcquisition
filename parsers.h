// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#ifndef __PARSERS_H
#define __PARSERS_H

#include <pcl/String.h>

struct OutputData
{
	pcl::String YYYY;
	pcl::String YY;
	pcl::String MM;
	pcl::String DD;
	pcl::String TARGET;
	pcl::String SEQUENCE_ID;
	pcl::uint8 EXP_NUM;
	pcl::String FILTER;
};

extern pcl::String GenerateOutputFileName(pcl::String &outputPattern, OutputData &outputData);

#endif
