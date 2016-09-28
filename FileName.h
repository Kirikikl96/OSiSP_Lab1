#pragma once
class FileName
{
public:
	FileName();
	void SetFileName(char*);
	char* GetCurrentFileName();
	LPCSTR GetSaveQuestionString();
	char* CreateTempFileName(char* filename);
	void SetWindowCaption(HWND);
	void ResetFileName();
	~FileName();
private:
	char* currentFileName;
	char* currentWindowCaption;
	const char* baseFileName = "����������";
	const char* programName = "OSiSP_Lab1";
};

