#include "Puzzle.h"
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
	move = up(iter, loc);
	addMap("S", move, path, q, possible);
	move = down(iter, loc);
	addMap("W", move, path, q, possible);
	move = left(iter, loc);
	addMap("D", move, path, q, possible);
	move = right(iter, loc);
	addMap("A", move, path, q, possible);
	q.pop();
}
//源和目标搜索的函数分开，原因是加入的字母相反
void updateMap(queue <INTVEC>&q, map<INTVEC, string>& map) {
	INTVEC iter = q.front();
	string path = map.find(iter)->second;
	Loc loc = getLoc(iter);
	INTVEC move;//还原路径和操作路径相反
	move = up(iter, loc);
	addMap("W", move, path, q, map);
	move = down(iter, loc);
	addMap("S", move, path, q, map);
	move = left(iter, loc);
	addMap("A", move, path, q, map);
	move = right(iter, loc);
	addMap("D", move, path, q, map);
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
		INTVEC iter = q1.front();
		//showPossible();
		//printNum(iter);
		//system("Pause");
		if (possible.find(iter) != possible.end()) {
			return iter;
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
void Puzzle::getAll() {
	queue<INTVEC> q;
	q.push(ok);
	while (!q.empty())
	{
		INTVEC iter = q.front();
		string path = possible.find(iter)->second;
		Loc loc = getLoc(iter);
		INTVEC move;//还原路径和操作路径相反
		move = up(iter, loc);
		addMap("S", move, path, q, possible);
		move = down(iter, loc);
		addMap("W", move, path, q, possible);
		move = left(iter, loc);
		addMap("D", move, path, q, possible);
		move = right(iter, loc);
		addMap("A", move, path, q, possible);
		q.pop();
		if (possible.size() % 5000 == 0)
			cout << possible.size() << endl;
		/*if (possible.size() > 30000) {
		cout << "debug:以1，2，3，4，5，6，7,0 开头的可能数目" << endl;
		for (auto i = possible.begin(); i != possible.end(); i++)
		{
		INTVEC p = i->first;
		if(debugHead(p))
		printNum(p);
		}
		system("Pause");
		}*/
	}
}

void Puzzle::preview(Img img)
{
	string name = "喵喵不气啦，快好了.png";
	string path = ".//tmp//";
	img.splice(arr, name, path);
	img.readImg("杰儿爱喵的~喵不气了", path + name);
}

void Puzzle::bfs()
{
	cout << "最短还原" << endl;
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

void Puzzle::dfs()
{
	cout << "快速还原" << endl;
	//先检查是否已经遍历过
	if (possible.find(arr) != possible.end()) {
		string path = possible.find(arr)->second;
		reverse(path.begin(), path.end());
		cout << "还原路径如下" << endl;
		cout << path << endl;
		return;
	}
	//dfs 开始
	stack<INTVEC> s;
	set<INTVEC> set;
	set.insert(arr);
	s.push(arr);
	string path1 = "";//dfs经历的路径
	string path2="";//已知可行解中的路径
	op ops[4] = { up,down,left,right };
	while (true) {
	CONTINUE:
		for (int i = 0; i < 4; i++)
		{
			if (canMove(s, set, path2, ops[i],path1,i)) {
				if (path2 != "")
					return;
				goto CONTINUE;
			}
		}
		s.pop();
		path1.pop_back();
	}

}

bool Puzzle::canMove(stack<INTVEC> &s, set<INTVEC> &set,string &path2, op op,string &path1,int index)
{
	INTVEC iter = s.top();
	if (possible.find(iter) != possible.end()) {
		path2 = possible.find(iter)->second;
		cout << "还原路径如下" << endl;
		cout << path1+path2 << endl;
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
		dfs();
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
