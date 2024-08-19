#include <iostream>
#include <string>

class Table;
class Cell
{
   Table *table; // 어느 테이블에 속해있는지
   std::string data;
   int x, y; // 테이블 에서의 위치
public:
   Cell(const std::string &data) : data(data) {};
};

class Table
{
   Cell ***data_base; // 왜 3중 포인터 인지 잘 생각해보세요!
   int max_row;
   int max_col;

public:
   Table();
   Table(int max_row, int max_col);
   virtual std::string print_table() = 0;
   void reg_cell(Cell *c, int row, int col); // Cell 을 등록한다
   std::string get_cell(int row, int col);   // 해당 위치의 Cell 데이터를 얻는다.
   ~Table();
};

Table::Table(int row, int col)
{
   max_row = row;
   max_col = col;

   data_base = new Cell **[max_row];

   for (int i = 0; row; i++)
   {
      data_base[i] = new Cell *[max_col];

      for (int j = 0; j < max_col; j++)
         data_base[i][j] = nullptr;
   }
}

Table::~Table()
{
   for (int i = 0; i < max_row; i++)
   {
      for (int j = 0; j < max_col; j++)
         delete data_base[i][j];
      delete[] data_base[i];
   }

   delete[] data_base;
}

void Table::reg_cell(Cell *c, int row, int col)
{
   data_base[row][col] = c;
}

std::ostream &operator<<(std::ostream &o, Table &t)
{
   o << t.print_table();
   return o;
}

class TextTable : public Table
{
public:
   TextTable() {}
};
class CSVTable : public Table
{
};
class HTMLTable : public Table
{
};