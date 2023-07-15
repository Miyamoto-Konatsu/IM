#include "config.h"

YAML::Node get_config() {
    static auto config = YAML::LoadFile(CONFIG_FILE_PATH);
    return config;
}