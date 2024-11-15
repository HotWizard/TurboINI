[![CodeQL Advanced](https://github.com/HotWizard/TurboINI/actions/workflows/codeql.yml/badge.svg)](https://github.com/HotWizard/TurboINI/actions/workflows/codeql.yml)
# TurboINI
### Примечания
- Версия C++ >= 17, рекомендуется 20.
### Пример простого ".ini" файла
```ini
"string" = "value"

["namespace"]
"string" = "value"
```
### Пример простой программы
```cpp
#include "TurboINI.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(void)
{
    const chrono::steady_clock::time_point start = chrono::steady_clock::now();

    TurboINI::parser parser;

    if (!parser.open("test.ini"))
        return EXIT_FAILURE;

    if (parser.exists("string"))
    {
        for (size_t i = 0; i < 1000000; i++)
            parser.get("string");
    }

    if (parser.NamespaceExists("namespace") && parser.ExistsInNamespace("namespace", "string"))
        cout << parser.GetFromNamespace("namespace", "string") << endl;

    chrono::duration<double> stop{chrono::steady_clock::now() - start};

    cout << stop << endl;

    return EXIT_SUCCESS;
}
```
### ToDo
- [x] Добавить возможность чтения значения строки.
- [x] Добавить возможность чтения пространств имён.
- [ ] Добавить возможность чтения массивов.
