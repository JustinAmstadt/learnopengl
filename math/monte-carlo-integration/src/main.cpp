#include <iostream>
#include <random>

struct domain {
    double a;
    double b;
};

float mathFunction(double x) {
    return x * x;
}

// Integrate in 1 dimension
float integrate1d(int numPoints, domain d) {
    double volume = d.b - d.a;
    double sum = 0;

    for (int i = 0; i < numPoints; ++i) {
		double randNum = d.a + (float(rand())/RAND_MAX) * (d.b - d.a);
        sum += mathFunction(randNum);
    }

    return (sum / numPoints) * volume;
}

int main() {
    const int NUM_LOOPS = 100;
    int sampleCount = 2475010;

    domain d;
    d.a = -1.0;
    d.b = 1.0;

    float totalSum = 0;

    float output = integrate1d(sampleCount, d);
    totalSum += output;
    std::cout << "sampleCount: " << sampleCount << ", Output: " << output << std::endl;

    return 0;
}