﻿#include "Puzzle.h"
extern int M, N;


Puzzle::Puzzle(INTVEC num)
{
	arr = num;
	ok = num;
	string path = " ";
	pair<INTVEC, string>p(ok, path);
	possible.insert(p);
	int inv = getInv(ok);
	Loc loc = getLoc(ok);
	flag = (inv + loc.x + loc.y) % 2;
}

Puzzle::~Puzzle()
{
}

void Puzzle::updatePossible(queue <INTVEC>&q) {
	INTVEC iter = q.front();
	string path = possible.find(iter)->second;
	Loc loc = getLoc(iter);
	INTVEC move;//还原路径和操作路径相反
	//重构：用函数指针，循环实现四次变量
	INTVEC(*movFun[4])(INTVEC, Loc) = { up,down,left,right };
	String dir[4] = { "S","W","D","A" };
	for (int i = 0; i < 4; i++)
	{
		move = movFun[i](iter, loc);
		addMap(dir[i], move, path, q, possible);
	}
	q.pop();
}
//源和目标搜索的函数分开，原因是加入的字母相反
void updateMap(queue <INTVEC>&q, map<INTVEC, string>& map) {
	INTVEC iter = q.front();
	string path = map.find(iter)->second;
	Loc loc = getLoc(iter);
	INTVEC move;//还原路径和操作路径相反
	//重构：用函数指针，循环实现四次变量
	INTVEC(*movFun[4])(INTVEC, Loc) = { up,down,left,right };
	String dir[4] = { "W","S","A","D" };
	for (int i = 0; i < 4; i++)
	{
		move = movFun[i](iter, loc);
		addMap(dir[i], move, path, q, map);
	}
	q.pop();
}

INTVEC Puzzle::getSolution(map<INTVEC, string>& solution)
{
	queue<INTVEC>q1, q2;
	q1.push(arr);//从当前位置广搜
	//q2.push(ok);//从最终位置广搜
	initq2(q2);
	while (true)
	{
		updatePossible(q2);
		INTVEC iter1 = q1.front();
		if (possible.find(iter1) != possible.end()) {
			return iter1;
		}
		INTVEC iter2 = q2.front();
		if (solution.find(iter2) != solution.end()) {
			return iter2;
		}
		updateMap(q1, solution);

	}
}
void Puzzle::initq2(queue<INTVEC>& q)
{
	for (auto i = possible.begin(); i != possible.end(); i++)
	{
		q.push(i->first);
	}
}

void Puzzle::preview(Img img)
{
	string name = "喵喵不气啦，快好了.png";
	string path = ".//tmp//";
	img.splice(arr, name, path);
	img.readImg("杰儿爱喵的~喵不气了", path + name);
}

void Puzzle::Astar()
{
	cout << "最快还原" << endl;
	Aupdated.clear();
	Aupdated.insert(arr);
	Anode head(arr, 0);
	vector<Anode> openlist;
	openlist.push_back(head);
	Anode iter = openlist[0];
	INTVEC(*movFun[4])(INTVEC, Loc) = { up,down,left,right };
	String dir[4] = { "W","S","A","D" };
	while (iter.h != 0)
	{
		INTVEC num = iter.arr;
		//cout << "g: "<< iter.g << endl;
		//cout << "h: " << iter.h << endl;
		//for (auto it:openlist)
		//{
		//	cout << it.f << "\t";
		//}
		//cout << "f: " << iter.f << endl;
		//printseg();
		string path = iter.path;
		Loc loc = getLoc(num);
		for (int i = 0; i < 4; i++)
		{
			INTVEC move = movFun[i](num, loc);
			if (move == num || Aupdated.find(move) != Aupdated.end())
				continue;
			Aupdated.insert(move);
			Anode node(move, iter.g + 3);
			node.path = path + dir[i];
			openlist.push_back(node);
			int index = openlist.size() - 1;
			//优先队列排序,入队
			while (index >= 0 && openlist[index].f < openlist[index / 2].f)
			{
				swap(openlist[index], openlist[index / 2]);
				index /= 2;
			}

		}
		//出队
		if (num == openlist[0].arr) {
			int size = openlist.size();
			swap(openlist[0], openlist[size - 1]);
			openlist.pop_back();
			int index = 0;
			int value = openlist[0].f;
			size = openlist.size();
			while (2 * index + 2 < size ) {
				int left = openlist[index * 2 + 1].f;
				int right = openlist[index * 2 + 2].f;
				if (left < right)
				{
					if (left < value) {
						swap(openlist[index], openlist[index * 2 + 1]);
						index = index * 2 + 1;
					}
					else {
						break;
					}
				}
				else {
					if (right < value) {
						swap(openlist[index], openlist[index * 2 + 2]);
						index = index * 2 + 2;
					}
					else {
						break;
					}
				}
			}
			if (2 * index + 2 == size - 1) {
				int left = openlist[index * 2 + 1].f;
				if (left < value) {
					swap(openlist[index], openlist[index * 2 + 1]);
					index = index * 2 + 1;
				}
			}

		}
		iter = openlist[0];
	}
	cout << "还原路径如下" << endl;
	cout << iter.path << endl;
	printseg();
}

