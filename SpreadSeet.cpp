#include "SpreadSheet.h"
#include "Cell.h"
#include <utility>


Cell& SpreadSheet::Column::operator[](size_t pos)
{
    return col[pos];
}

const Cell& SpreadSheet::Column::operator[](size_t pos) const
{
    return col[pos];
}



SpreadSheet::SpreadSheet()
{
    board = nullptr;
    rowcnt = 0;
    colcnt = 0;
}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv) : SpreadSheet(rhv.rowcnt, rhv.colcnt)
{
    for(int i = 0; i < rowcnt; ++i)
    {
        for(int j = 0; j < colcnt; ++j)
        {

            board[i][j] = rhv.board[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv)
{
    board = rhv.board;
    rowcnt = rhv.rowcnt;
    colcnt = rhv.colcnt;

    rhv.board = nullptr;
    rhv.rowcnt = 0;
    rhv.colcnt = 0;
}

SpreadSheet::SpreadSheet(size_t size)
{
    board = new Cell*[size];
    for(int i = 0; i < size; ++i)                                                               
    {
        board[i] = new Cell[size];
    }
    rowcnt = size;
    colcnt = size;
}

SpreadSheet::SpreadSheet(size_t row, size_t col)
{
    board = new Cell*[row];
    for(int i = 0; i < row; ++i)
    {
        board[i] = new Cell[col];
    }
    rowcnt = row;
    colcnt = col;
}

SpreadSheet::~SpreadSheet()
{
    clear();
}

const SpreadSheet& SpreadSheet::operator=(const SpreadSheet& rhv)
{
    if(this != &rhv)
    {
        resize(rhv.rowcnt, rhv.colcnt);
        for(int i = 0; i < rowcnt; ++i)
        {
            for(int j = 0; j < colcnt; ++j)
            {
                board[i][j] = rhv.board[i][j];
            }
        }
    }
    return *this;
}

const SpreadSheet& SpreadSheet::operator=(SpreadSheet&& rhv)
{
    if (this != &rhv)
    {
        if (board != nullptr)
        {
            for(int i = 0; i < rowcnt; ++i)
            {
                delete[] board[i];
            }
            delete[] board;
        }

        board = rhv.board;
        rowcnt = rhv.rowcnt;
        colcnt = rhv.colcnt;

        rhv.board = nullptr;
        rhv.rowcnt = 0;
        rhv.colcnt = 0;
    }
    return *this;
}


SpreadSheet::Column SpreadSheet::operator[](size_t pos)
{
    return Column(board[pos]);
}

const SpreadSheet::Column SpreadSheet::operator[](size_t pos) const
{
    return Column(board[pos]);
}


void SpreadSheet::clear() noexcept
{
    if(board != nullptr)
    {
        for(int i = 0; i < rowcnt; ++i)
        {
            delete[] board[i];
        }
        delete[] board;
    }
}


size_t SpreadSheet::row() const
{
    return rowcnt;
}

size_t SpreadSheet::col() const
{
    return colcnt;
}


void SpreadSheet::mirrorH()
{
    for(int i = 0; i < rowcnt / 2; ++i)
    {
        std::swap(board[i],board[rowcnt - 1 - i]);
    }
}

void SpreadSheet::mirrorV()
{
    for(int i = 0; i < rowcnt; ++i)
    {
        for(int j = 0; j < colcnt / 2; ++j)
        {
            std::swap(board[i][j],board[i][colcnt - 1 - j]);
        }
    }
}

void SpreadSheet::mirrorSD()
{
    if(rowcnt == colcnt)
    {
        for(int i = 0; i < rowcnt; ++i)
        {
            for(int j = 0; j < rowcnt - i; ++j)
            {
                std::swap(board[i][j], board[rowcnt - 1 - j][rowcnt - 1 - i]);
            }
        }
    }
}

void SpreadSheet::mirrorD()
{
    if(rowcnt == colcnt)
    {
        for(int i = 0; i < rowcnt; ++i)
        {
            for(int j = 0; j < i; ++j)
            {
                std::swap(board[i][j], board[j][i]);
            }
        }
    }
}


void SpreadSheet::rotate(int cnt)
{
    if(cnt % 4 == 0)
    {
        return;
    }
    
    SpreadSheet tmp(colcnt, rowcnt);
    

    if(cnt % 2 == 1)
    {
        for (int i = 0; i < colcnt; ++i) 
        {
            for (int j = 0; j < rowcnt; ++j) 
            {
                tmp[j][colcnt - 1 - i] = board[i][j];
            }
        }
        --cnt;
        std::swap(rowcnt, colcnt);
        std::swap(this->board, tmp.board);
    }
    else if(cnt % 2 == -1)
    {
        for (int i = 0; i < colcnt; ++i) 
        {
            for (int j = 0; j < rowcnt; ++j) 
            {
                tmp[rowcnt - 1 - j][i] = board[i][j];
            }
        }
        ++cnt;
        std::swap(rowcnt, colcnt);
        std::swap(this->board, tmp.board);
    }

    cnt /= 2;
    if (cnt > 0) 
    {
        while(cnt != 0)
        {
            mirrorH();
            mirrorV();
            --cnt;
        }
    }
    else 
    {
        while(cnt != 0)
        {
            mirrorV();
            mirrorH();
            ++cnt;
        }
        
    }
}


void SpreadSheet::removeRow(size_t row)
{
    if(row < rowcnt)
    {
        Cell** tmp = new Cell*[rowcnt - 1];
        for(int i = 0; i < rowcnt - 1; ++i)
        {
            tmp[i] = new Cell[colcnt];
        }
        for(int i = 0; i < row; ++i)
        {
            for(int j = 0; j < colcnt; ++j)
            {
                tmp[i][j] = board[i][j];
            }
        }
        for(int i = row + 1; i < rowcnt; ++i)
        {
            for(int j = 0; j < colcnt; ++j)                                                             
            {
                tmp[i - 1][j] = board[i][j];
            }
        }
        for(int i = 0; i < rowcnt; ++i)
        {
            delete[] board[i];
        }
        delete[] board;

        board = tmp;
        --rowcnt;
    }
    else
    {
        throw std::invalid_argument("No such row");
    }
}

void SpreadSheet::removeRows(std::initializer_list<size_t> rows)
{
    for (size_t i : rows)
    {
        removeRow(i);
    }
}

void SpreadSheet::removeCol(size_t col)
{
    if (col < colcnt)
    {
        Cell** tmp = new Cell*[rowcnt];
        for(int i = 0; i < rowcnt; ++i)
        {
            tmp[i] = new Cell[colcnt - 1];
        }
        for(int i = 0; i < rowcnt; ++i)
        {
            for(int j = 0; j < col; ++j)
            {
                tmp[i][j] = board[i][j];
            }
            for(int j = col + 1; j < colcnt; ++j)
            {
                tmp[i][j - 1] = board[i][j];
            }
        }
        for(int i = 0; i < rowcnt; ++i)
        {
            delete[] board[i];
        }
        delete[] board;

        board = tmp;
        --colcnt;
    }
    else
    {
        throw std::invalid_argument("No such col");
    }
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols)
{
    for (size_t i : cols)
    {
        removeCol(i);
    }
}


void SpreadSheet::resizeRow(size_t r)
{
    resize(r, colcnt);
}

void SpreadSheet::resizeCol(size_t c)
{
    resize(rowcnt, c);
}

void SpreadSheet::resize(size_t r, size_t c)
{
    if(r != rowcnt || c != colcnt)
    {
        Cell** tmp = new Cell*[r];
        for(int i = 0; i < r; ++i)
        {
            tmp[i] = new Cell[c];
        }
        if (board != nullptr)
        {
            int min_row = (r < rowcnt) ? r : rowcnt;
            int min_col = (c < colcnt) ? c : colcnt;
            for(int i = 0; i < min_row;  ++i)
            {
                for(int j = 0; j < min_col; ++j)
                {
                    tmp[i][j] = board[i][j];
                }
            }
            for(int i = 0; i < rowcnt; ++i)
            {
                delete[] board[i];
            }
            delete[] board;
        }
        board = tmp;
        rowcnt = r;
        colcnt = c;
        tmp = nullptr;
    }
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols)
{
    SpreadSheet tmp(rows.size(), cols.size());
    
    auto k = rows.begin();
    for (auto i = 0; i < rows.size(); ++i)
    {
        auto t = cols.begin();
        for(int j = 0; j < cols.size(); ++j)
        {
            tmp[i][j] = board[*k][*t];
        }
        ++k;
        ++t;
    }
    return tmp;
}

bool operator==(const SpreadSheet& lhv, const SpreadSheet& rhv)
{
    if (&lhv == &rhv)
    {
        return true;
    }
    if (lhv.row() == rhv.row() && lhv.col() == rhv.col())
    {
        for(int i = 0; i < lhv.row(); ++i)
        {
            for(int j = 0; j < lhv.col(); ++j)
            {
                if (lhv[i][j] != rhv[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool operator!=(const SpreadSheet& lhv, const SpreadSheet& rhv)
{
    return !(lhv == rhv);
}

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob)
{
    for (int i = 0; i < ob.row(); ++i) 
    {
        for (int j = 0; j < ob.col(); ++j) 
        {
        out << std::setw(5) << ob[i][j];
        }
        out << '\n';
    }
    return out;
}
