class ParticleSystem {
    numParticles;
    particles;
    collisionDamping;
    circleScale;

    h = 1;
    k = 1;

    constructor(numParticles) {
        this.numParticles = numParticles;
        this.circleScale = 0.02;
        this.particles = this.genParticles();
        this.collisionDamping = 0.01;
    }

    genParticles() {
        let particleSpacing = 0.01; 
        let particlesPerRow = Math.floor(Math.sqrt(this.numParticles));
        let particlesPerCol = Math.floor((this.numParticles - 1) / particlesPerRow + 1);
        let spacing = this.circleScale * 2 + particleSpacing;

        let particles = [];

        for (let i = 0; i < this.numParticles; i++) {
            let x = (i % particlesPerRow - particlesPerRow / 2.0 + 0.5) * spacing;
            let y = (i / particlesPerRow - particlesPerCol / 2.0 + 0.5) * spacing;
            particles.push(new Particle(vec2(x, y), this.circleScale));
        }

        return particles;
    }

    findNeighbors(particleIndex) {
        return this.particles.filter((_, index) => index !== particleIndex);
    }
}

class Particle {
    acceleration;
    velocity;
    position;

    restDensity;
    mass;

    circleScale;
    screenEdge;

    constructor(p, circleScale) {
        this.acceleration = vec2(0.0, 0.0);
        this.velocity = vec2(0.0, 0.0);
        this.position = p;
        this.screenEdge = 1.0 - circleScale;
        this.mass = 0.005097;
        this.restDensity = 1;
        this.circleScale = circleScale
    }

    update(dt, neighbors, h, k) {
        let F = this.calcForces(neighbors, h, k);
        this.acceleration = vec2(F[0] / this.mass, F[1] / this.mass);
        this.velocity = add(this.velocity, mult(this.acceleration, vec2(dt, dt)));
        this.position = add(this.position, mult(this.velocity, vec2(dt, dt)));

        if (this.position[0] > this.screenEdge) {
            this.position[0] = this.screenEdge;
            this.velocity[0] = -this.velocity[0]
        }
        if (this.position[0] < -this.screenEdge) {
            this.position[0] = -this.screenEdge;
            this.velocity[0] = -this.velocity[0]
        }
        if (this.position[1] > this.screenEdge) {
            this.position[1] = this.screenEdge;
            this.velocity[1] = -this.velocity[1]
        }
        if (this.position[1] < -this.screenEdge) {
            this.position[1] = -this.screenEdge;
            this.velocity[1] = -this.velocity[1]
        }

        return mult(translate(this.position[0], this.position[1], 0.0), scalem(this.circleScale, this.circleScale, 1));
    }

    calcForces(neighbors, h, k) {
        let pressure = this.calcFp(neighbors, h, k);
        let gravity = this.calcGravity(this.mass);
        gravity = vec2(0, 0);

        return vec2(pressure[0] + gravity[0], pressure[1] + gravity[1]);
    }

    // mass: float
    calcGravity(mass) {
        return vec2(0, -mass * 9.81);
    }

    calcFp(neighbors, h, k) {
        let densityi = this.calcDensity(this, neighbors, h);
        let pressurei = this.calcPressure(densityi, this.restDensity, k);
        let sum = vec2(0.0, 0.0);

        for (let i = 0; i < neighbors.length; i++) {
            let r = this.magnitude(vec2(this.position[0] - neighbors[i].position[0], this.position[1] - neighbors[i].position[1]));
            let densityj = this.calcDensity(neighbors[i], neighbors, h);
            let pressurej = this.calcPressure(densityj, neighbors[i].restDensity, k);
            let scalar = neighbors[i].mass * ((pressurei / (densityi * densityi)) + (pressurej / (densityj * densityj)));

            let gradient = this.gradientOfGaussianKernel(this, neighbors[i], h);
            let output = vec2(scalar * gradient[0], scalar * gradient[1]);

            sum = vec2(sum[0] + output[0], sum[1] + output[1]);
        }

        return vec2(-sum[0], -sum[1]);
    }

    // r: float: magnitude(ri - rj)
    // h: float: smoothing length
    gaussianKernel(r, h) {
        return 1.0 / Math.pow((2 * Math.PI * h * h), 1.5) * Math.exp(-(r * r) / (2 * h * h));
    }

    cubicSplineKernel() {

    }

    // pi: vec2 of this particle
    // pj: vec2 of neighboring particle
    // h: float: smoothing length
    gradientOfGaussianKernel(pi, pj, h) {
        let r_vec = vec2(pi.position[0] - pj.position[0], pi.position[1] - pj.position[1])
        let r = this.magnitude(r_vec);

        let W = this.gaussianKernel(r, h);
        let factor = -(1 / (h * h)) * W;  // The scalar factor for the gradient

        let gradient = vec2(factor * (r_vec[0] / r), factor * (r_vec[1] / r));
        return gradient;
    }

    // p: Particle
    // neighbors: Particle[]
    // h: smoothing length
    calcDensity(p, neighbors, h) {
        let sum = 0.0;

        for (let i = 0; i < neighbors.length; i++) {
            let rij = vec2(p.position[0] - neighbors[i].position[0], p.position[1] - neighbors[i].position[1]);
            sum += neighbors[i].mass * this.gaussianKernel(this.magnitude(rij), h);
        }

        return sum;
    }

    calcPressure(density, restDensity, k) {
        return k * (density - restDensity);
    }

    distance(p1, p2) {
        return Math.sqrt(Math.pow(p2[0] - p1[0], 2) + Math.pow(p2[1] - p1[1], 2));
    }

    magnitude(p) {
        return Math.sqrt(p[0] * p[0] + p[1] * p[1]);
    }
}
