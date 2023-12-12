#include <array>
#include <cstddef>

constexpr size_t N{128};

auto
main() -> int
{
    using T = double;
    const std::array<std::array<T, N>, N> A{};
    const std::array<std::array<T, N>, N> B{};
    std::array<std::array<T, N>, N> C{};
    for (auto i{0UZ}; i != N; ++i) {
        for (auto k{0UZ}; k != N; ++k) {
            for (auto j{0UZ}; j != N; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C[0][0];
}
