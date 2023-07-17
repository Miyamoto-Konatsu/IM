#include "config.h"

YAML::Node getConfig() {
    static auto config = YAML::LoadFile(CONFIG_FILE_PATH);
    return config;
}