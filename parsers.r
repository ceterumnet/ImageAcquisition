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
		outputFileName += outputData.EXP_NUM;
	  }
	  
	  action STAR {
		outputFileName += "*";
	  }
	  
	  action STAR2 {
		outputFileName += "+";
	  }
	  action OTHER2 {
		outputFileName += "^";
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
		START_CMD SPECIALS END_CMD
	  );

	  NON_CMD = (
	    START_CMD 
		( alnum @OTHER | '<' )* - ( alnum* 'YYYY' alnum*)
		END_CMD 
	  );
	  
	  USER = (
		( alnum @OTHER | space @OTHER | '-' @OTHER | '>' ) 
	  );
	  main := (
		CMD | ( NON_CMD - CMD ) | USER
	  )+;
	  
	  write init;
	  write exec;
	}%%
	
	//FOO<YYYY>-<MM>-<DD>-<M106>-<<FOO<<WHAT>>BAR
	//FOO 2010 - 03 - 26 - M106 -  FOO  WHAT  BAR
	//FOO 2010 - 03 - 26 -*^^^^+-*^^^^^^^^^^+
	//FOO 2010   03   26 -*^^^^+-*
	//FOO^2010 -*03 -*26 -*^
	//FOO 2010 - 03 - 26 -
	//FOO*^-^*^-^*^-^*^-^*^+>^B^A^R
	//FOO*^^^2010^^+^^^^^+^^^^^+^^^^^^^+^^^^^^^^^^^^^+^+^^^
	//FOO*^^^2010^^+^^^^^+^^^^^+^^^^^^^+^^^^^^^^^^^^^+^+^^^
	//FOO*^2010-*^03-*^26-*^
	//FOO*^2010-*^03-*^26-*^
	//FOO*Y2010-*M03-*D26-*M
	//FOO2010-03-26-
	//_2010_03_26_____
	return outputFileName;
}