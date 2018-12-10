#include "Img.h"

extern int M, N;
Img::Img(string imgPath)
{
	path = imgPath;
}


Img::~Img()
{
}

void Img::setsegPath(string str)
{
	segPath = str;
}

void Img::setsplicePath(string str)
{
	splicePath = str;
}

void Img::segment()
{
	//cout << "分割图片" << endl;
	Mat img = imread(path); //将图像放在项目工程里，使用imread函数读取
	int t = 0;
	int m = M;    //m*n是切割后子图像的个数
	int n = N;
	int l = img.cols / M, w = img.rows / N;
	vector<Mat> ceil_img;  //迭代器ceil_img存储子图像
	vector<int> name;     //迭代器name存储子图像的名字，从0到m*n-1
	for (t; t < m*n; t++)
		name.push_back(t);
	Mat image_cut, roi_img, tim_img;
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < m; i++)
		{
			Rect rect(i * l, j * w, l, w);
			image_cut = Mat(img, rect);
			roi_img = image_cut.clone();
			ceil_img.push_back(roi_img);
		}
	}
	for (int t = 0; t < m*n - 1; t++) {
		imwrite(segPath + to_string(name[t]) + ".png", ceil_img[t]);
	}
	Mat pure = generatePure(ceil_img[0]);
	imwrite(segPath + to_string(-1) + ".png", pure);

}

void Img::splice(vector<int> arr,string name,string outPath)
{
	if (outPath == " ")
		outPath = splicePath;
	//cout << "拼接图片" << endl;
	Mat row;
	Mat combine;
	string filename;
	filename = segPath + to_string(0) + ".png";
	combine = imread(filename);
	for (int j = 1; j < M; j++)
	{
		filename = segPath + to_string(arr[j]) + ".png";
		Mat img = imread(filename);
		hconcat(combine, img, combine);
	}
	for (int i = 1; i < N; i++)
	{
		filename = segPath + to_string(arr[i*M]) + ".png";
		row = imread(filename);
		for (int j = 1; j < M; j++)
		{
			filename = segPath + to_string(arr[i*M + j]) + ".png";
			Mat img = imread(filename);
			hconcat(row, img, row);
		}
		vconcat(combine, row, combine);
	}
	//namedWindow("Combine",CV_WINDOW_AUTOSIZE);
	//imshow("Combine",combine);
	imwrite(outPath + name, combine);
}
inline Mat generatePure(Mat src)
{
	Mat M(src.size(), CV_8UC1);
	M = Scalar(255);
	return M;
}

int readImg(string path)
{
	Mat src;
	//加载图片
	src = imread(".\\img\\lena_400_225.jpg", 1);
	//检测是否加载成功
	if (!src.data)  //or == if(src.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	// 创建窗口
	namedWindow("Display");
	//显示图像
	imshow("Display", src);

	waitKey(0);
	return 1;
}