void Puzzle::bfs()
{
	cout << "最短还原" << endl;
	if (!preFind())
	{
		return;
	}
	map<INTVEC, string> solution;
	pair<INTVEC, string>p(arr, "");
	solution.insert(p);
	INTVEC mid = getSolution(solution);
	string path1 = solution.find(mid)->second;
	string path2 = possible.find(mid)->second;
	reverse(path2.begin(), path2.end());
	cout << "还原路径如下" << endl;
	cout << path1 + path2 << endl;
	printseg();
}
int Puzzle::preFind() {
	if (possible.find(arr) != possible.end()) {
		string path = possible.find(arr)->second;
		reverse(path.begin(), path.end());
		cout << "还原路径如下" << endl;
		cout << path << endl;
		return 0;
	}
	else
		return -1;
}

void Puzzle::dfs()
{
	cout << "快速还原" << endl;
	//先检查是否已经遍历过
	if (!preFind())
	{
		return;
	}
	//dfs 开始
	stack<INTVEC> s;
	set<INTVEC> set;
	set.insert(arr);
	s.push(arr);
	string path1 = "";//dfs经历的路径
	string path2 = "";//已知可行解中的路径
	op ops[4] = { up,down,left,right };
	while (true) {
	CONTINUE:
		for (int i = 0; i < 4; i++)
		{
			if (canMove(s, set, path2, ops[i], path1, i)) {
				if (path2 != "")
					return;
				goto CONTINUE;
			}
		}
		s.pop();
		path1.pop_back();
	}

}



bool Puzzle::canMove(stack<INTVEC> &s, set<INTVEC> &set, string &path2, op op, string &path1, int index)
{
	INTVEC iter = s.top();
	if (possible.find(iter) != possible.end()) {
		path2 = possible.find(iter)->second;
		cout << "还原路径如下" << endl;
		cout << path1 + path2 << endl;
		return true;
	}
	Loc loc = getLoc(iter);
	INTVEC move = op(iter, loc);
	if (set.find(move) == set.end()) {
		set.insert(move);
		s.push(move);
		switch (index)
		{
		case 0:
			path1 += "W";
			break;
		case 1:
			path1 += "S";
			break;
		case 2:
			path1 += "A";
			break;
		case 3:
			path1 += "D";
			break;
		}
		return true;
	}
	return false;
}



void addMap(string dir, INTVEC & move, string & basepath, queue<INTVEC> &q, map<INTVEC, string > &map)
{
	if (map.find(move) == map.end()) {
		string newpath = basepath;
		newpath += dir;
		pair<INTVEC, string>p(move, newpath);
		map.insert(p);
		q.push(move);
	}
}

void Puzzle::showPossible()
{
	printseg();
	cout << "所有的可能方案" << endl;
	for (auto i = possible.begin(); i != possible.end(); i++)
	{
		printNum(i->first);
		string path = i->second;
		reverse(path.begin(), path.end());
		cout << "对应路径: " << path << endl;
	}
	printseg();
}
bool debugHead(INTVEC &p) {
	for (int i = 1; i < 8; i++)
	{
		if (p[i - 1] != i)
			return false;
	}
	return p[7] == 0;
}


int Puzzle::getInv(INTVEC num)
{
	if (num.empty())
		num = arr;
	int inv = 0;
	for (int i = 1; i < N*M; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (num[i] < num[j]) {
				inv++;
			}
		}
	}
	return inv;
}



bool Puzzle::available()
{
	cout << "分析是否可行" << endl;
	int inv = getInv();
	Loc loc = getLoc(arr);
	int Curflag = inv + loc.x + loc.y;
	return Curflag % 2 == flag;
}
Loc getLoc(INTVEC num)
{
	Loc loc;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (num[i*M + j] == -1) {
				loc.y = i;
				loc.x = j;
			}
		}
	}
	return loc;
}
inline void  printLoc(Loc loc) {
	cout << "x=" + to_string(loc.x) << endl;
	cout << "y=" + to_string(loc.y) << endl;
}

