
#line 1 "parsers.r"
#include "parsers.h"
#include <iostream>

#line 2 "parsers.cpp"
static const char _fileOutputFormat_actions[] = {
	0, 1, 4, 1, 6, 2, 0, 4, 
	2, 1, 4, 2, 2, 4, 2, 3, 
	4, 2, 5, 4
};

static const unsigned char _fileOutputFormat_key_offsets[] = {
	0, 0, 12, 13, 14, 15, 16, 28, 
	45, 58, 71, 84, 97, 110, 123, 136, 
	149, 162, 175, 188, 201
};

static const char _fileOutputFormat_trans_keys[] = {
	32, 45, 60, 62, 9, 13, 48, 57, 
	65, 90, 97, 122, 78, 85, 77, 62, 
	32, 45, 60, 62, 9, 13, 48, 57, 
	65, 90, 97, 122, 32, 45, 60, 62, 
	68, 69, 70, 77, 89, 9, 13, 48, 
	57, 65, 90, 97, 122, 32, 45, 60, 
	62, 68, 9, 13, 48, 57, 65, 90, 
	97, 122, 32, 45, 60, 62, 88, 9, 
	13, 48, 57, 65, 90, 97, 122, 32, 
	45, 60, 62, 80, 9, 13, 48, 57, 
	65, 90, 97, 122, 32, 45, 60, 62, 
	95, 9, 13, 48, 57, 65, 90, 97, 
	122, 32, 45, 60, 62, 73, 9, 13, 
	48, 57, 65, 90, 97, 122, 32, 45, 
	60, 62, 76, 9, 13, 48, 57, 65, 
	90, 97, 122, 32, 45, 60, 62, 84, 
	9, 13, 48, 57, 65, 90, 97, 122, 
	32, 45, 60, 62, 69, 9, 13, 48, 
	57, 65, 90, 97, 122, 32, 45, 60, 
	62, 82, 9, 13, 48, 57, 65, 90, 
	97, 122, 32, 45, 60, 62, 77, 9, 
	13, 48, 57, 65, 90, 97, 122, 32, 
	45, 60, 62, 89, 9, 13, 48, 57, 
	65, 90, 97, 122, 32, 45, 60, 62, 
	89, 9, 13, 48, 57, 65, 90, 97, 
	122, 32, 45, 60, 62, 89, 9, 13, 
	48, 57, 65, 90, 97, 122, 0
};

static const char _fileOutputFormat_single_lengths[] = {
	0, 4, 1, 1, 1, 1, 4, 9, 
	5, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5
};

static const char _fileOutputFormat_range_lengths[] = {
	0, 4, 0, 0, 0, 0, 4, 4, 
	4, 4, 4, 4, 4, 4, 4, 4, 
	4, 4, 4, 4, 4
};

static const unsigned char _fileOutputFormat_index_offsets[] = {
	0, 0, 9, 11, 13, 15, 17, 26, 
	40, 50, 60, 70, 80, 90, 100, 110, 
	120, 130, 140, 150, 160
};

static const char _fileOutputFormat_indicies[] = {
	0, 0, 2, 3, 0, 0, 0, 0, 
	1, 4, 1, 5, 1, 6, 1, 3, 
	1, 0, 0, 2, 3, 0, 0, 0, 
	0, 1, 0, 0, 2, 3, 7, 8, 
	9, 10, 11, 0, 0, 0, 0, 1, 
	0, 0, 2, 3, 12, 0, 0, 0, 
	0, 1, 0, 0, 2, 3, 13, 0, 
	0, 0, 0, 1, 0, 0, 2, 3, 
	14, 0, 0, 0, 0, 1, 0, 0, 
	2, 3, 15, 0, 0, 0, 0, 1, 
	0, 0, 2, 3, 16, 0, 0, 0, 
	0, 1, 0, 0, 2, 3, 17, 0, 
	0, 0, 0, 1, 0, 0, 2, 3, 
	18, 0, 0, 0, 0, 1, 0, 0, 
	2, 3, 19, 0, 0, 0, 0, 1, 
	0, 0, 2, 3, 20, 0, 0, 0, 
	0, 1, 0, 0, 2, 3, 21, 0, 
	0, 0, 0, 1, 0, 0, 2, 3, 
	22, 0, 0, 0, 0, 1, 0, 0, 
	2, 3, 23, 0, 0, 0, 0, 1, 
	0, 0, 2, 3, 24, 0, 0, 0, 
	0, 1, 0
};

static const char _fileOutputFormat_trans_targs[] = {
	6, 0, 7, 6, 3, 4, 5, 8, 
	9, 12, 17, 18, 6, 10, 11, 2, 
	13, 14, 15, 16, 6, 6, 19, 20, 
	6
};

static const char _fileOutputFormat_trans_actions[] = {
	1, 0, 0, 0, 0, 0, 3, 1, 
	1, 1, 1, 1, 14, 1, 1, 0, 
	1, 1, 1, 1, 17, 11, 8, 1, 
	5
};

static const int fileOutputFormat_start = 1;
static const int fileOutputFormat_first_final = 6;
static const int fileOutputFormat_error = 0;

static const int fileOutputFormat_en_main = 1;


#line 6 "parsers.r"


pcl::String GenerateOutputFileName(pcl::String &outputPattern, struct OutputData &outputData)
{	

	pcl::String outputFileName;
	pcl::IsoString isoStr = outputPattern.ToIsoString();
	
	char *p  = isoStr.c_str();
	char *pe = isoStr.c_str() + strlen( isoStr.c_str() );
	char *eof = 0;
	
	int cs;
	
	
#line 107 "parsers.cpp"
	{
	cs = fileOutputFormat_start;
	}

#line 110 "parsers.cpp"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _fileOutputFormat_trans_keys + _fileOutputFormat_key_offsets[cs];
	_trans = _fileOutputFormat_index_offsets[cs];

	_klen = _fileOutputFormat_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _fileOutputFormat_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += ((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _fileOutputFormat_indicies[_trans];
	cs = _fileOutputFormat_trans_targs[_trans];

	if ( _fileOutputFormat_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _fileOutputFormat_actions + _fileOutputFormat_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 21 "parsers.r"
	{
		outputFileName += outputData.YYYY;
	  }
	break;
	case 1:
#line 25 "parsers.r"
	{
		outputFileName += outputData.YY;
	  }
	break;
	case 2:
#line 29 "parsers.r"
	{
		outputFileName += outputData.MM;
	  }
	break;
	case 3:
#line 33 "parsers.r"
	{
		outputFileName += outputData.DD;
	  }
	break;
	case 4:
#line 37 "parsers.r"
	{
		outputFileName += (*p);
	  }
	break;
	case 5:
#line 41 "parsers.r"
	{
		outputFileName += outputData.FILTER;
	  }
	break;
	case 6:
#line 45 "parsers.r"
	{
		outputFileName += outputData.EXP_NUM;
	  }
	break;
#line 218 "parsers.cpp"
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 98 "parsers.r"

	
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