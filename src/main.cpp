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
	//接口1（运行中添加文件）：输入格式"<包含待识别图片的文件夹路径>（例如'C:\Users\dell\Desktop\ffmpeg\qrimage')"
	if (argc == 1)
	{
		cin >> DirName;
		QrcodeProcess process(DirName);
		process.QrcodeProcessJpg();
	}
	//接口2（通过命令行实现）： 命令行格式"...> openCV.exe <包含待识别图片的文件夹路径>（例如'C:\Users\dell\Desktop\ffmpeg\qrimage')"
	else
	{
		string Dirname(argv[1]);
		QrcodeProcess process(Dirname);
		process.QrcodeProcessJpg();
	}
	return 0;
}