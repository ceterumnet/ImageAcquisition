#include "parsers.h"
#include <iostream>
%%{
  machine fileOutputFormat;
  write data;  
}%%

pcl::String GenerateOutputFileName(pcl::String &outputPattern, struct OutputData &outputData)
{	

	pcl::String outputFileName;
	pcl::IsoString isoStr = outputPattern.ToIsoString();
	
	char *p  = isoStr.c_str();
	char *pe = isoStr.c_str() + strlen( isoStr.c_str() );
	char *eof = 0;
	
	int cs;
	
	%%{
	  action YYYY {
		outputFileName += outputData.YYYY;
	  }
	  
	  action YY {
		outputFileName += outputData.YY;
	  }
	  
	  action MM {
		outputFileName += outputData.MM;
	  }
	  
	  action DD {
		outputFileName += outputData.DD;
	  }
	  
	  action OTHER {
		outputFileName += fc;
	  }
 
	  action FILTER {
		outputFileName += outputData.FILTER;
	  }
	  
	  action EXP_NUM {
		outputFileName += pcl::String(outputData.EXP_NUM);
	  }
	  
	  START_CMD = '<';
	  
	  YYYY = 'YYYY';
	  YY = 'YY';
	  MM = 'MM';
      DD = 'DD';
	  FILTER = 'FILTER';
	  EXP_NUM = 'EXP_NUM'; 
	  
	  END_CMD = '>';
	  
	  SPECIALS = (
		YYYY @YYYY |
		YY @YY |
		MM @MM |
		DD @DD |
		FILTER @FILTER |
		EXP_NUM @EXP_NUM
	  );
	  
	  CMD = (
		START_CMD 
		  ( SPECIALS | ( any* - ( SPECIALS | '<' | '>' ) )  )
		END_CMD
	  );
	  
	  USER = (
		( alnum @OTHER | space @OTHER | '-' @OTHER | '>' ) 
	  );
	  
	  main := (
		CMD | USER
	  )+;
	  
	  write init;
	  write exec;
	}%%
	
	return outputFileName;
}