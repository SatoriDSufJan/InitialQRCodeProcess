#pragma once
#include <iostream> 
#include <string>   
#include <fstream>
#include <vector>
#include <opencv2/core/core.hpp>       
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/objdetect/objdetect.hpp>

#include "FileDir.h"

using namespace std;
using namespace cv;

//二维码处理类，其中包含了二维码定位，二维码解码等方法；
class QrcodeProcess
{
public:
	
	//默认构造函数；
	QrcodeProcess();
	//Mat类；
	QrcodeProcess(Mat& img);
	//命令行提供包含Qrcode图片（.jpg)的文件夹路径；
	QrcodeProcess(string& DirName);

	void GetMat(Mat& img);

	void GetDir(string& Dirname);

	void QrcodeProcessJpg(string& DirName);

	void QrcodeProcessJpg();

	void QrcodeProcessPng(string& Dirname);

	void QrcodeProcessPng();

private:
	string DirName;
	Mat preimg;
};
QrcodeProcess::QrcodeProcess(){}
QrcodeProcess::QrcodeProcess(Mat& img)
{
	preimg = img;
}
 QrcodeProcess::QrcodeProcess(string& Dirname)
{
	 DirName = Dirname;
 }
 void QrcodeProcess::GetMat(Mat& img)
 {
	 preimg = img;
 }
 void QrcodeProcess::GetDir(string& Dirname)
 {
	 DirName = Dirname;
 }
void QrcodeProcess:: QrcodeProcessJpg(string& Dirname)
{
	
		QRCodeDetector detector;
		string DirName(Dirname);
		vector<string> AllImages;
		

		//如果文件是png时选择此项；
		/*
		getAllFiles(DirName,  AllImages);
		for (int i = 0; i < countFile(DirName, "*.png"){
		//...
		};
		*/
		myGetAllFiles(DirName, AllImages);
		for (int i = 0; i < AllImages.size(); ++i)
		{
			string OutputString, tempFileName(".\\Output");

			Mat InputImg = imread(AllImages[i]);

			//imshow("test",InputImg);
			//waitKey(); 

			Mat OutputImg;
			Mat Points;

			if (detector.detect(InputImg, Points))
			{
				OutputString = detector.decode(InputImg, Points, OutputImg);

				//imshow("test", OutputImg);
				//waitKey();

				string FileName =
					tempFileName.append(
						/*to_string(i) + */  //生成多个bin文件时还原；
						".bin");

				ofstream Outtext(FileName, ios::app);
				if (Outtext.is_open())
				{
					Outtext << OutputString << "\n";
					Outtext.close();
				}

			}
			else cout << "找不到二维码！~" << endl << "未能识别第" << i << "张照片；" << endl;
		}
}
void QrcodeProcess::QrcodeProcessJpg()
{

	QRCodeDetector detector;
	vector<string> AllImages;


	//如果文件是png时选择此项；
	/*
	getAllFiles(DirName,  AllImages);
	for (int i = 0; i < countFile(DirName, "*.png"){
	//...
	};
	*/
	myGetAllFiles(this->DirName, AllImages);
	for (int i = 0; i < AllImages.size(); ++i)
	{
		string OutputString, tempFileName(".\\Output");

		Mat InputImg = imread(AllImages[i]);

		//imshow("test",InputImg);
		//waitKey(); 

		Mat OutputImg;
		Mat Points;

		if (detector.detect(InputImg, Points))
		{
			OutputString = detector.decode(InputImg, Points, OutputImg);

			//imshow("test", OutputImg);
			//waitKey();

			string FileName =
				tempFileName.append(
					/*to_string(i) + */  //生成多个bin文件时还原；
					".txt");

			ofstream Outtext(FileName, ios::app);
			if (Outtext.is_open())
			{
				Outtext << OutputString << "\n";
				Outtext.close();
			}

		}
		else cout << "找不到二维码！~" << endl << "未能识别第" << i << "张照片；" << endl;

	}
}
void QrcodeProcess::QrcodeProcessPng(string& Dirname)
{
	QRCodeDetector detector;
	string DirName(Dirname);
	vector<string> AllImages;


	myGetAllFiles(DirName,  AllImages);
	for (int i = 0; i < countFile(DirName, "*.png"); ++i)
	{
		string OutputString, tempFileName(".\\Output");

		Mat InputImg = imread(AllImages[i]);

		//imshow("test",InputImg);
		//waitKey(); 

		Mat OutputImg;
		Mat Points;

		if (detector.detect(InputImg, Points))
		{
			OutputString = detector.decode(InputImg, Points, OutputImg);

			//imshow("test", OutputImg);
			//waitKey();

			string FileName =
				tempFileName.append(
					/*to_string(i) + */  //生成多个bin文件时还原；
					".bin");

			ofstream Outtext(FileName, ios::app);
			if (Outtext.is_open())
			{
				Outtext << OutputString << "\n";
				Outtext.close();
			}

		}

		else cout << "找不到二维码！~" << endl << "未能识别第" << i << "张照片；" << endl;

	}
};
void QrcodeProcess::QrcodeProcessPng()
{
	QRCodeDetector detector;
	string DirName(this->DirName);
	vector<string> AllImages;


	myGetAllFiles(DirName, AllImages);
	for (int i = 0; i < countFile(DirName, "*.png"); ++i)
	{
		string OutputString, tempFileName(".\\Output");

		Mat InputImg = imread(AllImages[i]);

		//imshow("test",InputImg);
		//waitKey(); 

		Mat OutputImg;
		Mat Points;

		if (detector.detect(InputImg, Points))
		{
			OutputString = detector.decode(InputImg, Points, OutputImg);

			//imshow("test", OutputImg);
			//waitKey();

			string FileName =
				tempFileName.append(
					/*to_string(i) + */  //生成多个bin文件时还原；
					".bin");

			ofstream Outtext(FileName, ios::app);
			if (Outtext.is_open())
			{
				Outtext << OutputString << "\n";
				Outtext.close();
			}

		}

		else cout << "找不到二维码！~" << endl << "未能识别第" << i << "张照片；" << endl;

	}
}