INTVEC up(INTVEC num, Loc loc) {
	if (loc.y == 0)
		return num;
	int index1 = loc.y*M + loc.x;
	int index2 = index1 - M;
	swap(num[index1], num[index2]);
	return num;
}

INTVEC down(INTVEC num, Loc loc) {
	if (loc.y == N - 1)
		return num;
	int index1 = loc.y*M + loc.x;
	int index2 = index1 + M;
	swap(num[index1], num[index2]);
	return num;
}
INTVEC left(INTVEC num, Loc loc) {
	if (loc.x == 0)
		return num;
	int index1 = loc.y*M + loc.x;
	int index2 = index1 - 1;
	swap(num[index1], num[index2]);
	return num;
}
INTVEC right(INTVEC num, Loc loc) {
	if (loc.x == M - 1)
		return num;
	int index1 = loc.y*M + loc.x;
	int index2 = index1 + 1;
	swap(num[index1], num[index2]);
	return num;
}

void Puzzle::puzzleMove(char t)
{
	//定位空格位置
	Loc loc = getLoc(arr);
	switch (t)
	{
	case 'W':
		cout << "空格上移" << endl;
		arr = up(arr, loc);
		showMat();
		printseg();
		break;
	case 'A':
		cout << "空格左移" << endl;
		arr = left(arr, loc);
		showMat();
		printseg();
		break;
	case 'D':
		cout << "空格右移" << endl;
		arr = right(arr, loc);
		showMat();
		printseg();
		break;
	case 'S':
		cout << "空格下移" << endl;
		arr = down(arr, loc);
		showMat();
		printseg();
		break;
	default:
		break;
	}
}

void Puzzle::showMat(INTVEC num)
{
	if (num.empty())
		num = arr;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << num[i*M + j] << "\t";
		}
		cout << endl;
	}
	//cout << "(-1 表示空格)" << endl;
}

void Puzzle::shuffleShow()
{
	srand(unsigned(time(0)));
	do {
		random_shuffle(arr.begin(), arr.end());
	} while (arr == ok);
	cout << "shuffle show" << endl;
	showMat();
	init = arr;//每次shuffle 保存状态为最初状态
}

void Puzzle::restart()
{
	cout << "重新开始" << endl;
	arr = init;
	showMat();
	printseg();
}

void Puzzle::saveImg(Img img)
{
	cout << "输入保存图片的名称(输入 y 使用默认参数  loveLT.png)" << endl;
	string name;
	cin >> name;
	if (name == "y") {
		printDefault("loveLT.png");
		name = "loveLT.png";
	}
	cout << "输入完整路径名，保存当前状态对应的图像(输入 y 使用默认参数 .\\splice\\)" << endl;
	string path;
	cin >> path;
	if (path == "y") {
		printDefault(".\\splice\\");
		path = ".\\splice\\";
	}
	try
	{
		img.splice(arr, name, path);
	}
	catch (const std::exception&)
	{
		cout << "保存图片失败" << endl;
	}

	cout << "保存图片成功" << endl;
	printseg();
}

void Puzzle::save()
{
	cout << "输入进度名称，保存当前进度" << endl;
	string name;
	cin >> name;
	pair<string, INTVEC> p(name, arr);
	states.insert(p);
	cout << "存档成功" << endl;
	printseg();
}

void Puzzle::load()
{
	cout << "输入进度名称，载入对应的进度" << endl;
	string name;
	cin >> name;
	if (states.find(name) == states.end()) {
		cout << "对不起，没有该名称的进度" << endl;
	}
	else
	{
		cout << "读档成功" << endl;
		arr = states.find(name)->second;
	}
	showMat();
	printseg();
}

void Puzzle::reduction()
{
	cout << "输入A，快速还原，得到一条还原路径，但不是最短的" << endl;
	cout << "输入B，最短还原,用较长的时间，得到一条最短的还原路径" << endl;
	char t = _getch();
	t = toCaption(t);
	switch (t) {
	case 'A':
		//dfs();
		Astar();
		break;
	case 'B':
		bfs();
		break;
	default:
		cout << "输入错误，重新输入" << endl;
		reduction();
	}

}

bool Puzzle::check()
{
	return arr == ok;
}
