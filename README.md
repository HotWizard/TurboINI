[![CodeQL Advanced](https://github.com/HotWizard/TurboINI/actions/workflows/codeql.yml/badge.svg)](https://github.com/HotWizard/TurboINI/actions/workflows/codeql.yml)
# TurboINI
### Примечания
- Версия C++ >= 17.
- [xmake](https://xmake.io/#/)
### Построение и запуск тестовых программ
```shell
# Построение
xmake && xmake build TurboINITest0
# Запуск тестовой программы tests/0.cpp
xmake run TurboINITest0
```
### Документация
Документацию можете посмотреть в файле [DOCUMENTATION.md](DOCUMENTATION.md)
### Пример кода C++, не требующий \"INI\" файла
```cpp
#include "TurboINI.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>

using TIT = TurboINI::types;

inline std::unique_ptr<TurboINI::parser> parser;

const inline void InitParser(const std::string &raw)
{
    parser = std::make_unique<TurboINI::parser>(raw);
}

int main(void)
{
    InitParser("\"integer\"=324");

    if (parser->exists(TIT::INTEGER, "integer"))
        std::cout << parser->GetInteger("integer") << std::endl;

    return EXIT_SUCCESS;
}
```
---
### Пример кода C++, но уже с использованием \"INI\" файла
```cpp
// main.cpp
#include "TurboINI.hpp"

#include <cstdlib>
#include <iostream>

using namespace std;

TurboINI::parser parser;

const inline void init(const std::string &path)
{
    if (!parser.open(path))
        exit(EXIT_FAILURE);

    parser.EnableRefreshing(true);
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        init(argv[1]);

        if (parser.exists(TurboINI::types::INTEGER, "integer"))
            cout << parser.GetInteger("integer") << endl;
        if (parser.exists(TurboINI::types::STRING, "string"))
            cout << parser.get("string") << endl;
        if (parser.NamespaceExists("namespace"))
        {
            if (parser.ExistsInNamespace(TurboINI::types::INTEGER, "namespace", "integer"))
                cout << parser.GetIntegerFromNamespace("namespace", "integer") << endl;
            if (parser.ExistsInNamespace(TurboINI::types::STRING, "namespace", "string"))
                cout << parser.GetFromNamespace("namespace", "string") << endl;
        }
    }

    parser.close();

    return EXIT_SUCCESS;
}
```
```ini
"integer"=1
"string"="string"

["namespace"]
"integer"=1
"string"="1"
```
### Пример команды компиляции и запуска тестовой программы с помощью GCC на Unix
```shell
g++ -std=c++17 -Wall -Werror -Wpedantic -pedantic-errors -g tools.cpp parser.cpp main.cpp && ./a.out test.ini
```
### ToDo
- [x] Добавить возможность чтения значения строки.
- [x] Добавить возможность чтения пространств имён.
- [ ] Добавить возможность чтения массивов.
- [x] Добавить возможность чтения целых чисел.
- [ ] Добавить возможность чтения вещественных чисел.
