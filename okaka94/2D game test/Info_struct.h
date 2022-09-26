#pragma once
#include "std.h"

struct Song_info {
	std::wstring	FullPath;
	int				BPM = 0;
	int				TimeSignature = 0;
	float			Offset = 0.0f;
};

struct Note_info {
	int				Beat_index = 0;
	std::wstring	Note_type;
	int				x = 0;
	int				y = 0;
};