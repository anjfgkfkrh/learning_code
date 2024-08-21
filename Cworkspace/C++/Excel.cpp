#include "utils.h"
#include <iostream>
#include <string>
#include <fstream>

using std::string;

namespace MyExcel {
  class Table;
  class Cell {
  protected:
    int x, y;
    Table* table;

    string data;

  public:
    virtual string stringify();
    virtual int to_numeric();

    Cell(string data, int x, int y, Table* table);
  };

  Cell::Cell(string data, int x, int y, Table* table) : data(data), x(x), y(y), table(table) {}

  string Cell::stringify() { return data; }
  int Cell::to_numeric() { return 0; }

  ////////////////////////////////////////////
  // Cell
  ////////////////////////////////////////////
  // Table
  ////////////////////////////////////////////

  class Table {
  protected:
    int max_row_size, max_col_size;

    Cell*** data_table;

  public:
    Table(int max_row_size, int max_col_size);

    ~Table();

    // 새로운 셀을 row 행 col 열에 등록
    void reg_cell(Cell* c, int row, int col);

    // 해당 셀의 정수값을 반환
    // s : 셀 이름 (ex. A3, B6 과 같이)
    int to_numeric(const string& s);

    // 행 및 열 번호로 셀을 호출
    int to_numeric(int row, int col);

    // 해당 셀의 문자열을 반환
    string stringify(const string& s);
    string stringify(int row, int col);

    virtual string print_table() = 0;
  };

  Table::Table(int max_row_size, int max_col_size) : max_row_size(max_row_size), max_col_size(max_col_size) {
    data_table = new Cell * *[max_row_size];
    for (int i = 0; i < max_row_size; i++) {
      data_table[i] = new Cell * [max_col_size];
      for (int j = 0; j < max_col_size; j++)
        data_table[i][j] = nullptr;
    }
  }

  Table::~Table() {
    for (int i = 0; i < max_row_size; i++) {
      for (int j = 0; j < max_col_size; j++)
        if (data_table[i][j])
          delete data_table[i][j];
      delete[] data_table[i];
    }
    delete[] data_table;
  }

  void Table::reg_cell(Cell* c, int row, int col) {
    if (row >= max_row_size || row < 0 || col >= max_col_size || col < 0)
      return;

    if (data_table[row][col])
      delete data_table[row][col];

    data_table[row][col] = c;
  }

  int Table::to_numeric(const string& s) {
    int row = s[0] - 'A';
    int col = atoi(s.c_str() + 1) - 1;

    if (row >= max_row_size || row < 0 || col >= max_col_size || col < 0)
      return 0;
    if (!data_table[row][col])
      return 0;
    return data_table[row][col]->to_numeric();
  }

  int Table::to_numeric(int row, int col) {
    if (row >= max_row_size || row < 0 || col >= max_col_size || col < 0)
      return 0;
    if (!data_table[row][col])
      return 0;
    return data_table[row][col]->to_numeric();
  }

  string Table::stringify(const string& s) {
    int row = s[0] - 'A';
    int col = atoi(s.c_str() + 1) - 1;

    if (row >= max_row_size || row < 0 || col >= max_col_size || col < 0)
      return "";
    if (!data_table[row][col])
      return "";
    return data_table[row][col]->stringify();
  }

  string Table::stringify(int row, int col) {
    if (row >= max_row_size || row < 0 || col >= max_col_size || col < 0)
      return "";
    if (!data_table[row][col])
      return "";
    return data_table[row][col]->stringify();
  }

  std::ostream& operator<<(std::ostream& os, Table& table) {
    os << table.print_table();
    return os;
  }

  ////////////////////////////////////////////
  // Table
  ////////////////////////////////////////////
  // TxTTable
  ////////////////////////////////////////////

  class TxTTable : public Table {
    string repeat_char(int n, char c);

    // 숫자로 된 열 번호를 A, B, .... Z, AA, AB, ...  이런 순으로 매겨줌
    string col_num_to_str(int n);

  public:
    TxTTable(int row, int col);

    // 텍스트로 표를 깨끗하게 출력
    string print_table();
  };

  TxTTable::TxTTable(int row, int col) : Table(row, col) {}

