/*� ������� ��������������� ���������� ������� ������ ���������������� �������.
� ��� ����� ����������� � ������ ����� �������� ��� ������ ������ � ��������� ������������� A, B, C. ��� ��� ���� �� ���� � ��� �� ������ � ����� ����� �� ���� � ������ �����.
�� ���� ������� ������� ������������� ����� ���������� ������ ���� �����. ��������� ������ ������ �����, ���� ��� ������� ����� �����������.
� ������ ��������� ������������ ��������������� ������ ��� ������� ������ ����� � ���� �� ������� (� ��������). ����� ����� ������ �������� ��� �������� �� �������� ���������� �������. ��� ������ ����� ������ �� ������,
�� ������� �� ������������ ������� depart, ������� ������������� � ��� ������� � �������.
�� ���� �������� (�������� �� ������, �������� ���������� �����, ������� � �������) ������ � �������� ������������ ������ ��������� ��������� � �������.
��������� �����������, ����� �� ������� �������� ��� ��� ������.

������ � ������������
����������� ��� ������� ��������� ������� � ����������� �������� � ������� ����.*/


#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace std;

mutex mt;
bool stationOccupied = false;

static void trainArrival(string trainName, int travelTime)
{
    this_thread::sleep_for(chrono::seconds(travelTime));

    {
        std::lock_guard<std::mutex> lock(mt);
        std::cout << trainName << " ������ �� ������." << endl;
    }

    string command;
    cout << "�������� �������: ";
    cin >> command;

    {
        lock_guard<std::mutex> lock(mt);
        stationOccupied = false;
        cout << trainName << " ����� � �������." << endl;
    }
}

void task2()
{
    int arrivalTimeOfTrainA;
    int arrivalTimeOfTrainB;
    int arrivalTimeOfTrainC;

    cout << "������� ����� �������� ������� �� �������: ";
    cin >> arrivalTimeOfTrainA >> arrivalTimeOfTrainB >> arrivalTimeOfTrainC;

    thread trainA(trainArrival, "����� A", arrivalTimeOfTrainA);
    thread trainB(trainArrival, "����� B", arrivalTimeOfTrainB);
    thread trainC(trainArrival, "����� C", arrivalTimeOfTrainC);

    trainA.join();
    trainB.join();
    trainC.join();
}