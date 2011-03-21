#include "parsers.h"
%%{
  machine fileOutputFormat;
  write data;  
}%%

pcl::String GenerateOutputFileName(pcl::String &outputPattern, struct OutputData &outputData)
{
	pcl::String outputFileName;
	outputFileName += "works: ";
	pcl::IsoString isoStr = outputPattern.ToIsoString();
	char *p = isoStr.c_str();
	char *pe = isoStr.c_str() + strlen(isoStr.c_str());
	char *eof = 0;
	
	int cs;
	%%{
	  action YEAR {
		outputFileName += "YYYY";
	  }
	  
	  action S_YEAR {
		outputFileName += "YY";
	  }
	  
	  action MONTH {
		outputFileName += "MM";
	  }
	  
	  action DAY {
		outputFileName += "DD";
	  }
	  
	  action OTHER {
		outputFileName += "X";
	  }
	  action FILTER {
		outputFileName += "Filter";
	  }
	  YYYY = '<YYYY>';
	  YY = '<YY>';
	  MM = '<MM>';
      DD = '<DD>';
	  FILTER = '<FILTER>';
	  
	  
	  main :=
	  (  YYYY @YEAR | 
		 YY @S_YEAR | 
		 MM @MONTH  | 
		 DD @DAY | 
		 FILTER @FILTER |
		 any @OTHER
	  )+;
	  write init;
	  write exec;
	}%%
	
	return outputFileName;
}

int main( int argc, char **argv )
{
	
	return 0;
}