#include "utils.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using std::string;

namespace MyExcel {
  class Table;
  class Cell {
  protected:
    int x, y;
    Table* table;

    //string data;

  public:
    virtual string stringify() = 0;
    virtual int to_numeric() = 0;

    Cell(int x, int y, Table* table);
    virtual ~Cell() {};
  };

  class StringCell : public Cell {
    string data;

  public:
    string stringify();
    int to_numeric();

    StringCell(string data, int x, int y, Table* t);
  };

  class NumberCell : public Cell {
    int data;

  public:
    string stringify();
    int to_numeric();

    NumberCell(int data, int x, int y, Table* t);
  };

  class DateCell : public Cell {
    time_t data;

  public:
    string stringify();
    int to_numeric();

    DateCell(string s, int x, int y, Table* t);
  };

  class ExprCell : public Cell {
    string data;
    string* parsed_expr;

    Vector<string> exp_vec;

    // 연산자 우선 순위를 반환한다.
    int precedence(char c);

    // 수식을 분석한다.
    void parse_expresstion();

  public:
    ExprCell(string data, int x, int y, Table* t);

    string stringify();
    int to_numeric();
  };

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

  class TxTTable : public Table {
    string repeat_char(int n, char c);

    // 숫자로 된 열 번호를 A, B, .... Z, AA, AB, ...  이런 순으로 매겨줌
    string col_num_to_str(int n);

  public:
    TxTTable(int row, int col);

    // 텍스트로 표를 깨끗하게 출력
    string print_table();
  };

  class HtmlTable : public Table {
  public:
    HtmlTable(int row, int col);
    string print_table();
  };
  class CSVTable : public Table {
  public:
    CSVTable(int row, int col);
    string print_table();
  };

  ////////////////////////////////////////////
  // 선언
  ////////////////////////////////////////////
  // 구현
  ////////////////////////////////////////////

  Cell::Cell(int x, int y, Table* table) : x(x), y(y), table(table) {}

  StringCell::StringCell(string data, int x, int y, Table* t) : Cell(x, y, t), data(data) {}

  string StringCell::stringify() { return data; }
  int StringCell::to_numeric() { return 0; }

  NumberCell::NumberCell(int data, int x, int y, Table* t) : Cell(x, y, t), data(data) {}

  string NumberCell::stringify() { return std::to_string(data); }
  int NumberCell::to_numeric() { return data; }

  DateCell::DateCell(string s, int x, int y, Table* t) :Cell(x, y, t) {
    int year = atoi(s.c_str());
    int month = atoi(s.c_str() + 5);
    int day = atoi(s.c_str() + 8);

    tm timeinfo;
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;

    data = mktime(&timeinfo);
  }

  string DateCell::stringify() {
    char buf[50];
    tm temp;
    localtime_r(&data, &temp);

    strftime(buf, 50, "%F", &temp);

    return string(buf);
  }

  int DateCell::to_numeric() { return static_cast<int>(data); }

  ExprCell::ExprCell(string data, int x, int y, Table* t) : Cell(x, y, t), data(data) {}

  string ExprCell::stringify() { return data; }

  int ExprCell::to_numeric() {
    double result = 0;
    NumStack stack;

    for (int i = 0; i < exp_vec.size(); i++) {
      string s = exp_vec[i];

      //셀 일 경우
      if (isalpha(s[0])) {
        stack.push(table->to_numeric(s));
      }
      // 숫자 일 경우 (한 자리라 가정)
      else if (isdigit(s[0])) {
        stack.push(atoi(s.c_str()));
      }
      else {
        double y = stack.pop();
        double x = stack.pop();
        switch (s[0]) {
        case '+':
          stack.push(x + y);
          break;
        case '-':
          stack.push(x - y);
          break;
        case '*':
          stack.push(x * y);
          break;
        case '/':
          stack.push(x / y);
          break;
        }
      }
    }
    return stack.pop();
  }

  int ExprCell::precedence(char c) {
    switch (c) {
    case '(':
    case '[':
    case '{':
      return 0;
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    }

    return 0;
  }

