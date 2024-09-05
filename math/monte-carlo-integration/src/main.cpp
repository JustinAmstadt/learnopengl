#include <iostream>
#include <random>

struct domain {
    double a;
    double b;
};

// Have it integrate x*x for now
float integrate1d(int numPoints, domain d) {
    double volume = d.b - d.a;
    double sum = 0;

    for (int i = 0; i < numPoints; ++i) {
		double x = d.a + (float(rand())/RAND_MAX) * (d.b - d.a);
        sum += x * x;
    }

    return (sum / numPoints) * volume;
}

int main() {
    const int NUM_LOOPS = 100;
    int sampleCount = 2000475010;

    domain d;
    d.a = -1.0;
    d.b = 1.0;

    float totalSum = 0;

    float output = integrate1d(sampleCount, d);
    totalSum += output;
    std::cout << "sampleCount: " << sampleCount << ", Output: " << output << std::endl;

    return 0;
}