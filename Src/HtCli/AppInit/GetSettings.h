#ifndef __GET_SETTINGS_H
#define __GET_SETTINGS_H

#include <memory>
#include <string>

#include <Core/Config/Settings.h>

std::unique_ptr<Config::Settings> getSettings(const std::string& filename);

#endif // __GET_SETTINGS_H
