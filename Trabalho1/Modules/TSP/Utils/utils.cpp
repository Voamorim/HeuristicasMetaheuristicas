#include "utils.hpp"

float getRandomFloat(mt19937& gen) {
        uniform_real_distribution<float> dis(0.0f, 1.0f);
        return dis(gen);
}

int getRandomInteger(int l, int r, mt19937& gen) {
        uniform_int_distribution<int> dis(l, r);
        return dis(gen);
}
