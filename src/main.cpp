#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 
#include <string>   
#include <fstream>
#include <vector>
#include <opencv2/core/core.hpp>       
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/objdetect/objdetect.hpp>

#include "FileDir.h"
#include "QrcodeProcess.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	
	string DirName;
	//�ӿ�1������������ļ����������ʽ"<������ʶ��ͼƬ���ļ���·��>������'C:\Users\dell\Desktop\ffmpeg\qrimage')"
	if (argc == 1)
	{
		cin >> DirName;
		QrcodeProcess process(DirName);
		process.QrcodeProcessJpg();
	}
	//�ӿ�2��ͨ��������ʵ�֣��� �����и�ʽ"...> openCV.exe <������ʶ��ͼƬ���ļ���·��>������'C:\Users\dell\Desktop\ffmpeg\qrimage')"
	else
	{
		string Dirname(argv[1]);
		QrcodeProcess process(Dirname);
		process.QrcodeProcessJpg();
	}
	return 0;
}