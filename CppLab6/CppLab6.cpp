#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

struct Client
{
	string name;
	float monthCost;
	int monthsPaidTotal;
	int nextMonthsPaid;

	void calc()
	{
		nextMonthsPaid = monthsPaidTotal - 1;
	}

	void printInfo()
	{
		cout << "Name: " << name;
		cout << "\nMonth Cost: " << monthCost;
		cout << "\nMonths Paid: " << monthsPaidTotal;
		cout << "\nNext Months Paid: " << nextMonthsPaid << "\n";
	}
};

Client init()
{
	Client client;
	client.name = "";
	client.monthCost = 0;
	client.monthsPaidTotal = 0;
	client.calc();

	return client;
}

int main()
{
	srand(time(0));

	const char* PATH = "D:\\CppLab5.lab";
	Client client;

	client.name = "Vasiliy Petrovich";
	client.monthCost = (rand() % 111) + 90;
	client.monthsPaidTotal = (rand() % 6) + 1;
	client.calc();

	client.printInfo();

	ofstream out(PATH, ios::binary);
	out.write((char*)&client, sizeof(client));
	out.close();

	Client fromFile;

	ifstream inp(PATH, ios::binary);
	inp.read((char*)& fromFile, sizeof(client));
	inp.close();

	if (fromFile.nextMonthsPaid > 3)
	{
		fromFile.monthCost -= (fromFile.monthCost / 100) * 5;

		ofstream out(PATH, ios::binary);
		out.write((char*)&fromFile, sizeof(fromFile));
		out.close();

		ifstream inp(PATH, ios::binary);
		inp.read((char*)& fromFile, sizeof(client));
		inp.close();
	}

	fromFile.printInfo();

	system("pause");
}