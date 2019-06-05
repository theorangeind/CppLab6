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

	void writeToFile(const char* path)	
	{
		ofstream stream(path, ios::binary);
		int nameLength = name.length() + 1;
		
		stream.write((char*)& nameLength, sizeof(int));
		stream.write((char*)name.c_str(), nameLength);
		stream.write((char*)& monthCost, sizeof(float));
		stream.write((char*)& monthsPaidTotal, sizeof(int));
		stream.write((char*)& nextMonthsPaid, sizeof(int));
		
		stream.close();
	}

	void readFromFile(const char* path)
	{
		ifstream stream(path, ios::binary);
		int nameLength;
		stream.read((char*)& nameLength, sizeof(int));
		char* buffer = new char[nameLength];
		stream.read(buffer, nameLength);
		name = buffer;
		delete[]buffer;
		stream.read((char*)& monthCost, sizeof(float));
		stream.read((char*)& monthsPaidTotal, sizeof(int));
		stream.read((char*)& nextMonthsPaid, sizeof(int));
		stream.close();
	}

	void printInfo()
	{
		cout << "Name: " << name;
		cout << "\nMonth Cost: " << monthCost;
		cout << "\nMonths Paid: " << monthsPaidTotal;
		cout << "\nNext Months Paid: " << nextMonthsPaid << "\n";
	}
};

int main()
{
	srand(time(0));

	const char* PATH = "D:\\CppLab5.lab";
	
	Client client;

	client.name = "Vasiliy Petrovich";
	client.monthCost = (rand() % 111) + 90;
	client.monthsPaidTotal = (rand() % 6) + 1;
	client.calc();

	cout << "Writing to file this info:\n\n";

	client.printInfo();

	client.writeToFile(PATH);
	
	Client fromFile;

	fromFile.readFromFile(PATH);
	
	if (fromFile.nextMonthsPaid > 3)
	{
		fromFile.monthCost -= (fromFile.monthCost / 100) * 5;

		fromFile.writeToFile(PATH);

		fromFile.readFromFile(PATH);
	}

	cout << "\nInfo from file (if next months paid > 3, subtract 5% from cost):\n\n";

	fromFile.printInfo();

	system("pause");
}