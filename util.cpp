#include "util.h"

void printNum(vector<int> num)
{
	cout << "输出 num " << endl;
	for (int i = 0; i < num.size(); i++)
	{
		cout << num[i] << "\t";
	}
	cout << endl;
}



void printRule()
{
	cout << "操作规则如下" << endl;
	cout << "输入对应的字母，进行相应的操作" << endl;
	cout << "1. 移动" << endl;
	cout << "\tW:将空格上方的小块向下移" << endl;
	cout << "\tA:将空格左侧的小块向右移" << endl;
	cout << "\tS:将空格下方的小块向上移" << endl;
	cout << "\tD:将空格右侧的小块向左移" << endl;
	cout << "2. 重新游戏" << endl;
	cout << "\tR:重新开始游戏，恢复成打乱后的样子" << endl;
	cout << "3. 保存图像" << endl;
	cout << "\tG：下一行输入完整的路径名，保存当前状态对应的图像" << endl;
	cout << "4. 存档" << endl;
	cout << "\tI:下一行输入进度名称，保存游戏进度（游戏进度并不永久保存，只在程序运行期间有效)" << endl;
	cout << "5. 读档" << endl;
	cout << "\tO:下一行输入进度名称，载入游戏进度" << endl;
	cout << "6. 自动还原" << endl;
	cout << "\tF：自动完成拼图复原，以WASD组合形式输出复原步骤" << endl;
	cout << "7. 图片预览." << endl;
	cout << "\tX:预览图片，图片暂存在./tmp下" << endl;
	cout << "8. 重设难度." << endl;
	cout << "\tZ:重新设定N和M，打乱开始游戏" << endl;
	cout << "9. 重设背景图." << endl;
	cout << "\tC:重新输入图片地址，作为新的背景图" << endl;
	cout << "10. 退出." << endl;
	cout << "\tP:退出游戏，程序结束" << endl;
	printseg();
}

void welcome()
{
	cout << "\t******************************************************" << endl;
	cout << "\t*                                                    *" << endl;
	cout << "\t*                     welcome to                     *" << endl;
	cout << "\t*                     puzzle_meow                    *" << endl;
	cout << "\t*                                                    *" << endl;
	cout << "\t******************************************************" << endl;
	cout << "友情提示：游戏过程中如果弹出相应图片，需要先将图片关闭才能继续游戏" << endl;
	cout << endl;
}

void newBackgound(Img &img)
{
	cout << "请输入新的图片地址" << endl;
	string newPath;
	cin >> newPath;
	img.setPath(newPath);
	img.segment();
	img.readImg("漂亮的lena哟~");
}
