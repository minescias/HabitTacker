#ifndef __GET_SETTINGS_H
#define __GET_SETTINGS_H

#include <memory>

#include <Core/Config/Settings.h>

std::unique_ptr<Config::Settings> getSettings();

#endif // __GET_SETTINGS_H
