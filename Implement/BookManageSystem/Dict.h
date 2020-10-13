#pragma once
#include<iostream>
#include<string>
#include"AList.h"
#include <windows.h>
#include<fstream>
using namespace std;

template<class E>
class Dict {
public:
	virtual void insert(const string& k, const E& e) = 0;//�ü�k����һ����¼
	virtual E find(const string& k)const = 0;//���ؼ�k�ļ�¼
};

class Book {
	//��¼��ʵ��
private:
	string ISBN;
	string Name;
	string Author;
	string Price;
	string Publisher;
	string PrintTime;
	string Mark="�ϼ�";
	string Key ;
public:
	Book(string inISBN, string inName, string inAuthor,
		string inPrice, string inPublisher, string inPrintTime,string inMark = "�ϼ�")
	{
		ISBN = inISBN;
		Name = inName;
		Author = inAuthor;
		Price = inPrice;
		Publisher = inPublisher;
		PrintTime = inPrintTime;
		Mark = inMark;
	}
	~Book() {}

	string getISBN() { return ISBN; }
	string getName() { return Name; }
	string getPrice() { return Price; }
	string getAuthor() { return Author; }
	string getPublisher() { return Publisher; }
	string getPrintTime() { return PrintTime; }
	string getMark() { return Mark; }
	bool isSale() { return (Mark == "�ϼ�") ? true : false; }
	string getKey() { Key = ISBN + Name; return Key; }
	void mark()
	{
		Mark = "���¼�";
	}
};

template<class E>
class KVpair
{
private:
	string k;
	E e;
public:
	KVpair() {}
	KVpair(string kval, E eval) { k = kval; e = eval; }
	KVpair(const KVpair& o) { k = o.k; e = o.e; }

	void operator=(const KVpair& o) { k = o.k; e = o.e; }
	string key1() { return k.substr(0,13); }
	string key2() { return k.substr(13); }
	void setKey(string ink) { k = ink; }
	E value() { return e; }
};

ostream& operator<<(ostream& out, Book* book)
{//����<<ʹ����Դ�ӡ��
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	if (book != nullptr) {
		out << "ISBN��:" << book->getISBN() << endl
			<< "����:" << book->getName() << endl
			<< "����:" << book->getAuthor() << endl
			<< "�۸�:" << book->getPrice()  << endl
			<< "���淢�е�λ:" << book->getPublisher() << endl
			<< "����ʱ��:" << book->getPrintTime()<<endl 
			<< "״̬:" << book->getMark() << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		return out;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	//cout << "�鼮������" << endl;
	return out;
}

template< class E>
class Adict :public Dict< E> {
private:
	SeqList<KVpair<E>>* list;
public:
	Adict(int size = defaultSize)
	{
		list = new SeqList<KVpair< E>>(size);
	}
	~Adict()
	{
		delete list;
	}

	void insert(const string& k, const E& e)
	{
		KVpair<E> temp(k, e);
		list->append(temp);
	}
	E remove(const string& k) {
		for (int i = 1; i < list->length() + 1; i++)
		{
			Book* cBook;
			KVpair<E>temp = list->getValue(i);
			cBook = temp.value();
			if (k == temp.key1() || k == temp.key2())
			{
				if (cBook->isSale()) {
					list->remove(i);
					cout << "�����鼮����ɾ��" << endl;
					return temp.value();
				}
			}
		}
		cout << "���鼮�����ڣ�ɾ��ʧ��" << endl;
		return nullptr;
	}

	E removeLazy(const string& k) {
		for (int i = 1; i < list->length() + 1; i++)
		{
			KVpair<E>temp = list->getValue(i);
			Book* cBook;
			cBook = temp.value();
			if (k == temp.key1() || k == temp.key2())
			{
				if (cBook->isSale()) {
					cBook->mark();
					cout << "�����鼮�����¼�" << endl;
					return temp.value();
				}
			}
		}
		cout << "���鼮�����ڣ��¼�ʧ��" << endl;
		return nullptr;
	}

	void removeAlist(int j) {
		list->remove(j);
	}

	E find(const string& k)const {
		Book* cBook;
		KVpair<E>temp;
		int j = -1;
		for (int i = 1; i < list->length() + 1; i++)
		{
			temp = list->getValue(i);
			cBook = temp.value();
			if ((k == temp.key1() || k == temp.key2()) && cBook->isSale()) { j = i; break; }

		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		if (j == -1) { cout << "���鼮������" << endl; return nullptr; }
		cout << "���鼮��Ϣ���£�" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		return temp.value();
	}

	void print()
	{
		KVpair<E>temp;
		Book* cBook;
		int sum = list->length();
		cout << "*************************************" << endl;
		cout << "��ǰ���飺"; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		for (int i = 1; i < list->length() + 1; i++)
		{
			temp = list->getValue(i);
			cBook = temp.value();
			if (!cBook->isSale())
				sum--;
		}
		cout << sum;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "��" << endl; cout << endl;
		for (int i = 1; i < list->length() + 1; i++)
		{
			temp = list->getValue(i);
			cBook = temp.value();
			if (cBook->isSale())
				cout << temp.value() << endl;
		}
	}

	int getLength()
	{
		return list->length();
	}

	string BookStore(int i)
	{
		string newbook;
		KVpair<E>temp;
		temp = list->getValue(i);
		Book* book = temp.value();
		if (book->isSale()) {
			newbook =
				"\nISBN��:" + book->getISBN() +
				"\n����:" + book->getName()
				+ "\n����:" + book->getAuthor()
				+ "\n�۸�:" + book->getPrice()
				+ "\n���淢�е�λ:" + book->getPublisher()
				+ "\n��������:" + book->getPrintTime()
				+ "\n״̬:" + book->getMark()
				+ "\n---------------*";
			return newbook;
		}
		return "";
	}
};