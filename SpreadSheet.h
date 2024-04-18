#ifndef __SPREADSHEET__H__
#define __SPREADSHEET__H__

#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <iomanip>

#include "Cell.h"

class SpreadSheet
{
private:
    Cell** board;
    size_t rowcnt;
    size_t colcnt;
private:
    class Column;
public:

    SpreadSheet();
    SpreadSheet(const SpreadSheet& rhv);
    SpreadSheet(SpreadSheet&& rhv);
    SpreadSheet(size_t size);
    SpreadSheet(size_t row, size_t col);
    ~SpreadSheet();

    const SpreadSheet& operator=(const SpreadSheet& rhv);
    const SpreadSheet& operator=(SpreadSheet&& rhv);

    Column operator[](size_t pos);
    const Column operator[](size_t pos) const;

    void clear() noexcept;

    size_t row() const;
    size_t col() const;
    
    void mirrorH();
    void mirrorV();
    void mirrorD();
    void mirrorSD();

    void rotate(int cnt);

    void removeRow(size_t row);
    void removeRows(std::initializer_list<size_t> rows);
    void removeCol(size_t col);
    void removeCols(std::initializer_list<size_t> cols);

    void resizeRow(size_t r);
    void resizeCol(size_t c);
    void resize(size_t r, size_t c);


    SpreadSheet slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols);        
};


class SpreadSheet::Column {
    private:
        Cell* col;
    public:
        explicit Column(Cell* col)
        {
            this->col = col;
        }
    public:
        Column() = delete;
        Column(const Column&) = delete;
        Column(Column&&) = delete;

        const Column& operator=(const Column&) = delete;
        const Column& operator=(Column&&) = delete;
    public:
        Cell& operator[](size_t pos);
        const Cell& operator[](size_t pos) const;
};

bool operator==(const SpreadSheet& lhv, const SpreadSheet& rhv);
bool operator!=(const SpreadSheet& lhv, const SpreadSheet& rhv);

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob); // beauty output using iomanip library



#endif //__SPREADSHEET__H__
