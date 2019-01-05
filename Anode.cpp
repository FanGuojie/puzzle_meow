#include "Anode.h"
extern int M, N;


int Anode::caculate()
{
	int len = N * M;
	//for (int i = 0; i < len; i++)
	//{
	//	for (int j = 0; j < len; j++)
	//	{
	//		cout << Manha[i*len+j] << " ";
	//	}
	//	cout << endl;
	//}
	h = 0;
	for (int i = 0; i <len; i++)
	{
		if (arr[i] == -1) {
			h += Manha[(len - 1)*len+i];
		}
		else {
			h += Manha[(arr[i])*len + i];
		}
	}
	f = g + h;
	return f;
}

Anode::Anode(INTVEC num, int g0)
{
	arr = num;
	g = g0;
	caculate();
	path = "";
}


void Anode::initDis()
{
	int len = N * M;
	Manha = INTVEC(len*len);
	for (int i = 0; i < len; i++)
	{
		Manha[i*len +i]=0;
		int ni = i / M;
		int mi = i % M;
		for (int j = 0; j < i; j++)
		{
			int nj = j / M;
			int mj = j % M;
			Manha[i*len +j] = abs(ni - nj) + abs(mi - mj);
			Manha[j*len +i] = Manha[i*len +j];
			cout << " i: " << i << " j: " << j << " Manha: " << Manha[i*len + j];
		}
		cout << endl;
	}
}




Anode::~Anode()
{

}
INTVEC Anode::Manha(N*N*M*M);

/*
int main() {
	INTVEC test = { -1,1,2,3,4,5,6,7 ,0 };
	//Anode::initDis();
	//Anode node(test, 0);
	//cout << node.f << endl;
}
*/