  // 텍스트를 표로 깨끗하게 출력
  string TxTTable::print_table()
  {
    string total_table;

    int* col_max_wide = new int[max_col_size];
    std::fill_n(col_max_wide, max_col_size, 2);

    for (int i = 0; i < max_row_size; i++)
      for (int j = 0; j < max_col_size; j++)
        if (data_table[i][j])
          col_max_wide[j] = std::max(col_max_wide[j], (int)data_table[i][j]->stringify().length());

    // 맨 상단에 열 정보 표시
    total_table += "    ";
    int total_wide = 4;
    for (int i = 0; i < max_col_size; i++) {
      if (col_max_wide[i]) {
        total_table += " | " + col_num_to_str(i);
        total_table += repeat_char(col_max_wide[i] - col_num_to_str(i).length(), ' ');
        total_wide += (col_max_wide[i] + 3);
      }
    }

    total_table += "\n";
    // 일단 기본적으로 최대 9999 번째 행 까지 지원한다고 생각한다.
    for (int i = 0; i < max_row_size; i++) {
      total_table += repeat_char(total_wide, '-');
      total_table += "\n" + std::to_string(i + 1);
      total_table += repeat_char(4 - std::to_string(i + 1).length(), ' ');

      for (int j = 0; j < max_col_size; j++) {
        if (col_max_wide[j]) {
          string s = "";
          if (data_table[i][j])
            s = data_table[i][j]->stringify();

          total_table += " | " + s;
          total_table += repeat_char(col_max_wide[j] - s.length(), ' ');
        }
      }
      total_table += "\n";
    }

    return total_table;
  }

  string TxTTable::repeat_char(int n, char c) {
    string s = "";
    for (int i = 0; i < n; i++)
      s += c;

    return s;
  }

  string TxTTable::col_num_to_str(int n) {
    string s = "";
    if (n < 26)
      s += ('A' + n);
    else {
      s += ('A' + (int)(n / 26) - 1);
      s += ('A' + (n % 26));
    }

    return s;
  }

  ////////////////////////////////////////////
  // TxTTable
  ////////////////////////////////////////////
  // HtmlTable
  ////////////////////////////////////////////

  class HtmlTable : public Table {
  public:
    HtmlTable(int row, int col);
    string print_table();
  };

  HtmlTable::HtmlTable(int row, int col) : Table(row, col) {};

  string HtmlTable::print_table() {
    string s = "<table border='1' cellpadding='10'>";
    for (int i = 0; i < max_row_size; i++) {
      s += "<tr>";
      for (int j = 0; j < max_col_size; j++) {
        s += "<td>";
        if (data_table[i][j])
          s += data_table[i][j]->stringify();
        s += "</td>";
      }
      s += "</tr>";
    }
    s += "</table>";
    return s;
  }

  ////////////////////////////////////////////
  // HtmlTable
  ////////////////////////////////////////////
  // CSVTable
  ////////////////////////////////////////////

  class CSVTable : public Table {
  public:
    CSVTable(int row, int col);
    string print_table();
  };

  CSVTable::CSVTable(int row, int col) : Table(row, col) {};

  string CSVTable::print_table() {
    string s = "";
    for (int i = 0; i < max_row_size; i++) {
      for (int j = 0; j < max_col_size; j++) {
        if (j >= 1) s += ",";
        // CSV 파일 규칙에 따라 문자열에 큰따옴표가 포함되어 있다면 ""로 치환한다.
        string temp;
        if (data_table[i][j]) temp = data_table[i][j]->stringify();

        for (int k = 0; k < temp.length(); k++) {
          if (temp[k] == '"') {
            // k의 위치에 "를 한 개 더 집어넣는다.
            temp.insert(k, 1, '"');

            // 이미 추가된 "를 다시 확인하는 일이 없게 하기 위해
            // k를 한 칸 더 이동한다.
            k++;
          }
        }
        temp = '"' + temp + '"';
        s += temp;
      }
      s += '\n';
    }
    return s;
  }

};

// 생략
int main() {
  MyExcel::CSVTable table(5, 5);
  std::ofstream out("test.csv");

  table.reg_cell(new MyExcel::Cell("Hello~", 0, 0, &table), 0, 0);
  table.reg_cell(new MyExcel::Cell("C++", 0, 1, &table), 0, 1);

  table.reg_cell(new MyExcel::Cell("Programming", 1, 1, &table), 1, 1);
  std::cout << std::endl
    << table;
  out << table;
}