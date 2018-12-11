#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<conio.h>
#include <algorithm>    // std::random_shuffle
#include <ctime>        // std::time
#include <map>
#include <set>
#include <queue>
#include <stack>
#include "util.h"
#include "Img.h"
#define INTVEC vector<int>
using namespace std;


typedef struct Loc
{
	int x, y;
}Loc;
INTVEC up(INTVEC num, Loc loc);
INTVEC down(INTVEC num, Loc loc);
INTVEC left(INTVEC num, Loc loc);
INTVEC right(INTVEC num, Loc loc);
typedef INTVEC (*op)(INTVEC, Loc);
Loc getLoc(INTVEC num);//计算arr的位置
void addMap(string dir, INTVEC & move, string & basepath, queue<INTVEC> &q, map<INTVEC, string>& map);
void updateMap(queue <INTVEC>&q, map<INTVEC, string>& map);
class Puzzle
{
public:
	INTVEC arr;
	Puzzle(INTVEC num);
	~Puzzle();
	bool available();

	void puzzleMove(char t); 
	void showMat(INTVEC num = {});
	void shuffleShow(); 
	void restart(); 
	void saveImg(Img img); 
	void save(); 
	void load(); 
	void reduction(); 
	bool check();
	void showPossible();
	void getAll();
	void preview(Img img);
private:
	void bfs();//广度优先搜索，得到最短还原路径
	void dfs();//深度优先搜索，得到快速还原路径
	bool canMove(stack<INTVEC>&s, set<INTVEC>&set,string &path2,op op, string &path1, int index);
	int flag;//ok的逆序对加上-1的位置
	INTVEC ok;
	INTVEC init;//用于保存最初状态，用于重新开始
	map<string, INTVEC> states;
	int getInv(INTVEC num = {});//获得数组的逆序对
	map<INTVEC, string> possible;//第一项是可行方案，第二项是到达路径
	INTVEC getSolution(map<INTVEC, string> &solution);
	void initq2(queue <INTVEC>&q);
	void updatePossible(queue <INTVEC>&q);
	/*
	用字符串路径定义
	""：完成
	W：上
	S：下
	A：左
	D：右
	*/
};

