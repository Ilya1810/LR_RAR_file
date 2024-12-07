#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdint>
#include <vector>

using namespace std;

//Установить 1-байтовое выравнивание
#pragma pack(push, 1)

// Объявление структуры
struct rar_header
{
    uint16_t header_crc;
    uint8_t header_type;
    uint16_t header_flag;
    uint16_t header_size;
   // char padding[8]; // Пропуск 8 байт (просто чтобы показать)
};

//Восстановить выравнивание
#pragma pack(pop)

int main()
{

    setlocale (LC_ALL, "Russian");

    return 0;
}
