#pragma once
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/Imgproc/Imgproc.hpp>
#include <string>

//#include "constant.h"

using namespace std;
using namespace cv;
inline Mat generatePure(Mat src);
int readImg(string path = "..\\img\\lena_400_225.jpg");

class Img
{
public:
	Img(string imgPath);
	~Img();
	void setsegPath(string str);
	void setsplicePath(string str);
	void segment();
	void splice(vector<int> arr,string name, string outPath=" ");


	

private:
	string path;
	string segPath;   //分割目录
	string splicePath ;//拼接目录
};

