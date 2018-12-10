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
	cin >> imgPath;
	Img img(imgPath);

	cin >> N >> M;
	img.setsegPath(".\\segmentImg\\");
	img.setslicePath(".\\splice\\");
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
	img.splice(p.arr);//图片拼接
	//______________________图片数值展示与随机打乱________________________

	cout << "init show" << endl;
	p.showMat(); //init show
	printseg();
	p.shuffleShow();
	printseg();
	//______________________验证拼图可行性________________________
	//if (!available(num)) {
	/*while (!p.available()) {
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
	}*/
	//______________________开始游玩________________________
	cout << "欢迎游玩" << endl;
	printRule();
	while (1) {
		char t = _getch();
		switch (t)
		{
		case 'W':
		case 'A':
		case 'S':
		case 'D':
			p.puzzleMove(t);
			if (p.check()) {
				cout << "恭喜完成" << endl;
			}
			break;
		case 'R':
			p.restart();
			break;
		case 'G':
			p.saveImg();
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
			system("pause");
			exit(1);
			break;
		default:
			cout << "非法输入，请看规则，重新输入" << endl;
			printseg();
			printRule();
		}
	}

	//system("pause");
	return 0;
}
