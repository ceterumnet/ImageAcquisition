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
