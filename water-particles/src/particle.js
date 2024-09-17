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

    // Code taken from this video: https://www.youtube.com/watch?v=rSKMYc1CQHE
    // Generates particles in a convenient block
    // return: Particle[]
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

    // Do the dumb thing: Say every other particle is a neighbor. Optimize in the future
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

    // dt: float
    // neighbors: Particle[]
    // h: float
    // k: float
    // return: mat4
    update(dt, neighbors, h, k) {
        // Physics calculation
        let F = PhysicsEngine.calcForces(this, neighbors, h, k, this.restDensity);
        this.acceleration = vec2(F[0] / this.mass, F[1] / this.mass);
        this.velocity = add(this.velocity, mult(this.acceleration, vec2(dt, dt)));
        this.position = add(this.position, mult(this.velocity, vec2(dt, dt)));

        // Bounds checking
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

        // Get transformation matrix
        return mult(translate(this.position[0], this.position[1], 0.0), scalem(this.circleScale, this.circleScale, 1));
    }

}
