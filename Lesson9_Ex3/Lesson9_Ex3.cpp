#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class Employee {
protected:
    std::string name;

public:
    Employee(const std::string& name) : name(name) {}

    virtual void performTask(char task) {
        std::cout << name << " выполняет задачу типа " << task << "\n";
    }

    virtual ~Employee() {}
};

class Worker : public Employee {
public:
    Worker(const std::string& name) : Employee(name) {}

    void performTask(char task) override {
        std::cout << "Рабочий " << name << " выполняет задачу " << task << "\n";
    }
};

class Manager : public Employee {
private:
    std::vector<Worker> workers;

public:
    Manager(const std::string& name, const std::vector<std::string>& workerNames) : Employee(name) {
        for (const auto& workerName : workerNames) {
            workers.emplace_back(workerName);
        }
    }

    void assignTasks(int seed) {
        std::srand(seed);
        int tasksCount = rand() % (workers.size() + 1);
        const char taskTypes[] = { 'A', 'B', 'C' };

        std::cout << "Менеджер " << name << " раздаёт " << tasksCount << " задач.\n";
        for (int i = 0; i < tasksCount; ++i) {
            int workerIndex = i % workers.size();
            char task = taskTypes[rand() % 3];
            workers[workerIndex].performTask(task);
        }
    }
};

class CEO : public Employee {
private:
    std::vector<Manager> managers;

public:
    CEO(const std::string& name, const std::vector<std::pair<std::string, std::vector<std::string>>>& teams)
        : Employee(name) {
        for (const auto& team : teams) {
            managers.emplace_back(team.first, team.second);
        }
    }

    void giveOrder(int command) {
        std::cout << "Глава компании " << name << " отдаёт команду с идентификатором " << command << "\n";
        for (int i = 0; i < managers.size(); ++i) {
            managers[i].assignTasks(command + i);
        }
    }
};

int main() {
    setlocale(LC_CTYPE, "rus");
    std::srand(std::time(0));

    int numTeams, numWorkersPerTeam;
    std::cout << "Введите количество команд: ";
    std::cin >> numTeams;
    std::cout << "Введите количество работников в каждой команде: ";
    std::cin >> numWorkersPerTeam;

    std::vector<std::pair<std::string, std::vector<std::string>>> teams;
    for (int i = 0; i < numTeams; ++i) {
        std::vector<std::string> workers;
        for (int j = 0; j < numWorkersPerTeam; ++j) {
            workers.push_back("Рабочий_" + std::to_string(i) + "_" + std::to_string(j));
        }
        teams.emplace_back("Менеджер_" + std::to_string(i), workers);
    }

    CEO ceo("Глава_Компании", teams);

    int command;
    while (true) {
        std::cout << "Введите команду от главы компании (целое число, или -1 для выхода): ";
        std::cin >> command;
        if (command == -1) {
            break;
        }
        ceo.giveOrder(command);
    }

    return 0;
}
