#include "distance.h"
extern int M, N;
void Dis()
{
	vector<INTVEC> Manha(N*M, INTVEC(N*M)); 
	for (int i = 0; i < N*M; i++)
	{
		int ni = i / N;
		int mi = i % N;
		for (int j = 0; j < i; j++)
		{
			int nj = j / N;
			int mj = j % M;
			Manha[i][j] = abs(ni - nj) + abs(mi - mj);
			Manha[j][i] = Manha[i][j];
		}
	}

	//输出到文件
	string filename = "distance.txt";
	ofstream dis(filename);
	if (dis) {//创建成功
		cout << "输出到文件" << endl;
		for (int  i = 0; i < N*M; i++)
		{
			for (int j = 0; j < N*M; j++)
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

