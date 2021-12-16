#include <fstream>
using namespace std;

int main()
{
	ofstream file;
	file.open("zc.dat");
	for (int i=0;i<53;i++)
	{
		file<<"<"<<0<<", "<<0<<", "<<1<<">"<<endl;
	}
	for (int i=53;i<157;i++)
    {
        file<<"<"<<0<<", "<<0<<", "<<-1<<">"<<endl;
    }
    for (int i=157;i<210;i++)
    {
        file<<"<"<<0<<", "<<0<<", "<<1<<">"<<endl;
    }
    
	file.close();
	return 0;
}
