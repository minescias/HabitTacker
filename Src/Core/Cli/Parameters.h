#ifndef __PARSER_RESULT_H
#define __PARSER_RESULT_H

#include <map>
#include <set>
#include <string>

namespace Cli
{

struct Parameters
{
    Parameters();

    void setCommandName(const std::string& name);
    std::string getCommandName() const;

    void setFilter(const std::string& filter);
    std::string getFilter() const;

    void setFlag(const std::string& flagName);
    bool getFlag(const std::string& flagName) const;

    void setDefaultParameter(const std::string& value);
    std::string getDefaultParameter() const;

    void setParameter(const std::string& name, const std::string& value);
    std::string getParameter(const std::string& name) const;

    // for validation
    std::map<std::string, std::string> getAllArguments() const;

private:
    std::string commandName;
    std::string filter;
    std::string defaultParameter;
    std::map<std::string, std::string> arguments;
};

} // namespace Cli

#endif
