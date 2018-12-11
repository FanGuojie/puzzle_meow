#include "Puzzle.h"
extern int M, N;


Puzzle::Puzzle(INTVEC num)
{
	arr = num;
	ok = num;
	string path ="";
	pair<INTVEC, string>p(ok, path);
	possible.insert(p);
}

Puzzle::~Puzzle()
{
}


void Puzzle::addPossible(string dir, INTVEC & move, string & basepath,queue<INTVEC> &q)
{
	if (possible.find(move) == possible.end()) {
		string newpath=basepath;
		newpath+=dir;
		pair<INTVEC, string>p(move, newpath);
		possible.insert(p);
		q.push(move);

	}
}

void Puzzle::showPossible()
{
	for (auto i = possible.begin(); i != possible.end(); i++)
	{
		printNum(i->first);
		string path = i->second;
		reverse(path.begin(), path.end());
		cout << "对应路径: " << path << endl;
	}
	printseg();
}

void Puzzle::getAll() {
	queue<INTVEC> q;
	q.push(ok);
	while (!q.empty())
	{
		INTVEC iter = q.front();
		string path = possible.find(iter)->second;
		Loc loc=getLoc(iter);
		INTVEC move;//还原路径和操作路径相反
		move = up(iter, loc);
		addPossible("S", move, path, q);
		move = down(iter, loc);
		addPossible("W", move, path, q);
		move = left(iter, loc);
		addPossible("D", move, path, q);
		move = right(iter, loc);
		addPossible("A", move, path, q);
		q.pop();
	}
}



bool Puzzle::available()
{
	cout << "分析是否可行" << endl;
	getAll();

	if (possible.find(arr) != possible.end()) {
		cout << "可行" << endl;
		printseg();
		return true;
	}
	return false;
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
}

void Puzzle::shuffleShow()
{
	srand(unsigned(time(0)));
	random_shuffle(arr.begin(), arr.end());
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
	cout << "输入保存图片的名称(输入y默认是loveLT.png)" << endl;
	string name;
	cin >> name;
	if (name == "y") {
		printDefault("loveLT.png");
		name = "loveLT.png";
	}
	cout << "输入完整路径名，保存当前状态对应的图像(输入y默认保存图片的路径是.\\splice\\)" << endl;
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
	cout << "自动还原" << endl;
	string path = possible.find(arr)->second;
	reverse(path.begin(), path.end());
	cout << "还原路径如下" << endl;
	cout << path << endl;
	printseg();
}

bool Puzzle::check()
{
	return arr == ok;
}
