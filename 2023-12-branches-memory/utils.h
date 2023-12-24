
#include <algorithm>   // generate
#include <functional>  // bind
#include <iterator>    // begin, end, and ostream_iterator
#include <random>      // mt19937 and uniform_int_distribution
#include <vector>

std::vector<int> create_growing_array(int n, int stride, int input_array_len) {
    std::vector<int> v(n);
    int j = 0;
    for (int i = 0; i < n; i++) {
        v[i] = j;
        j = (j + stride) % input_array_len;
    }
    return v;
}

template <typename T>
std::vector<T> create_random_array(int n, int min, int max);

template <>
std::vector<int> create_random_array(int n, int min, int max) {
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 eng(seed);  // a source of random data

    std::uniform_int_distribution<int> dist(min, max - 1);
    std::vector<int> v(n);

    generate(begin(v), end(v), bind(dist, eng));
    return v;
}

template <>
std::vector<float> create_random_array(int n, int min, int max) {
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 eng(seed);  // a source of random data

    std::uniform_real_distribution<float> dist(min, max - 1);
    std::vector<float> v(n);

    generate(begin(v), end(v), bind(dist, eng));
    return v;
}

template <>
std::vector<double> create_random_array(int n, int min, int max) {
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 eng(seed);  // a source of random data

    std::uniform_real_distribution<double> dist(min, max - 1);
    std::vector<double> v(n);

    generate(begin(v), end(v), bind(dist, eng));
    return v;
}

int generate_random_growing_array(int* array, int len) {
    constexpr int random_array_len = 6;
    int random_array[random_array_len] = {1, 2, 4, 3, 1, 2};
    int j = 0;

    array[0] = 0;
    for (int i = 1; i < len; i++) {
        j = (j + 1) % random_array_len;
        array[i] = array[i - 1] + random_array[j];
    }
    return array[len - 1];
}

static void escape(void* p) {
    asm volatile("" : : "g"(p) : "memory");
}

static void clobber() {
    asm volatile("" : : : "memory");
}