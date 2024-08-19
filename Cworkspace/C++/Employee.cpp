#include <iostream>

class Employee
{
protected:
   std::string name;
   int age;

   std::string position;
   int rank;

public:
   Employee(std::string name, int age, std::string position, int rank) : name(name), age(age), position(position), rank(rank) {}

   Employee(const Employee &emp) : name(emp.name), age(emp.age), position(emp.position), rank(emp.rank) {}

   Employee() {}

   virtual void print_info()
   {
      std::cout << name << " (" << position << ", " << age << ") ==> " << calculate_pay() << "만원" << std::endl;
   }

   virtual int calculate_pay() { return 200 + rank * 50; }

   virtual ~Employee() {};
};

class Manager : public Employee
{
   int year_of_service;

public:
   Manager(std::string name, int age, std::string position, int rank, int year_of_service) : Employee(name, age, position, rank), year_of_service(year_of_service) {}

   Manager(const Manager &manager) : Employee(manager), year_of_service(manager.year_of_service) {}

   Manager() : Employee() {}

   int calculate_pay() override { return 200 + rank * 50 + 5 * year_of_service; }

   void print_info() override
   {
      std::cout << name << " (" << position << ", " << age << ", "
                << year_of_service << "년차) ==> " << calculate_pay() << "만원"
                << std::endl;
   }
};

class EmployeeList
{
   int alloc_employee;

   int current_employee;
   // int current_manager;

   Employee **employee_list;
   // Manager **manager_list;

public:
   EmployeeList(int alloc_employee) : alloc_employee(alloc_employee)
   {
      employee_list = new Employee *[alloc_employee];
      // manager_list = new Manager *[alloc_employee];
      current_employee = 0;
      // current_manager = 0;
   }

   void add_employee(Employee *employee)
   {
      // 사실 current_employee 보다 alloc_employee 가 더
      // 많아지는 경우 반드시 재할당을 해야 하지만, 여기서는
      // 최대한 단순하게 생각해서 alloc_employee 는
      // 언제나 current_employee 보다 크다고 생각한다.
      // (즉 할당된 크기는 현재 총 직원수 보다 많음)
      employee_list[current_employee++] = employee;
   }
   // void add_manager(Manager *manager)
   // {
   //    manager_list[current_manager++] = manager;
   // }

   int current_employee_num() { return current_employee; }

   void print_employee_info()
   {
      int total_pay = 0;
      for (int i = 0; i < current_employee; i++)
      {
         employee_list[i]->print_info();
         total_pay += employee_list[i]->calculate_pay();
      }
      // for (int i = 0; i < current_manager; i++)
      // {
      //    manager_list[i]->print_info();
      //    total_pay += manager_list[i]->calculate_pay();
      // }

      std::cout << "총 비용 : " << total_pay << "만원" << std::endl;
   }

   ~EmployeeList()
   {
      for (int i = 0; i < current_employee; i++)
         delete employee_list[i];

      // for (int i = 0; i < current_employee; i++)
      //    delete manager_list[i];

      delete[] employee_list;
      // delete[] manager_list;
   }
};

int main()
{
   EmployeeList emp_list(10);
   emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
   emp_list.add_employee(new Employee("하하", 34, "평사원", 1));

   emp_list.add_employee(new Manager("유재석", 41, "부장", 7, 12));
   emp_list.add_employee(new Manager("정준하", 43, "과장", 4, 15));
   emp_list.add_employee(new Manager("박명수", 43, "차장", 5, 13));
   emp_list.add_employee(new Employee("정형돈", 36, "대리", 2));
   emp_list.add_employee(new Employee("길", 36, "인턴", -2));
   emp_list.print_employee_info();
   return 0;
}