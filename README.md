[![CodeQL Advanced](https://github.com/HotWizard/TurboINI/actions/workflows/codeql.yml/badge.svg)](https://github.com/HotWizard/TurboINI/actions/workflows/codeql.yml)
# TurboINI
### Примечания
- Версия C++ >= 17.
### Документация
Документацию можете посмотреть в файле [DOCUMENTATION.md](DOCUMENTATION.md)
### Пример "test.ini" INI файла
```ini
"integer"=1
"string"="string"

["namespace"]
"integer"=1
"string"="1"
```
### Пример кода C++
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
