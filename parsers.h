#ifndef __PARSERS_H
#define __PARSERS_H

#include <pcl/String.h>

struct OutputData
{
	pcl::String YYYY;
	pcl::String MM;
	pcl::String DD;
	pcl::String TARGET;
	pcl::String SEQUENCE_ID;
	pcl::String EXP_NUM;
};

extern pcl::String GenerateOutputFileName(pcl::String &outputPattern, OutputData &outputData);

#endif
