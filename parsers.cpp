
#line 1 "parsers.r"
#include "parsers.h"

#line 2 "parsers.cpp"
static const char _fileOutputFormat_actions[] = {
	0, 1, 4, 2, 0, 4, 2, 1, 
	4, 2, 2, 4, 2, 3, 4
};

static const char _fileOutputFormat_key_offsets[] = {
	0, 1, 2, 6, 8, 10, 12, 14, 
	16, 19, 21
};

static const char _fileOutputFormat_trans_keys[] = {
	60, 60, 60, 68, 77, 89, 60, 68, 
	60, 62, 60, 77, 60, 62, 60, 89, 
	60, 62, 89, 60, 89, 60, 62, 0
};

static const char _fileOutputFormat_single_lengths[] = {
	1, 1, 4, 2, 2, 2, 2, 2, 
	3, 2, 2
};

static const char _fileOutputFormat_range_lengths[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0
};

static const char _fileOutputFormat_index_offsets[] = {
	0, 2, 4, 9, 12, 15, 18, 21, 
	24, 28, 31
};

static const char _fileOutputFormat_indicies[] = {
	1, 0, 1, 0, 1, 2, 3, 4, 
	0, 1, 5, 0, 1, 6, 0, 1, 
	7, 0, 1, 8, 0, 1, 9, 0, 
	1, 10, 11, 0, 1, 12, 0, 1, 
	13, 0, 0
};

static const char _fileOutputFormat_trans_targs[] = {
	1, 2, 3, 5, 7, 4, 1, 6, 
	1, 8, 1, 9, 10, 1
};

static const char _fileOutputFormat_trans_actions[] = {
	1, 1, 1, 1, 1, 1, 12, 1, 
	9, 1, 6, 1, 1, 3
};

static const int fileOutputFormat_start = 0;
static const int fileOutputFormat_first_final = 1;
static const int fileOutputFormat_error = -1;

static const int fileOutputFormat_en_main = 0;


#line 5 "parsers.r"


pcl::String GenerateOutputFileName(pcl::String &outputPattern, struct OutputData &outputData)
{
	pcl::String outputFileName;
	outputFileName += "works: ";
	pcl::IsoString isoStr = outputPattern.ToIsoString();
	char *p = isoStr.c_str();
	char *pe = isoStr.c_str() + strlen(isoStr.c_str());
	char *eof = 0;
	
	int cs;
	
#line 57 "parsers.cpp"
	{
	cs = fileOutputFormat_start;
	}

#line 60 "parsers.cpp"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
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
#line 18 "parsers.r"
	{
		outputFileName += "YYYY";
	  }
	break;
	case 1:
#line 22 "parsers.r"
	{
		outputFileName += "YY";
	  }
	break;
	case 2:
#line 26 "parsers.r"
	{
		outputFileName += "MM";
	  }
	break;
	case 3:
#line 30 "parsers.r"
	{
		outputFileName += "DD";
	  }
	break;
	case 4:
#line 34 "parsers.r"
	{
		outputFileName += "X";
	  }
	break;
#line 156 "parsers.cpp"
		}
	}

_again:
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	}

#line 52 "parsers.r"

	
	return outputFileName;
}

int main( int argc, char **argv )
{
	
	return 0;
}