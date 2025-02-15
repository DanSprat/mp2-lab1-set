// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <sstream>
#include <vector>
TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw 1;
	}
	BitLen = len;
	MemLen = (BitLen / 32 + 1);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования 
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	this->pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n 

{
	return (n / 32);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n 
{

	return (1 << n % 32);
}

// доступ к битам битового поля 

int TBitField::GetLength() const // получить длину (к-во битов) 
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит 
{
	if (n < BitLen)
	{
		if (n < 0)
		{
			throw 1;
		}
		(pMem[GetMemIndex(n)]) = pMem[GetMemIndex(n)] | (GetMemMask(n));
	}
	else
	{
		throw 1;
	}

}

void TBitField::ClrBit(const int n) // очистить бит 
{
	if (n < BitLen)
	{
		if (n < 0)
		{
			throw 1;
		}
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~(GetMemMask(n));
	}
	else
	{
		throw 1;
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < BitLen)
	{
		if (n < 0)
		{
			throw 1;
		}
		else
		{
			if ((pMem[n / 32] & GetMemMask(n)) > 0)
				return 1;
			else
				return 0;
		}
	}
	else throw 1;

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf)
		return *this;
	delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return (*this);
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (MemLen != bf.MemLen)
		return 0;
	else
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				return 0;
			}
		}
		return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (bf == *this)
		return 0;
	 return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int max;
	if (BitLen > bf.BitLen)
		max = BitLen;
	else
		max = bf.BitLen;
	TBitField elem(max);

	for (int i = 0; i < (max / 32 + 1); i++)
	{
		elem.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return elem;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int min;
	if (BitLen > bf.BitLen)
		min = BitLen;
	else
		min = bf.BitLen;
	TBitField elem(min);

	for (int i = 0; i < (min / 32 + 1); i++)
	{
		elem.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return elem;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField bf(*this);
	for (int i = 0; i < bf.MemLen; i++)
	{
		bf.pMem[i] = ~(bf.pMem[i]);
		if (i == (bf.MemLen - 1))
		{
			int  check = bf.MemLen * 32 - 1;
			while (check != (bf.BitLen - 1))
			{
				bf.pMem[MemLen - 1] = bf.pMem[MemLen - 1] & (~(1 << check));
				check--;
			}
		}
	}
	return bf;
}

// ввод/вывод


istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	delete[] bf.pMem;
	string s;
	
	istr >> s;
	bf.BitLen = s.size();
	bf.pMem = new TELEM[s.size()];
	for (int i = 0; i < s.size(); i++)
	{
		bf.pMem[i] = 0;
	}
	
	stringstream is;
	for (int i = 0; i <s.size(); i++)
	{
		int check;
		is.clear();
		is << s[i];
		is >> check;
		if (check == 1)
			bf.SetBit(s.size()-i-1);
			
		
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = (bf.BitLen)-1; i >= 0; i--)
		ostr << bf.GetBit(i);
	return ostr;
}
