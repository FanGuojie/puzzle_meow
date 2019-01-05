#include "distance.h"

Dis::Dis(int n,int m)
{
	this->n = n;
	this->m = m;
	Manha.resize(n*m);
	for (int i = 0; i < n*m; i++)
	{
		Manha[i].resize(n*m);
		int ni = i / n;
		int mi = i % n;
		for (int j = 0; j < i; j++)
		{
			int nj = j / n;
			int mj = j % m;
			Manha[i][j] = abs(ni - nj) + abs(mi - mj);
			Manha[j][i] = Manha[i][j];
		}
	}

	//输出到文件
	string filename = "distance.txt";
	ofstream dis(filename);
	dis << n << " " << m << endl;
	if (dis) {//创建成功
		cout << "输出到文件" << endl;
		for (int  i = 0; i < n*m; i++)
		{
			for (int j = 0; j < n*m; j++)
			{
				dis << Manha[i][j] << " ";
			}
			dis << endl;
		}
		dis.close();
	}
	else {
		cout << "创建文件失败" << endl;
	}
	
}

Dis::~Dis()
{
}

/*
int main() {
	cout << "test" << endl;
	Dis dis(3,3);
}
*/