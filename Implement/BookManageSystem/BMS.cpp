#include"AList.h"
#include"Dict.h"
#include <windows.h>
#include<fstream>
using namespace std;

Adict<Book*> Bookdict;
int judge;
Book* currentBook;
int num = 0;
void bookStore()
{
	ofstream book("D:\\Books.txt", ios::in | ios::out|ios::trunc);
	for (int i = 1; i <= Bookdict.getLength(); i++)
		book << Bookdict.BookStore(i) ;
	book.close();
}

void readBook()
{
	int i = 0; int j = 0;
	string tmp;
	string inISBN; string inName; string inAuthor; string inPrice; string inPublisher; string inPrintTime; string inMark;
	ifstream book("D:\\Books.txt", ios::in | ios::out );
	while (!book.eof())
	{
		tmp = book.get();
		if (tmp == ":") { tmp.pop_back(); j++; };
		if (tmp == "\n") { tmp.pop_back(); i++; }
		if (j == 1 && i == 1)inISBN = inISBN + tmp;
		if (j == 2 && i == 2)inName = inName + tmp;
		if (j == 3 && i == 3)inAuthor = inAuthor + tmp;
		if (j == 4 && i == 4)inPrice = inPrice + tmp;
		if (j == 5 && i == 5)inPublisher = inPublisher + tmp;
		if (j == 6 && i == 6)inPrintTime = inPrintTime + tmp;
		if (j == 7 && i == 7)inMark = inMark + tmp;
		if (tmp=="*")
		{
			Book* newBook = new Book(inISBN, inName, inAuthor, inPrice, inPublisher, inPrintTime,inMark);
			Bookdict.insert(newBook->getKey(), newBook);
			i = 0;  j = 0;
			inISBN = ""; inName = ""; inAuthor = ""; inPrice = ""; inPublisher = ""; inPrintTime = ""; inMark = "";
		}
	}
}

void start()
{
	cout << endl;
	cout << "*************************************" << endl<<endl;
	cout << "1.添加图书	2.查看当前藏书" << endl; cout << endl;
	cout << "3.删除图书	4.查找图书" << endl; cout << endl;
	cout << "5.下架图书" << endl; cout << endl;
	cout << "*************************************" << endl;
	cout << "	*请输入功能选项：";
}

void addBook()
{
	cout << endl;
	cout << "*************************************" << endl;
	cout << "添加一本书" << endl;
	string inISBN; string inName; string inAuthor; string inPrice; string inPublisher; string inPrintTime;
	cout << "请输入书籍ISBN号："; 
	while (cin >> inISBN)
	{
		if (inISBN.length() == 13)break;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		cout << "输入错误，ISBN号为13位数字" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "请重新输入书籍ISBN号：";
	}
	cout << "请输入书籍名字："; cin >> inName;
	cout << "请输入书籍作者："; cin >> inAuthor;
	cout << "请输入书籍价格："; cin >> inPrice;
	cout << "请输入书籍出版发行单位："; cin >> inPublisher;
	cout << "请输入书籍出版日期："; cin >> inPrintTime;
	Book* newBook = new Book(inISBN, inName, inAuthor, inPrice, inPublisher, inPrintTime);
	Bookdict.insert(newBook->getKey(), newBook);
}

void removeBook()
{
	cout << endl;
	cout << "*************************************" << endl;
	cout << "请输入删除图书的ISBN号或名字:" ;
	string ISBN;
	cin >> ISBN;
	cout<<Bookdict.remove(ISBN);
}

void removeLazyBook()
{
	cout << endl;
	cout << "*************************************" << endl;
	cout << "请输入下架图书的ISBN号或名字:";
	string ISBN;
	cin >> ISBN;
	cout << Bookdict.removeLazy(ISBN);
}

void findBook()
{
	cout << endl;
	cout << "*************************************" << endl;
	cout << "请输入查找图书的ISBN号或名字:";
	string ISBN;
	cin >> ISBN;
	cout << Bookdict.find(ISBN);
}

int main()
{
	cout << "*************************************" << endl << endl;
	cout << "      欢迎使用密大图书管理系统" << endl; cout << endl;
	cout << "本系统将会在D盘下生成一个Books.txt文件保存书单" << endl; cout << endl;
	ofstream book("D:\\Books.txt", ios::in | ios::out );
	book.close();
	readBook();
	while (true)
	{
		start();
		cin >> judge;
		switch (judge)
		{
		case(1):
			addBook();
			cout << "添加完毕" << endl;
			bookStore();
			break;
		case(2):
			Bookdict.print();
			break;
		case(3):
			removeBook();
			bookStore();
			break;
		case(4):
			findBook();
			break;
		case(5):
			removeLazyBook();
			bookStore();
			break;
		}
	}
}
