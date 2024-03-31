
#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

/*Реализуйте симуляцию состязаний по заплыву на n метров.
Всего шесть дорожек и шесть пловцов. Имена пловцов указываются в начале из стандартного ввода.
Каждый из них плывёт с разной скоростью, которая также задаётся пользователем при старте, через стандартный ввод в метрах в секунду.
Каждую секунду в стандартный вывод выдаётся информация о том, сколько проплыл тот или иной пловец.
Как только все пловцы коснулись 100-метровой отметки, заплыв заканчивается и выводится таблица с итоговыми результатами, отсортированная по возрастанию итогового времени заплыва.

Советы и рекомендации
Используйте нити для реализации движения каждого пловца в отдельности.*/

using namespace std;

struct Swimmer
{
    double speed;
    double distance;
    std::string name;

    Swimmer(double spd, double dist, std::string nm) : speed(spd), distance(dist), name(nm) {}
};

std::vector<Swimmer> swimmers;
std::mutex mtx;
int swimLength;

void swimmer(double speed, std::string name)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        {
            std::lock_guard<std::mutex> lock(mtx);
            for (auto& s : swimmers)
            {
                s.distance += s.speed;
                std::cout << s.name << " проплыл " << s.distance << " метров." << std::endl;
            }
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            if (std::all_of(swimmers.begin(), swimmers.end(), [](const Swimmer& s) { return s.distance >= swimLength; }))
                break;
        }
    }
}

void showDistance()
{
    std::thread t(swimmer, 0.0, "");
    t.join();
}

void swimming(int countSwimmer)
{
    for (int i = 1; i <= countSwimmer; ++i)
    {
        cout << "Введите имя пловца #" << i << ": ";
        string name;
        cin >> name;

        cout << "Введите скорость для пловца #" << i << " (м/сек): ";
        double speed;
        cin >> speed;

        swimmers.emplace_back(speed, 0.0, name);
    }

    showDistance();
}

void task1()
{
    swimLength = 100;
    swimming(6);

    sort(swimmers.begin(), swimmers.end(), [](const Swimmer& a, const Swimmer& b) { return a.distance / a.speed < b.distance / b.speed; });

    cout << "Итоги:" << endl;
    for (size_t i = 0; i < swimmers.size(); ++i)
    {
        cout << swimmers[i].name << " закончил за " << (swimLength / swimmers[i].speed) << " секунд." << endl; //swimmers[i].distance 
    }
}