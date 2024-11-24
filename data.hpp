#pragma once

#ifndef TURBOINI_DATA_HPP
#define TURBOINI_DATA_HPP

#include <memory>
#include <string>
#include <vector>

namespace TurboINI
{
    namespace DataTypes
    {
        class DataType
        {
          public:
            explicit DataType();
            explicit DataType(const std::string &key);
            ~DataType();

            void SetKey(const std::string &key);

            const std::string &GetKey() const;

          private:
            std::shared_ptr<std::string> key;
        };

        class integer : public DataType
        {
          public:
            explicit integer();
            explicit integer(const std::string &key, const long long &value);
            ~integer();

            void SetValue(const long long &value);

            const long long &GetValue() const;

          private:
            std::shared_ptr<long long> value;
        };

        class string : public DataType
        {
          public:
            explicit string();
            explicit string(const std::string &key, const std::string &value);
            ~string();

            void SetValue(const std::string &value);

            const std::string &GetValue() const;

          private:
            std::shared_ptr<std::string> value;
        };

        class _namespace : public DataType
        {
          public:
            explicit _namespace();
            explicit _namespace(const std::string &key, const std::vector<integer> &integers,
                                const std::vector<string> &strings);
            ~_namespace();

            void SetIntegers(const std::vector<integer> &integers), SetStrings(const std::vector<string> &strings);

            std::vector<integer> &GetIntegers() const;
            std::vector<string> &GetStrings() const;

          private:
            std::shared_ptr<std::vector<integer>> integers;
            std::shared_ptr<std::vector<string>> strings;
        };
    } // namespace DataTypes

    class data
    {
      public:
        explicit data();
        explicit data(const std::vector<DataTypes::integer> &integers, const std::vector<DataTypes::string> &strings,
                      const std::vector<DataTypes::_namespace> &namespaces);
        ~data();

        void SetIntegersVector(const std::vector<DataTypes::integer> &integers),
            SetStringsVector(const std::vector<DataTypes::string> &strings),
            SetNamespacesVector(const std::vector<DataTypes::_namespace> &namespaces);

        std::vector<DataTypes::integer> &GetIntegersVector() const;
        std::vector<DataTypes::string> &GetStringsVector() const;
        std::vector<DataTypes::_namespace> &GetNamespacesVector() const;

      private:
        std::shared_ptr<std::vector<DataTypes::integer>> integers;
        std::shared_ptr<std::vector<DataTypes::string>> strings;
        std::shared_ptr<std::vector<DataTypes::_namespace>> namespaces;
    };
} // namespace TurboINI

#endif // TURBOINI_DATA_HPP
