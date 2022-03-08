// Image_Stitch_With_Matchtemplate.cpp
// 环境VS2017 + OpenCV4.4.0
// 功能：基于模板匹配的图像拼接
// 特点：图像有重合区域，且待拼接图像之间无明显尺度变换和畸变
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<algorithm>
#include <string>
#include <vector>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int MAX_PICTURE__COUNT = 8;

int testImg(const void* imageIn,const UINT sizeIn) {
	if (imageIn == NULL) {
		return -1;
	}
	std::vector<uchar> imageIn_vec((uchar*)imageIn, (uchar*)imageIn + sizeIn);
	Mat src = cv::imdecode(imageIn_vec, CV_LOAD_IMAGE_COLOR);
	if (src.empty()) {
		return -2;
	}
	return 1;
}



int main()
{
	int a[3], b[4] = {1,2,3,4};
	try {
		
	}
	catch (...) {
		return -8;
	}
	

	/*FILE* file_ShortStick = fopen("F:\\Baoxin\\steel2\\IM\\1.JPG", "rb");
	uchar* mem_ShortStick = nullptr;
	long sizeIn_ShortStick = 0;
	if (file_ShortStick != nullptr) {
		fseek(file_ShortStick, 0, SEEK_END);
		sizeIn_ShortStick = ftell(file_ShortStick);
		fseek(file_ShortStick, 0, SEEK_SET);
		mem_ShortStick = new uchar[sizeIn_ShortStick];
		fread(mem_ShortStick, 1, sizeIn_ShortStick, file_ShortStick);
		fclose(file_ShortStick);
	}
	const void* imageIn_ShortStick = mem_ShortStick;
	int res = testImg(imageIn_ShortStick, sizeIn_ShortStick);
	cout << res << endl;*/
	//double location[4];
	//Mat imgL,imgR,tempImg;
	//double start = getTickCount();
	//vector<Mat> imgs;
	//UINT sizeIn_ShortStick[MAX_PICTURE__COUNT] = { 0 };
	//const void* imageIn_ShortStick[MAX_PICTURE__COUNT];
	//uchar* mem_ShortStick = nullptr;
	//for (int i = 0; i < 5; i++) {
	//	char sBuffer[100];
	//	sprintf(sBuffer, "F://Baoxin//steel2//IM//%d.jpg", i + 1);
	//	FILE* file_ShortStick = fopen(sBuffer, "rb");

	//	if (file_ShortStick != nullptr) {
	//		fseek(file_ShortStick, 0, SEEK_END);
	//		sizeIn_ShortStick[i] = ftell(file_ShortStick);
	//		fseek(file_ShortStick, 0, SEEK_SET);
	//		mem_ShortStick = new uchar[sizeIn_ShortStick[i]];
	//		fread(mem_ShortStick, 1, sizeIn_ShortStick[i], file_ShortStick);
	//		fclose(file_ShortStick);
	//	}

	//	imageIn_ShortStick[i] = mem_ShortStick;
	//}
	//uchar** srcFile = (uchar**)imageIn_ShortStick;

	//for (int i = 0; i < 5; i++) {
	//	if (sizeIn_ShortStick[i] == 0) {
	//		cout << "failed!!!" << endl;
	//		return -1;
	//	}
	//	std::vector<uchar> picbb_vec(((uchar*)srcFile[i]), ((uchar*)srcFile[i]) + sizeIn_ShortStick[i]);
	//	Mat src = cv::imdecode(picbb_vec, CV_LOAD_IMAGE_COLOR);
	//	if (src.empty()) {
	//		cout << "no!!!!" << endl;
	//		return -1;
	//	}
	//	imgs.push_back(src);
	//}

	//for (int i = 0; i < 5;i++) {
	//	if (i == 0) {
	//		imgL = imgs.at(0);
	//		i++;
	//	}
	//	else {
	//		imgL = tempImg;
	//	}
	//	cout << i << endl;
	//	imgR = imgs.at(i);

	//	Mat grayL, grayR;
	//	cvtColor(imgL, grayL, COLOR_BGR2GRAY);
	//	cvtColor(imgR, grayR, COLOR_BGR2GRAY);
	//
	//	cout <<"L size :" << imgL.cols << " , " << imgL.rows << endl;
	//	cout << "R size :" << imgR.cols << " , " << imgR.rows << endl;
	//	Rect rectCut = Rect(imgL.cols - 200 , 0, 200,imgL.rows / 2);
	//
	//	Rect rectMatched = Rect(0, 0, imgR.cols, imgR.rows);
	//	Mat imgTemp = grayL(Rect(rectCut));
	//	Mat imgMatched = grayR(Rect(rectMatched));
	//	int width = imgMatched.cols - imgTemp.cols + 1;
	//	int height = imgMatched.rows - imgTemp.rows + 1;
	//	Mat matchResult(height, width, CV_32FC1);
	//	matchTemplate(imgMatched, imgTemp, matchResult, TM_CCORR_NORMED);
	//	//normalize(matchResult, matchResult, 0, 1, NORM_MINMAX, -1);  //归一化到0--1范围
	//	

	//	double minValue, maxValue;
	//	Point minLoc, maxLoc;
	//	minMaxLoc(matchResult, &minValue, &maxValue, &minLoc, &maxLoc);
	//	
	//	if (maxValue > 0.98) {
	//		Mat dstImg(imgL.rows, imgR.cols + rectCut.x - maxLoc.x, CV_8UC3, Scalar::all(0));
	//		Mat roiLeft = dstImg(Rect(0, 0, imgL.cols, imgL.rows));
	//		imgL.copyTo(roiLeft);
	//		Mat roiMatched = imgR(Rect(maxLoc.x, maxLoc.y - rectCut.y, imgR.cols - maxLoc.x, imgR.rows - 1 - (maxLoc.y - rectCut.y)));
	//		Mat roiRight = dstImg(Rect(rectCut.x, 0, roiMatched.cols, roiMatched.rows));
	//		roiMatched.copyTo(roiRight);
	//		tempImg = dstImg;
	//		//line(tempImg, Point(rectCut.x, 0), Point(rectCut.x, 1000), Scalar(0, 0, 255), 5, CV_AA);
	//		line(tempImg, Point(rectCut.x-maxLoc.x, 0), Point(rectCut.x-maxLoc.x, 1000), Scalar(255, 0, 255), 5, CV_AA);
	//		location[i - 1] = rectCut.x;
	//	}
	//	else {
	//		Mat dstImg(imgL.rows, imgL.cols + imgR.cols, CV_8UC3, Scalar::all(0));
	//		Mat roiLeft = dstImg(Rect(0, 0, imgL.cols, imgL.rows));
	//		imgL.copyTo(roiLeft);
	//		Mat roiMatched = imgR(Rect(0, 0, imgR.cols , imgL.rows ));
	//		Mat roiRight = dstImg(Rect(imgL.cols, 0, imgR.cols, imgL.rows));
	//		roiMatched.copyTo(roiRight);
	//		tempImg = dstImg;
	//		line(tempImg, Point(imgL.cols, 0), Point(imgL.cols, 1000), Scalar(0, 0, 255), 5, CV_AA);
	//		location[i - 1] = imgL.cols;
	//		
	//	}
	//	
	//	
	//	
	//	cout << "匹配值: " << maxValue<<" , "<<"最小值： "<<minValue << endl;
	//}
	//for (int i = 0; i < 4; i++) {
	//	location[i] = location[i] / tempImg.cols;
	//	cout << location[i] << endl;
	//}
	//double end = getTickCount();
	//double useTime = (end - start) / getTickFrequency();
	//cout << "use-time : " << useTime << "s" << endl;
	//namedWindow("temp" ,WINDOW_NORMAL);
	//imshow("temp", tempImg);
	//waitKey();

	/*vector<Mat> imgs;
	for (int i = 1; i < 5; i++) {
		Mat img = imread("F://Baoxin//steel2//IM//" + to_string(i) + ".jpg");
		if (img.empty()) {
			cout << "Can't read image" << endl;
		}
		imgs.push_back(img);
	}*/

	/*Mat imgL = imread("F:\\Baoxin\\steel2\\IM\\1.jpg");
	Mat imgR = imread("F:\\Baoxin\\steel2\\IM\\2.jpg");*/
	//Mat imgL = imgs.at(2);
	//Mat imgR = imgs.at(3);
	//double start = getTickCount();
	//Mat grayL, grayR;

	//cvtColor(imgL, grayL, COLOR_BGR2GRAY);
	//cvtColor(imgR, grayR, COLOR_BGR2GRAY);
	//
	//cout <<"L size :" << imgL.cols << " , " << imgL.rows << endl;
	//cout << "R size :" << imgR.cols << " , " << imgR.rows << endl;
	//Rect rectCut = Rect(imgL.cols - 300 , 300, 200,imgL.rows/2);
	//
	//Rect rectMatched = Rect(0, 0, imgR.cols, imgR.rows);
	//Mat imgTemp = grayL(Rect(rectCut));
	//Mat imgMatched = grayR(Rect(rectMatched));
	//int width = imgMatched.cols - imgTemp.cols + 1;
	//int height = imgMatched.rows - imgTemp.rows + 1;
	//Mat matchResult(height, width, CV_32FC1);
	//matchTemplate(imgMatched, imgTemp, matchResult, TM_CCORR_NORMED);
	//normalize(matchResult, matchResult, 0, 1, NORM_MINMAX, -1);  //归一化到0--1范围


	//double minValue, maxValue;
	//Point minLoc, maxLoc;
	//minMaxLoc(matchResult, &minValue, &maxValue, &minLoc, &maxLoc);
	//Mat dstImg(imgL.rows, imgR.cols + rectCut.x - maxLoc.x, CV_8UC3, Scalar::all(0));
	//cout << dstImg.cols<<" , "<<rectCut.x << " , "<<maxLoc.x << endl;
	//Mat roiLeft = dstImg(Rect(0, 0, imgL.cols, imgL.rows));

	//imgL.copyTo(roiLeft);

	//cout << "okk" << endl;
	//cout << "maxLocY" << maxLoc.y << "rectCut: "<<rectCut.y << endl;
	//cout<<" imgRCols: "<<imgR.cols<<"maxLocX: "<<maxLoc.x << endl;
	//Mat roiMatched = imgR(Rect(maxLoc.x, maxLoc.y - rectCut.y, imgR.cols - maxLoc.x, imgR.rows - 1 - (maxLoc.y - rectCut.y)));
	//Mat roiRight = dstImg(Rect(rectCut.x, 0, roiMatched.cols, roiMatched.rows));
	//cout <<"error" << endl;
	//roiMatched.copyTo(roiRight);

	//double end = getTickCount();
	//double useTime = (end - start) / getTickFrequency();
	//cout << "use-time : " << useTime << "s" << endl;

	//namedWindow("dst", WINDOW_NORMAL);
	//imshow("dst", dstImg);
	//cout << "Done!" << endl;
	//waitKey();
	return 0;

}