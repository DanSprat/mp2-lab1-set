// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля
#include <sstream>
#include <vector>
#include "tset.h"

TSet::TSet(const int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?

{
	if (BitField.GetBit(Elem) == 1)
		return 1;
	else return 0;


}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (!IsMember(Elem))
		BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (IsMember(Elem))
		BitField.ClrBit(Elem);

}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return (*this);
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return 0;
	else
	{
		if (BitField == s.BitField)
			return 1;
		else return 0;
	}

}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return 1;
	{
		if (BitField != s.BitField)
			return 1;
		else
			return 0;
	}
}

TSet TSet::operator+(const TSet &s) // объединение
{

	TSet help(*this);
	help.BitField = BitField | s.BitField;
	if (help.MaxPower > s.MaxPower)
	{
	}
	else
		help.MaxPower = s.MaxPower;
	return help;


}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > MaxPower - 1)
		throw 1;
	else
	{
		BitField.SetBit(Elem);
		return (*this);
	}

}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem > MaxPower - 1)
		throw 1;
	else
	{
		BitField.ClrBit(Elem);
		return (*this);
	}

}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet help(*this);
	help.BitField = BitField & s.BitField;
	if (help.MaxPower > s.MaxPower)
	{
	}
	else
		help.MaxPower = s.MaxPower;
	return help;
}

TSet TSet::operator~(void) // дополнение
{
	TSet help(*this);
	help.BitField = ~BitField;
	return help;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	string str;
	vector <int> input;
	int word;
	cout << str;
	for (istringstream is(str); is >> word;)
	{
		input.push_back(word);
	}
	vector<int>::const_iterator it;
	for (it = input.begin(); it != input.end(); it++)
	{
		(s.BitField.SetBit(*it));
	}

	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{


	for (int i = 0; i < s.GetMaxPower(); i++)
	{
		if (s.BitField.GetBit(i) > 0)
			cout << i;
	}
	return ostr;
}
