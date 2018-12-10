#include "Puzzle.h"
extern int M, N;

typedef struct Loc
{
	int x, y;
}Loc;
Puzzle::Puzzle(vector<int> num)
{
	arr = num;
}

Puzzle::~Puzzle()
{
}

bool Puzzle::available()
{
	cout << "分析是否可行" << endl;
	return true;
}
Loc getLoc(vector<int>num)
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
//得到一列数据
inline vector<int> getCol(vector<int> &num, int x) {
	vector<int> col;
	for (int i = 0; i < N; i++)
	{
		if (num[i*M + x] == -1)
			continue;
		col.push_back(num[i*M + x]);
	}
	return col;
}
inline vector<int> getRow(vector<int> &num, int y) {
	vector<int> row;
	for (int i = 0; i < M; i++)
	{
		if (num[y*M + i] == -1)
			continue;
		row.push_back(num[y*M + i]);
	}
	return row;
}
void up(vector<int> &num, int x) {
	vector<int> col = getCol(num, x);
	num[x] = -1;
	for (int i = 1; i < N; i++)
	{
		num[i*M + x] = col[i - 1];
	}
}

void down(vector<int> &num, int x) {
	vector<int> col = getCol(num, x);
	num[(N - 1)*M + x] = -1;
	for (int i = 0; i < N - 1; i++)
	{
		num[i*M + x] = col[i];
	}
}
void left(vector<int> &num, int y) {
	vector<int> row = getRow(num, y);
	num[y*M] = -1;
	for (int i = 0; i < M - 1; i++)
	{
		num[y*M + i + 1] = row[i];
	}
}
void right(vector<int> &num, int y) {
	vector<int> row = getRow(num, y);
	num[y*M + M - 1] = -1;
	for (int i = 0; i < M - 1; i++)
	{
		num[y*M + i] = row[i];
	}
}

void Puzzle::puzzleMove(char t)
{
	//定位空格位置
	Loc loc = getLoc(arr);
	switch (t)
	{
	case 'W':
		cout << "空格上移" << endl;
		up(arr, loc.x);
		showMat();
		printseg();
		break;
	case 'A':
		cout << "空格左移" << endl;
		left(arr, loc.y);
		showMat();
		printseg();
		break;
	case 'D':
		cout << "空格右移" << endl;
		right(arr, loc.y);
		showMat();
		printseg();
		break;
	case 'S':
		cout << "空格下移" << endl;
		down(arr, loc.x);
		showMat();
		printseg();
		break;
	default:
		break;
	}
}

void Puzzle::showMat()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << arr[i*M + j] << "\t";
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
	if(name=="y")
		name = "loveLT.png";
	cout << "输入完整路径名，保存当前状态对应的图像(输入y默认保存图片的路径是.\\splice\\)" << endl;
	string path;
	cin >> path;
	if (path == "y") {
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
	pair<string, vector<int>> p(name, arr);
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
}

bool Puzzle::check()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (arr[i*M + j] != i * M + j)
				return false;
		}
	}
	return true;
}
