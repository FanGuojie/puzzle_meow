#include "Anode.h"



int Anode::caculate()
{
	int h = 0;
	for (int i = 0; i < n*m; i++)
	{
		h += Manha[(arr[i] == -1) ? n * m - 1 : arr[i]][i];
	}

	f = g + h;
	return f;
}

Anode::Anode(INTVEC num, int g0)
{
	arr = num;
	g = g0;
	string filename = "distance.txt";
	ifstream dis(filename);
	dis >> n >> m;
	Manha.resize(n*m);
	for (int i = 0; i < n*m; i++)
	{
		Manha[i].resize(n*m);
		for (int j = 0; j < n*m; j++)
		{
			dis >> Manha[i][j];
		}
	}
}



Anode::~Anode()
{

}

/*
int main() {
	INTVEC test = { -1,1,2,3,4,5,6,7 ,0 };
	Anode node(test, 0);
	cout << node.caculate() << endl;

}
*/

