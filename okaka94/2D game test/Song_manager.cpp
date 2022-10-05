#include "Song_manager.h"

bool Song_manager::Load(std::wstring filename) {

	ZeroMemory(&m_song_info, sizeof(Song_info));
	while (!m_noteQ.empty()) {

		//Note_info data = m_noteQ.front();
		//delete data;
		m_noteQ.pop();
	}
	
	TCHAR Buffer[256] = { 0, };
	TCHAR Temp[2][256] = { 0, };
	

	FILE* fp_src;
	_wfopen_s(&fp_src, filename.c_str(), _T("rt"));
	if (fp_src == NULL) return false;

	
	
	while (!feof(fp_src)) {
		_fgetts(Buffer, _countof(Buffer), fp_src);

		if (_tcscmp(Buffer, _T("[Song_info]\n")) == 0) {

			_fgetts(Buffer, _countof(Buffer), fp_src);

			_stscanf_s(Buffer, _T("%s\t%s\n"), Temp[0], (unsigned int)_countof(Temp[0]), Temp[1], _countof(Temp[1]));
			m_song_info.FullPath = Temp[1];

			_fgetts(Buffer, _countof(Buffer), fp_src);
			_stscanf_s(Buffer, _T("%s\t%f\n"), Temp[0], (unsigned int)_countof(Temp[0]), &m_song_info.BPM);

			_fgetts(Buffer, _countof(Buffer), fp_src);
			_stscanf_s(Buffer, _T("%s\t%d\n"), Temp[0], (unsigned int)_countof(Temp[0]), &m_song_info.TimeSignature);

			_fgetts(Buffer, _countof(Buffer), fp_src);
			_stscanf_s(Buffer, _T("%s\t%f\n"), Temp[0], (unsigned int)_countof(Temp[0]), &m_song_info.Offset);
		}

		
		if (_tcscmp(Buffer, _T("[Note_info]\n")) == 0) {
			while (!feof(fp_src)) {
				Note_info data;
				_fgetts(Buffer, _countof(Buffer), fp_src);
				_stscanf_s(Buffer, _T("%d %s %d %d"), &data.Beat_index,  Temp[0], (unsigned int)_countof(Temp[0]),&data.x,&data.y );
				data.Note_type = Temp[0];
				m_noteQ.push(data);
			}

		}


	}
	fclose(fp_src);
	return true;
}

bool Song_manager::Init() {


	return true;
}
