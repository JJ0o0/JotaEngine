#pragma once

#include "Model.h"

#include <string>

namespace ModelLoader {
    Model* LoadModel(const std::string& path);
}