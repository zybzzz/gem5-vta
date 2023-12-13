#ifndef VTA_CONFIG_HH
#define VTA_CONFIG_HH

#include <cstddef>

namespace vta
{

constexpr size_t LOG_INPUT_WIDTH{3};
constexpr size_t LOG_WEIGHT_WIDTH{3};
constexpr size_t LOG_ACCUMULATOR_WIDTH{5};
constexpr size_t LOG_BATCH{0};
constexpr size_t LOG_BLOCK{4};
constexpr size_t LOG_MICRO_OP_BUFFER_SIZE{15};
constexpr size_t LOG_INPUT_BUFFER_SIZE{15};
constexpr size_t LOG_WEIGHT_BUFFER_SIZE{18};
constexpr size_t LOG_ACCUMULATOR_BUFFER_SIZE{17};

} // namespace vta

#endif
