// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.



#line 1 "parsers.r"
#include "parsers.h"
#include <iostream>

#line 7 "parsers.cpp"
static const char _fileOutputFormat_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6
};

static const char _fileOutputFormat_key_offsets[] = {
	0, 0, 12, 19, 20, 26, 28, 30, 
	32, 34, 36, 38, 40, 42, 44, 46, 
	48, 50, 52, 54, 56, 58, 58, 70
};

static const char _fileOutputFormat_trans_keys[] = {
	32, 45, 60, 62, 9, 13, 48, 57, 
	65, 90, 97, 122, 60, 62, 68, 69, 
	70, 77, 89, 62, 62, 68, 69, 70, 
	77, 89, 62, 68, 62, 88, 62, 80, 
	62, 95, 62, 78, 62, 85, 62, 77, 
	62, 73, 62, 76, 62, 84, 62, 69, 
	62, 82, 62, 77, 62, 89, 62, 89, 
	62, 89, 32, 45, 60, 62, 9, 13, 
	48, 57, 65, 90, 97, 122, 32, 45, 
	60, 62, 9, 13, 48, 57, 65, 90, 
	97, 122, 0
};

static const char _fileOutputFormat_single_lengths[] = {
	0, 4, 7, 1, 6, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 0, 4, 4
};

static const char _fileOutputFormat_range_lengths[] = {
	0, 4, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 4, 4
};

static const char _fileOutputFormat_index_offsets[] = {
	0, 0, 9, 17, 19, 26, 29, 32, 
	35, 38, 41, 44, 47, 50, 53, 56, 
	59, 62, 65, 68, 71, 74, 75, 84
};

static const char _fileOutputFormat_indicies[] = {
	0, 0, 2, 3, 0, 0, 0, 0, 
	1, 5, 6, 7, 8, 9, 10, 11, 
	4, 6, 4, 6, 7, 8, 9, 10, 
	11, 4, 6, 12, 4, 6, 13, 4, 
	6, 14, 4, 6, 15, 4, 6, 16, 
	4, 6, 17, 4, 6, 18, 4, 6, 
	19, 4, 6, 20, 4, 6, 21, 4, 
	6, 22, 4, 6, 23, 4, 6, 24, 
	4, 6, 25, 4, 6, 26, 4, 6, 
	27, 4, 4, 0, 0, 2, 3, 0, 
	0, 0, 0, 1, 28, 28, 29, 6, 
	28, 28, 28, 28, 4, 0
};

static const char _fileOutputFormat_trans_targs[] = {
	22, 0, 2, 22, 3, 21, 23, 5, 
	6, 12, 17, 18, 3, 7, 8, 9, 
	10, 11, 3, 13, 14, 15, 16, 3, 
	3, 19, 20, 3, 23, 4
};

static const char _fileOutputFormat_trans_actions[] = {
	9, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 7, 0, 0, 0, 
	0, 0, 13, 0, 0, 0, 0, 11, 
	5, 3, 0, 1, 9, 0
};

static const int fileOutputFormat_start = 1;
static const int fileOutputFormat_first_final = 22;
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
	
	
#line 103 "parsers.cpp"
	{
	cs = fileOutputFormat_start;
	}

#line 108 "parsers.cpp"
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
		outputFileName += pcl::String(outputData.EXP_NUM);
	  }
	break;
#line 224 "parsers.cpp"
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

#line 85 "parsers.r"

	
	return outputFileName;
}