  void ExprCell::parse_expresstion() {
    Stack stack;

    //수식 전체를 () 로 둘러 싸서 exp_vec에 남아있는 연산자들이 push 되게 해줌
    data.insert(0, "(");
    data.push_back(')');

    for (int i = 0; i < data.length(); i++) {
      if (isalpha(data[i])) {
        exp_vec.push_back(data.substr(i, 2));
        i++;
      }
      else if (isdigit(data[i])) {
        exp_vec.push_back(data.substr(i, 1));
      }
      else if (data[i] == '(' || data[i] == '[' || data[i] == '{') {
        stack.push(data.substr(i, 1));
      }
      else if (data[i] == ')' || data[i] == ']' || data[i] == '}') {
        string t = stack.pop();
        while (t != "(" && t != "[" && t != "{") {
          exp_vec.push_back(t);
          t = stack.pop();
        }
      }
      else if (data[i] == '+' || data[i] == '-' || data[i] == '*' || data[i] == '/') {
        while (!stack.is_empty() && precedence(stack.peek()[0]) >= precedence(data[i])) {
          exp_vec.push_back(stack.pop());
        }
        stack.push(data.substr(i, 1));
      }
    }
  }

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

  // 인터페이스 클래스
  class Excel {
    Table* current_table;

  public:
    Excel(int max_row, int max_col, int choice = 0);

    int parse_user_input(string s);
    void command_line();
  };

  Excel::Excel(int max_row, int max_col, int choice) {
    switch (choice) {
    case 0:
      current_table = new TxTTable(max_row, max_col);
      break;
    case 1:
      current_table = new CSVTable(max_row, max_col);
      break;
    default:
      current_table = new HtmlTable(max_row, max_col);
    }
  }

  int Excel::parse_user_input(string s) {
    int next = 0;
    string command = "";
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == ' ') {
        command = s.substr(0, i);
        next = i + 1;
        break;
      }
      else if (i == s.length() - 1) {
        command = s.substr(0, i + 1);
        next = i + 1;
        break;
      }
    }

    string to = "";
    for (int i = next; i < s.length(); i++) {
      if (s[i] == ' ' || i == s.length() - 1) {
        to = s.substr(next, i - next);
        next = i + 1;
        break;
      }
      else if (i == s.length() - 1) {
        to = s.substr(0, i + 1);
        next = i + 1;
        break;
      }
    }

    // Cell 이름으로 받는다.
    int col = to[0] - 'A';
    int row = atoi(to.c_str() + 1) - 1;

    string rest = s.substr(next);

    if (command == "sets") {
      current_table->reg_cell(new StringCell(rest, row, col, current_table), row, col);
    }
    else if (command == "setn") {
      current_table->reg_cell(new NumberCell(atoi(rest.c_str()), row, col, current_table), row, col);
    }
    else if (command == "setd") {
      current_table->reg_cell(new DateCell(rest, row, col, current_table), row, col);
    }
    else if (command == "sete") {
      current_table->reg_cell(new ExprCell(rest, row, col, current_table), row, col);
    }
    else if (command == "out") {
      std::ofstream out(to);
      out << *current_table;
      std::cout << to << " 에 내용이 저장되었습니다" << std::endl;
    }
    else if (command == "exit") {
      return 0;
    }

    return 1;
  }

  void Excel::command_line() {
    string s;
    std::getline(std::cin, s);

    while (parse_user_input(s)) {
      std::cout << *current_table << std::endl << ">> ";
      std::getline(std::cin, s);
    }
  }

};


// 생략
int main() {
  std::cout
    << "테이블 (타입) (최대 행 크기) (최대 열 크기) 를 순서대로 입력해주세요"
    << std::endl;
  std::cout << "* 참고 * " << std::endl;
  std::cout << "1 : 텍스트 테이블, 2 : CSV 테이블, 3 : HTML 테이블"
    << std::endl;

  int type, max_row, max_col;
  std::cin >> type >> max_row >> max_col;
  MyExcel::Excel m(max_row, max_col, type - 1);
  m.command_line();
}