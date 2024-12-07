#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdint>
#include <vector>

using namespace std;

// Установить 1-байтовое выравнивание
#pragma pack(push, 1)

// Объявление структуры для общей части заголовка
struct rar_header
{
    uint16_t header_crc;
    uint8_t header_type;
    uint16_t header_flag;
    uint16_t header_size;
};

// Объявление структуры для загловка файловой записи
struct file_head
{
    uint32_t pack_size;//! Размер упакованного файла
    uint32_t unp_size;
    uint8_t host_OS;
    uint32_t file_crc;
    uint32_t file_time;
    uint8_t unp_ver;
    uint8_t method;
    uint16_t name_size;//! Размер имени упакованного файла
    uint32_t file_attr;
};

// Функция, выводящая в консоль оглавление архива RAR
void RAR_file_content (vector<char> &data, const int &f_size)
{
    uint64_t i = 7;
    int length = 0;
    int k = 0;
    rar_header *p_rar_header;
    file_head *p_file_head;

    wcout << L"Оглавление архива ";
    cout << "RAR:" << endl;
    // Цикл, проходящий по всем заголовкам файлов внутри архива
    while ((f_size-i) > 0)
    {
        p_rar_header = reinterpret_cast<rar_header*>(&data[i]);// Считывание в структуру общей части заголовка

        if (p_rar_header->header_type == 116) // Проверка типа заголовка
        {
            p_file_head = reinterpret_cast<file_head*>(&data[i+7]); // Считывание специфической части заголовка
            length = p_file_head->name_size;

            // Оформление вывода
            k += 1;
            cout << k << ") ";
            for (int j=0; j<length; j++)
            cout << data[i+32+j];

            i += p_file_head->pack_size; // Смещение на длину упакованного файла
        }
        i += p_rar_header->header_size; // Смещение на длину заголовка
        cout << endl;
    }
}

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

        // Считать данные из файла
        vector<char> rar_data(rar_size, 0);
        rar_file.read(rar_data.data(), rar_size);

        // Вызов функции
        RAR_file_content(rar_data, rar_size);
    }

    return 0;
}
