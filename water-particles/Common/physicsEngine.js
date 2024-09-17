class PhysicsEngine {
    static calcForces(particle, neighbors, h, k, restDensity) {
        let pressure = this.calcFp(particle, neighbors, h, k, restDensity);
        let gravity = this.calcGravity(particle.mass);
        gravity = vec2(0, 0);

        return add(pressure, gravity);
    }

    // mass: float
    static calcGravity(mass) {
        return vec2(0, -mass * 9.81);
    }

    static calcFp(particle, neighbors, h, k, restDensity) {
        let densityi = this.calcDensity(particle, neighbors, h);
        let pressurei = this.calcPressure(densityi, restDensity, k);
        let sum = vec2(0.0, 0.0);

        for (let i = 0; i < neighbors.length; i++) {
            let densityj = this.calcDensity(neighbors[i], neighbors, h);
            let pressurej = this.calcPressure(densityj, neighbors[i].restDensity, k);
            let scalar = neighbors[i].mass * ((pressurei / (densityi * densityi)) + (pressurej / (densityj * densityj)));

            let gradient = this.gradientOfGaussianKernel(particle.position, neighbors[i].position, h);
            let output = vec2(scalar * gradient[0], scalar * gradient[1]);

            sum = add(sum, output);
        }

        return vec2(-sum[0], -sum[1]);
    }

    // r: float: magnitude(ri - rj)
    // h: float: smoothing length
    static gaussianKernel(r, h) {
        return 1.0 / Math.pow((2 * Math.PI * h * h), 1.5) * Math.exp(-(r * r) / (2 * h * h));
    }

    static cubicSplineKernel() {

    }

    // pi: vec2 of this particle
    // pj: vec2 of neighboring particle
    // h: float: smoothing length
    static gradientOfGaussianKernel(pi, pj, h) {
        let r_vec = subtract(pi, pj);
        let r = magnitude(r_vec);

        let W = this.gaussianKernel(r, h);
        let factor = -(1 / (h * h)) * W;  // The scalar factor for the gradient

        let gradient = vec2(factor * (r_vec[0] / r), factor * (r_vec[1] / r));
        return gradient;
    }

    // p: Particle
    // neighbors: Particle[]
    // h: smoothing length
    static calcDensity(particle, neighbors, h) {
        let sum = 0.0;

        for (let i = 0; i < neighbors.length; i++) {
            let rij = subtract(particle.position, neighbors[i].position);
            sum += neighbors[i].mass * this.gaussianKernel(magnitude(rij), h);
        }

        return sum;
    }

    static calcPressure(density, restDensity, k) {
        return k * (density - restDensity);
    }
}