# TurboINI документация
## parser.hpp
### Класс parser:
- ```hpp
  const bool open(const std::string &path) const
  ```
  Функция типа ```bool```, предназначена для открывания файла по конкретной директории, возвращает ```false``` если не удалось открыть файл.
- ```hpp
  const bool exists(const types &type, const std::string &key) const
  ```
  Функция типа ```bool```, проверяет если конкретный тип данных ```TurboINI::types``` существует в файле.
- ```hpp
  const bool NamespaceExists(const std::string &key) const
  ```
  Функция типа ```bool```, проверяет если конкретное пространство имён существует в файле.
- ```hpp
  const bool ExistsInNamespace(const types &type, const std::string &NamespaceKey, const std::string &key) const
  ```
  Функция типа ```bool```, проверяет если конкретный тип данных существует в конертном пространстве имён.
- ```hpp
  const long long &GetInteger(const std::string &key);
  ```
  Функция типа ```long long```, возвращает значение целого числа конкретного названия.
- ```hpp
  const std::string &get(const std::string &key) const
  ```
  Функция типа ```std::string```, возвращает значение строки конкретного названия.
- ```hpp
  const std::string &GetFromNamespace(const std::string &NamespaceKey, const std::string &key) const
  ```
  Функция типа ```std::string```, возвращает значение строки конкретного названия, из конкретного пространства имён.
- ```hpp
  const long long &GetIntegerFromNamespace(const std::string &NamespaceKey, const std::string &key) const;
  ```
  Функция типа ```long long```, возвращает значение целого числа конкретного названия, из конкретного пространства имён.
- ```hpp
  void close(void) const
  ```
- ```hpp
  void EnableRefreshing(const bool &status) const
  ```
- ```hpp
  void SetRefreshRate(const double &milliseconds) const
  ```
