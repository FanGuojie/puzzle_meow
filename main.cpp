#include<iostream>
#include<string>
#include<conio.h>
#include<stdio.h>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>    
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/imgproc/imgproc.hpp>  


#include "Puzzle.h"
#include "util.h"
#include "Img.h"
#define Vec vector<Mat>
using namespace std;
using namespace cv;
int M=0, N=0;

int main(int argc, char const *argv[]) {
	//______________________读取图片目录 & 设置难度 N M________________________
	string imgPath;//图片目录
	cout << "请输入背景图片的路径(输入y使用默认的图片 仙女喵.png)" << endl;
	cin >> imgPath;
	if (imgPath == "y") {
		printDefault(" 仙女喵.png ");
		imgPath = "C:\\Users\\fgj\\source\\repos\\puzzle\\puzzle\\img\\lena_400_225.jpg";
	}
	Img img(imgPath);
	cout << "现在把图片划分成N*M的大小，请输入参数以确定游戏难度(输入y使用默认参数3*3）" << endl;
	string tmp;
	cin >> tmp;
	if (tmp == "y") {
		printDefault("3 * 3");
		N = 3;
		M = 3;
	}
	else {
		N = tmp[0]-'0';
		cin >> M;
	}
	img.setsegPath(".\\segmentImg\\");
	img.setsplicePath(".\\splice\\");
	/*while (!readImg(path)) {
		cout << "重新输入图片路径" << endl;
		cin >> path;
	}*/
	//设置难度 图片划分成M*N,并将右下角的图片块去掉
	//_____________________拼图初始化_________________________
	vector<int> num(M*N);
	for (int i = 0; i < M*N - 1; i++)
	{
		num[i] = i;
	}
	num[M*N - 1] = -1;
	Puzzle p(num);
	//______________________图片的分割和拼接________________________
	img.segment();
	img.splice(p.arr, "combine.png");//图片拼接
	//______________________图片数值展示与随机打乱________________________

	cout << "init show" << endl;
	p.showMat(); //init show
	printseg();
	p.shuffleShow();
	printseg();
	//______________________验证拼图可行性________________________
	//if (!available(num)) {
	while (!p.available()) {
		cout << "拼图不可完成,q键退出，压其余任意按键重新生成拼图" << endl;
		char t = _getch();
		if (t == 'q') {
			cout << "欢迎使用" << endl;
			system("pause");
			exit(1);
		}
		else {
			p.shuffleShow();
			printseg();
		}
	}
	//p.showPossible();

	//______________________开始游玩________________________
	cout << "欢迎游玩" << endl;
	printRule();
	while (1) {
		char t = _getch();
		t = toCaption(t);
		switch (t)
		{
		case 'W':
		case 'A':
		case 'S':
		case 'D':
			p.puzzleMove(t);
			if (p.check()) {
				cout << "恭喜完成,游戏退出" << endl;
				exit(1);
			}
			break;
		case 'R':
			p.restart();
			break;
		case 'G':
			p.saveImg(img);
			break;
		case 'I':
			p.save();
			break;
		case 'O':
			p.load();
			break;
		case 'F':
			p.reduction();
			break;
		case 'P':
			cout << "退出游戏，欢迎使用" << endl;
			//system("pause");
			exit(1);
			break;
		default:
			cout << "非法输入，请看规则，重新输入" << endl;
			printRule();
		}
	}

	//system("pause");
	return 0;
}
