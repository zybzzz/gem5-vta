#include <array>
#include <chrono>
#include <cstddef>
#include <iostream>

constexpr size_t N{128};

auto
main() -> int
{
    using T = double;
    const std::array<std::array<T, N>, N> A{};
    const std::array<std::array<T, N>, N> B{};
    std::array<std::array<T, N>, N> C{};
    std::chrono::duration<double> total =
        std::chrono::duration<double>::zero();

    for (auto t{0UZ}; t != 40; ++t) {
        const auto start = std::chrono::steady_clock::now();
        for (auto i{0UZ}; i != N; ++i) {
            for (auto k{0UZ}; k != N; ++k) {
                for (auto j{0UZ}; j != N; ++j) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        const auto end = std::chrono::steady_clock::now();
        total += {end - start};
    }
    std::cout << "running_time: " << total / 40 << std::endl;

    return C[0][0];
}
