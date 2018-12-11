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

class Img
{
public:
	Img(string imgPath);
	~Img();
	void setsegPath(string str); // 设置分割目录
	void setsplicePath(string str); // 设置拼接目录
	void segment();  //图片分割
	void splice(vector<int> arr,string name, string outPath=" "); //图片拼接
	int readImg(string name,string imgPath =" "); //读取图片
private:
	string path;
	string segPath;   //分割目录
	string splicePath ;//拼接目录
};

