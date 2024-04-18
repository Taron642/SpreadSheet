#include "Cell.h"

std::ostream& operator<<(std::ostream& out, const std::vector<int>& ob)
{
	for(auto i : ob)
    {
        out << i;
    }
    return out;
}

Cell::Cell()
{
	value = "-";
}

Cell::Cell(const Cell& rhv)
{
	value = rhv.value;
}

Cell::Cell(Cell&& rhv)
{
	value = rhv.value;
	rhv.value = "";
}

Cell::Cell(int val)
{
	value = std::to_string(val);
}

Cell::Cell(double val)
{
	value = std::to_string(val);
}

Cell::Cell(char val)
{
    value = val;
}

Cell::Cell(bool val)
{
    value = std::to_string(val);
}

Cell::Cell(std::string val)
{
	value = val;
}

Cell::Cell(const std::vector<int>& val)
{
    for(auto i : val)
    {
        value += " " + std::to_string(i);
    }
}

const Cell& Cell::operator=(const Cell& rhv)
{
	value = rhv.value;
	return *this;
}

const Cell& Cell::operator=(Cell&& rhv)
{
	value = rhv.value;
	rhv.value = "";
	return *this;
}

const Cell& Cell::operator=(int rhv)
{
	value = std::to_string(rhv);
	return *this;
}

const Cell& Cell::operator=(double rhv)
{
	value = std::to_string(rhv);
	return *this;
}

const Cell& Cell::operator=(char rhv)
{
    value = std::to_string(rhv);
    return *this;
}

const Cell& Cell::operator=(bool rhv)
{
	value = std::to_string(rhv);
    return *this;
}

const Cell& Cell::operator=(std::string rhv)
{
	value = rhv;
    return *this;
}

const Cell& Cell::operator=(const std::vector<int>& rhv)
{
    value = "";
    for(auto i : rhv)
    {
        value += " " + std::to_string(i);
    }
    return *this;
}

Cell::operator int()
{
	int i = std::stoi(value);
	return i;
}

Cell::operator double()
{
	double d = std::stod(value);
    return d;
}

Cell::operator char()
{
	char ch = value[0];
	return ch;
}

Cell::operator bool()
{
	int i = std::stoi(value);
	bool b = i;
	return b;
}

Cell::operator std::string()
{
    const std::string st = value;
	return st;
}

Cell::operator std::vector<int>() const
{
    std::vector<int> vec;
    std::string val = value;
    while(val.find(" ") != std::string::npos)
    {
        vec.push_back(std::stoi(val.substr(0, val.find(" "))));
        val = val.substr(val.find(" ") + 1, val.size());
    }
    vec.push_back(std::stoi(val));

    return vec;
}

bool operator==(const Cell& lhv, const Cell& rhv)
{
    std::string st1 = Cell(lhv);
    std::string st2 = Cell(rhv);
	return st1 == st2;
}

bool operator!=(const Cell& lhv, const Cell& rhv)
{
	return !(lhv == rhv);
}

std::ostream& operator<<(std::ostream& out, const Cell& ob)
{
    Cell tmp(ob);
	std::string st  = tmp;
    if(st.find('.') != std::string::npos)
    {
        while(st.back() == '0')
        {
            st.pop_back();
        }
        if(st.back() == '.')
        {
            st.pop_back();
        }
    }
	out << st;
	return out;
}

std::istream& operator>>(std::istream& in, Cell& ob)
{
	std::string st;
	in >> st;
	ob = st;
	return in;
}
