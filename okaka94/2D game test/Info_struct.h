#pragma once
//#include "Std.h"

struct Song_info {
	std::wstring	FullPath;
	float				BPM = 0.0f;
	int				TimeSignature = 0;
	float			Offset = 0.0f;
};

struct Note_info {
	int				Beat_index = 0;
	std::wstring	Note_type;
	int				x = 0;
	int				y = 0;
};