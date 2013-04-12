#pragma once


#include <memory>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include <cstdint>
#include <cassert>


namespace dagger {


typedef std::shared_ptr<int32_t> data_t;
typedef std::vector<bool>        bit_mask_t;

}
