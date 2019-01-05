#pragma once
#include "env.h"
#include "util.h"
#include <fstream>
class Anode
{
public:
	int f, g, h;//启发函数, g为走当当前所用的步数，h为曼哈顿距离，f=g+h
	INTVEC arr;

	int caculate();
	
	string path;
	Anode(INTVEC num,int g0);
	//num 为当前的状态
	// g0为当前的步数
	~Anode();
	//static int M, N;
	static INTVEC Manha;
	static void initDis();
	
private:
};

