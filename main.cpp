#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdint>
#include <vector>

using namespace std;

//Установить 1-байтовое выравнивание
#pragma pack(push, 1)

// Объявление структуры для общей части заголовка
struct rar_header
{
    uint16_t header_crc;
    uint8_t header_type;
    uint16_t header_flag;
    uint16_t header_size;
};

// Восстановить выравнивание
#pragma pack(pop)

int main()
{
    setlocale (LC_ALL, "Russian");

    ifstream rar_file("Example.rar", ios::binary);
    if (rar_file.is_open())
    {
        // Определить размер файла
        rar_file.seekg(0, ios::end);
        int rar_size = rar_file.tellg();
        rar_file.seekg(0, ios::beg);
        cout << rar_size << endl;

        // Считать данные из файла
        vector<char> rar_data(rar_size, 0);
        rar_file.read(rar_data.data(), rar_size);
    }

    return 0;
}
