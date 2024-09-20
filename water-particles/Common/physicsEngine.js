class PhysicsEngine {
    // particle: Particle
    // neighbors: Particle[]
    // h: float
    // k: float
    // restDensity: float
    // return: F: vec2
    static calcForces(particle, neighbors, h) {
        let pressure = this.calcFp(particle, neighbors, h);
        let gravity = this.calcGravity(particle.mass);

        return add(pressure, gravity);
    }

    // mass: float
    // return: Fg: vec2
    static calcGravity(mass) {
        return vec2(0, -mass * 0.81);
    }

    // particle: Particle
    // neighbors: Particle[]
    // h: float
    // k: float
    // restDensity: float
    // return: Fp: vec2
    static calcFp(particle, neighbors, h) {
        let densityi = particle.prevDensity;
        let pressurei = particle.prevPressure;

        let sum = vec2(0.0, 0.0);

        for (let i = 0; i < neighbors.length; i++) {
            let densityj = neighbors[i].prevDensity;
            let pressurej = neighbors[i].prevPressure;
            let scalar = neighbors[i].mass * ((pressurei / (densityi * densityi)) + (pressurej / (densityj * densityj)));

            let gradient = this.gradientOfGaussianKernel(particle.position, neighbors[i].position, h);


            let output = vec2(scalar * gradient[0], scalar * gradient[1]);

            console.log(`
                Neighbor ${i}:
                    Previous Density (densityj): ${densityj}
                    Previous Pressure (pressurej): ${pressurej}
                    Scalar: ${scalar}
                    Gradient: (${gradient[0]}, ${gradient[1]})
                    Output: (${output[0]}, ${output[1]})
            `);

            if (isNaN(gradient)) {continue};

            sum = add(sum, output);
        }

        return vec2(-sum[0], -sum[1]);
    }

    // r: float: magnitude(ri - rj)
    // h: float: smoothing length
    // return: float
    static gaussianKernel(r, h) {
        if (h <= 0) throw new Error("Smoothing length h must be positive.");
        return 1.0 / Math.pow((2 * Math.PI * h * h), 1.5) * Math.exp(-(r * r) / (2 * h * h));
    }

    static cubicSplineKernel() {

    }

    // pi: vec2 of this particle
    // pj: vec2 of neighboring particle
    // h: float: smoothing length
    // return: gradient: vec2
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
    // return: density: float
    static calcDensity(particle, neighbors, h) {
        let sum = 0.0;

        for (let i = 0; i < neighbors.length; i++) {
            let rij = subtract(particle.position, neighbors[i].position);
            let r = magnitude(rij);

            // Only include neighbors with a non-zero distance to avoid singularities
            if (r > 0) {
                sum += neighbors[i].mass * this.gaussianKernel(r, h);
            }
        }

        // return sum;
        return .9;
    }    
    
    // density: float
    // restDensity: float
    // k (stiffness constant): float
    // return: pressure: float
    static calcPressure(density, restDensity, k) {
        return this.clampPressure(k * (density - restDensity));
    }

    static clampPressure(value) {
        let min = -1;
        let max = 1;
        return Math.max(min, Math.min(max, value));
    }
}