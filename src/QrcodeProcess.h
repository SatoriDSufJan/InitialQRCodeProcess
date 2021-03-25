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

//��ά�봦���࣬���а����˶�ά�붨λ����ά�����ȷ�����
class QrcodeProcess
{
public:
	
	//Ĭ�Ϲ��캯����
	QrcodeProcess();
	//Mat�ࣻ
	QrcodeProcess(Mat& img);
	//�������ṩ����QrcodeͼƬ��.jpg)���ļ���·����
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
		

		//����ļ���pngʱѡ����
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
						/*to_string(i) + */  //���ɶ��bin�ļ�ʱ��ԭ��
						".bin");

				ofstream Outtext(FileName, ios::app);
				if (Outtext.is_open())
				{
					Outtext << OutputString << "\n";
					Outtext.close();
				}

			}
			else cout << "�Ҳ�����ά�룡~" << endl << "δ��ʶ���" << i << "����Ƭ��" << endl;
		}
}
void QrcodeProcess::QrcodeProcessJpg()
{

	QRCodeDetector detector;
	vector<string> AllImages;


	//����ļ���pngʱѡ����
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
					/*to_string(i) + */  //���ɶ��bin�ļ�ʱ��ԭ��
					".txt");

			ofstream Outtext(FileName, ios::app);
			if (Outtext.is_open())
			{
				Outtext << OutputString << "\n";
				Outtext.close();
			}

		}
		else cout << "�Ҳ�����ά�룡~" << endl << "δ��ʶ���" << i << "����Ƭ��" << endl;

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
					/*to_string(i) + */  //���ɶ��bin�ļ�ʱ��ԭ��
					".bin");

			ofstream Outtext(FileName, ios::app);
			if (Outtext.is_open())
			{
				Outtext << OutputString << "\n";
				Outtext.close();
			}

		}

		else cout << "�Ҳ�����ά�룡~" << endl << "δ��ʶ���" << i << "����Ƭ��" << endl;

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
					/*to_string(i) + */  //���ɶ��bin�ļ�ʱ��ԭ��
					".bin");

			ofstream Outtext(FileName, ios::app);
			if (Outtext.is_open())
			{
				Outtext << OutputString << "\n";
				Outtext.close();
			}

		}

		else cout << "�Ҳ�����ά�룡~" << endl << "δ��ʶ���" << i << "����Ƭ��" << endl;

	}
}

