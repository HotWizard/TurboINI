#include "data.hpp"

#include <thread>

TurboINI::DataTypes::DataType::DataType()
{
}

TurboINI::DataTypes::DataType::DataType(const std::string &key)
{
    SetKey(key);
}

TurboINI::DataTypes::DataType::~DataType()
{
    auto a = std::make_unique<std::thread>([&](void) { key.reset(); });

    a->join();
}

void TurboINI::DataTypes::DataType::SetKey(const std::string &key)
{
    this->key = std::make_shared<std::string>(key);
}

const std::string &TurboINI::DataTypes::DataType::GetKey() const
{
    return *key;
}

TurboINI::DataTypes::integer::integer()
{
}

TurboINI::DataTypes::integer::integer(const std::string &key, const long long &value)
    : value(std::make_shared<long long>(value))
{
    SetKey(key);
}

TurboINI::DataTypes::integer::~integer()
{
    auto a = std::make_unique<std::thread>([&](void) { value.reset(); });

    a->join();
}

void TurboINI::DataTypes::integer::SetValue(const long long &value)
{
    this->value = std::make_shared<long long>(value);
}

const long long &TurboINI::DataTypes::integer::GetValue() const
{
    return *value;
}

TurboINI::DataTypes::string::string()
{
}

TurboINI::DataTypes::string::string(const std::string &key, const std::string &value)
{
    SetKey(key);
    SetValue(value);
}

void TurboINI::DataTypes::string::SetValue(const std::string &value)
{
    this->value = std::make_shared<std::string>(value);
}

const std::string &TurboINI::DataTypes::string::GetValue() const
{
    return *value;
}

TurboINI::DataTypes::string::~string()
{
    auto a = std::make_unique<std::thread>([&](void) { value.reset(); });

    a->join();
}

TurboINI::DataTypes::_namespace::_namespace()
{
}

TurboINI::DataTypes::_namespace::_namespace(const std::string &key, const std::vector<integer> &integers,
                                            const std::vector<string> &strings)
{
    SetKey(key);
    SetIntegers(integers);
    SetStrings(strings);
}

void TurboINI::DataTypes::_namespace::SetIntegers(const std::vector<integer> &integers)
{
    this->integers = std::make_shared<std::vector<integer>>(integers);
}

void TurboINI::DataTypes::_namespace::SetStrings(const std::vector<string> &strings)
{
    this->strings = std::make_shared<std::vector<string>>(std::vector<string>(strings));
}

std::vector<TurboINI::DataTypes::integer> &TurboINI::DataTypes::_namespace::GetIntegers() const
{
    return *integers;
}

std::vector<TurboINI::DataTypes::string> &TurboINI::DataTypes::_namespace::GetStrings() const
{
    return *strings;
}

TurboINI::DataTypes::_namespace::~_namespace()
{
    auto a = std::make_unique<std::thread>([&](void) { integers.reset(); }),
         b = std::make_unique<std::thread>([&](void) { strings.reset(); });

    a->join();
    b->join();
}

TurboINI::data::data()
{
}

TurboINI::data::data(const std::vector<DataTypes::integer> &integers, const std::vector<DataTypes::string> &strings,
                     const std::vector<DataTypes::_namespace> &namespaces)
{
    SetIntegersVector(integers);
    SetStringsVector(strings);
    SetNamespacesVector(namespaces);
}

void TurboINI::data::SetIntegersVector(const std::vector<DataTypes::integer> &integers)
{
    this->integers = std::make_shared<std::vector<DataTypes::integer>>(integers);
}

void TurboINI::data::SetStringsVector(const std::vector<DataTypes::string> &strings)
{
    this->strings = std::make_shared<std::vector<DataTypes::string>>(strings);
}

void TurboINI::data::SetNamespacesVector(const std::vector<DataTypes::_namespace> &namespaces)
{
    this->namespaces = std::make_shared<std::vector<DataTypes::_namespace>>(namespaces);
}

std::vector<TurboINI::DataTypes::integer> &TurboINI::data::GetIntegersVector() const
{
    return *integers;
}

std::vector<TurboINI::DataTypes::string> &TurboINI::data::GetStringsVector() const
{
    return *strings;
}

std::vector<TurboINI::DataTypes::_namespace> &TurboINI::data::GetNamespacesVector() const
{
    return *namespaces;
}

TurboINI::data::~data()
{
    auto a = std::make_unique<std::thread>([&](void) { integers.reset(); }),
         b = std::make_unique<std::thread>([&](void) { strings.reset(); }),
         c = std::make_unique<std::thread>([&](void) { namespaces.reset(); });

    a->join();
    b->join();
    c->join();
}
