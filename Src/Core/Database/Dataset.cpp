
#include "Core/Database/Dataset.h"

#include <ctime>

#include "Core/Utils/Exceptions/LogicError.h"
#include "Core/Utils/Exceptions/RuntimeError.h"
#include "Core/Utils/Strings/Case.h"
#include "Core/Utils/Types/TypeNames.h"

namespace
{

template<typename  T>
using  CastFunction = T (const std::string&);

template<typename  T>
T tryToCast(const std::string& name, const std::string& value,
    CastFunction<T>* castFuncion)
{
    try
    {
        return castFuncion(value);
    }
    catch(std::logic_error& err)
    {
        auto typeName = getTypeName(typeid(T).hash_code());

        std::string msg = "Dataset: Can't cast column '" + name + "' "
            + "value '" + value + "' to " + typeName;

        throw LogicError(msg);
    }
}

} // namespace

namespace Db
{

Dataset::Dataset()
    : firstNextIgnored(false)
{
}

void Dataset::addColumn(const std::string& name)
{
    columns[Strings::lower_copy(name)] = getColumnsCount();
}

void Dataset::addRow(const Row& row)
{
    assertInitialized();

    data.push_back(row);
    currentRow = data.begin();
}

bool Dataset::next()
{
    assertInitialized();

    if (!firstNextIgnored)
        firstNextIgnored = true;
    else
        currentRow++;

    return currentRow != data.end();
}

bool Dataset::initialized() const
{
    return !columns.empty();
}

bool Dataset::empty() const
{
    assertInitialized();
    return data.empty();
}

int Dataset::getColumnsCount()
{
    return columns.size();
}

int Dataset::getRowsCount()
{
    assertInitialized();
    return data.size();
}

template<>
int Dataset::getAs<int>(const std::string& name)
{
    assertValueIsNotEmpty(name);

    auto castFunc = [](const std::string& value){return stoi(value);};
    return tryToCast<int>(name, getColumnValue(name), castFunc);
}

template<>
time_t Dataset::getAs<time_t>(const std::string& name)
{
    assertValueIsNotEmpty(name);

    auto castFunc = [](const std::string& value){return time_t(stol(value));};
    return tryToCast<time_t>(name, getColumnValue(name), castFunc);
}

template<>
std::optional<int> Dataset::getAs<std::optional<int>>(const std::string& name)
{
    auto value =  getColumnValue(name);
    if (value.empty())
        return std::nullopt;

    auto castFunc = [](const std::string& value){return stoi(value);};
    auto result = tryToCast<int>(name, getColumnValue(name), castFunc);
    return std::make_optional<int>(result);
}

template<>
double Dataset::getAs<double>(const std::string& name)
{
    assertValueIsNotEmpty(name);

    auto castFunc = [](const std::string& value){return stod(value);};
    return tryToCast<double>(name, getColumnValue(name), castFunc);
}

template<>
std::optional<double> Dataset::getAs<std::optional<double>>(const std::string& name)
{
    auto value =  getColumnValue(name);
    if (value.empty())
        return std::nullopt;

    auto castFunc = [](const std::string& value){return stod(value);};
    auto result = tryToCast<double>(name, getColumnValue(name), castFunc);
    return std::make_optional<double>(result);
}

template<>
std::string Dataset::getAs<std::string>(const std::string& name)
{
    return getColumnValue(name);
}


std::string Dataset::getColumnValue(const std::string& name) const
{
    if (empty())
        throw LogicError("Dataset is empty");

    try
    {
        auto columnIndex = columns.at(Strings::lower_copy(name));
        return currentRow->at(columnIndex);
    }
    catch(std::logic_error& err)
    {
        std::string message
            = "Dataset: Trying to access nonexisting column (" + name + ")";

        throw LogicError(message);
    }
}

void Dataset::assertInitialized() const
{
    if (!initialized())
        throw LogicError("Dataset is not initialized");
}

void Dataset::assertValueIsNotEmpty(const std::string& name) const
{
    auto value = getColumnValue(name);
    if (!value.empty())
        return;

    std::string message = "Cannot cast empty value of column \"" + name +
        "\" to non nullable object";

    throw LogicError(message);
}

} //namespace Db

