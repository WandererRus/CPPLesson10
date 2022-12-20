// CPPLesson10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cassert>
using namespace std;
class MedalRow
{
    char country[4];
    int medals[3];
public:
    static const int GOLD{ 0 };
    static const int SILVER{ 1 };
    static const int BRONZE{ 2 };
    MedalRow(const char* countryP, const int* medalsP)
    {
        strcpy_s(country, 4, countryP ? countryP : "NON");
        for (int i{ 0 }; i < 3; ++i)
        {
            medals[i] = medalsP ? medalsP[i] : 0;
        }
    }    
    MedalRow() : MedalRow(nullptr, nullptr) {}

    MedalRow& operator=(MedalRow& row) 
    {
        for (int i{ 0 }; i < 4; ++i)
        {
            country[i] = row.country[i];
        }
        for (int i{ 0 }; i < 3; ++i)
        {
            medals[i] =  row.medals[i];
        }
    }
    MedalRow& operator=(const MedalRow& row)
    {
        for (int i{ 0 }; i < 4; ++i)
        {
            country[i] = row.country[i];
        }
        for (int i{ 0 }; i < 3; ++i)
        {
            medals[i] = row.medals[i];
        }
    }
    MedalRow& setCountry(const char* countryP)
    {
        if (countryP)
        {
            strcpy_s(country, 4, countryP);
        }
        return *this;
    }
    const char* getCountry()const { return country; }

    int& operator[](int idx)
    {
        assert((idx >= 0 and idx < 3) and "Index out "
            "of range!");
        return medals[idx];
    }
    int operator[](int idx)const
    {
        assert((idx >= 0 and idx < 3) and "Index out "
            "of range!");
        return medals[idx];
    }
    friend ostream& operator<<(ostream& out,const MedalRow& row) {
        out << '[' << row.country << "]-( ";
        for (int i{ 0 }; i < 3; ++i)
        {
            out << row.medals[i];
            if (i < 2) { out << '\t'; }
        }
        out << " )\n";
        return out;
    }    
};

class MedalsTable
{
private:
    MedalRow* medalRows;
    int maxsize;
    int size;
    int findCountry(const char* country)const
    {
        for (int i{ 0 }; i < size; ++i)
        {
            if (strcmp(medalRows[i].getCountry(),
                country) == 0)
            {
                return i;
            }
        }
        return -1;
    }
public:
    MedalsTable() : size{ 0 }, maxsize{10}, medalRows{ new MedalRow[10] }
    {};
    MedalsTable(int massivesize) : size{ 0 },maxsize{ massivesize },medalRows {new MedalRow[massivesize]}
    {  };
    /*MedalsTable& operator=(const MedalsTable&& object)   разобраться с обнулением объектов класса
    {
        if (!(this == &object))
        {
            delete medalRows;
            medalRows = object.medalRows;
            size = object.size;
            maxsize = object.maxsize;
        }
        std::cout << "DynArr move assigned for "
            << size << " elements, for " << this
            << '\n';
        return *this;
    }*/
    MedalRow& operator[](const char* country)
    {
        int idx{ findCountry(country) };
        if (idx == -1)
        {
            assert(size < maxsize and
                "Table is FULL!");
            idx = size++;
            medalRows[idx].setCountry(country);
        }
        return medalRows[idx];
    }
    const MedalRow& operator[](const char* country)const
    {
        int idx{ findCountry(country) };
        assert(idx != -1 and "Country not found on const "
            "table");
        return medalRows[idx];
    }

    friend ostream& operator<<(ostream& out, const MedalsTable& table) {
        
        for (int i{ 0 }; i < table.size; ++i)
        {
            out << table.medalRows[i];
        }

        return out;
    }   

    void operator()(const char* country)
    {
        
        if (medalRows[findCountry(country)][0] >= medalRows[findCountry(country)][1])
        {
            if (medalRows[findCountry(country)][0] >= medalRows[findCountry(country)][2])
            {
                cout << "У " << country << " больше всего золотых медалей: " << medalRows[findCountry(country)][0];
            }
            else
            {
                cout << "У " << country << " больше всего бронзовых медалей: " << medalRows[findCountry(country)][2];
            }
        }
        else if(medalRows[findCountry(country)][1] >= medalRows[findCountry(country)][2])
        {
            cout << "У "<< country<< " больше всего серебрянных медалей : " << medalRows[findCountry(country)][1];
        }
        else
        {
            cout << "У " << country << " больше всего бронзовых медалей: " << medalRows[findCountry(country)][2];
        }
         
    }
};
int main()
{
    setlocale(LC_ALL, "Russian");
    int tableCount = 0;
    cout << "Введите количество элементов в таблице медалей" << endl;
    cin >> tableCount;
    MedalsTable mt1(tableCount);
    std::cout << "Medals table #1:\n";
    mt1["UKR"][MedalRow::GOLD] = 14;
    mt1["UKR"][MedalRow::SILVER] = 15;
    mt1["HUN"][MedalRow::BRONZE] = 9;
    mt1["HUN"][MedalRow::GOLD] = 7;
    mt1["POL"][MedalRow::GOLD] = 4;
    cout << mt1;
    std::cout << "\nMedals table #2:\n";
    const MedalsTable mt2{ mt1 };
    cout << mt2;
    mt1("UKR");

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
