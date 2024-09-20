class ParticleSystem {
    numParticles; // int
    particles; // Particle[]
    collisionDamping; // float
    circleScale; // float

    h; // smoothing length: float
    k; // stiffness constant: float

    constructor(numParticles, h, k) {
        this.numParticles = numParticles;
        this.circleScale = 0.02;
        this.particles = this.genParticles();
        this.collisionDamping = 0.01;
        this.h = h;
        this.k = k;
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

    // Shift density and pressure over to be used to make new values
    updateDensityPressure(h, k) {
        for (let i = 0; i < this.numParticles; i++) {
            this.particles[i].prevPressure = this.particles[i].pressure;
            this.particles[i].prevDensity = this.particles[i].density;

            let neighbors = particleSystem.findNeighbors(i);
            this.particles[i].density = PhysicsEngine.calcDensity(this.particles[i], neighbors, h);
            this.particles[i].pressure = PhysicsEngine.calcPressure(this.particles[i].density, this.particles[i].restDensity, k);
        }
    }
}

class Particle {
    acceleration; // vec2
    velocity; // vec2
    position; // vec2

    restDensity; // float
    mass; // float
    volume; // float

    density; // float
    pressure; // float
    prevDensity; // float
    prevPressure; // float

    circleScale; // float
    screenEdge; // float

    constructor(p, circleScale) {
        this.acceleration = vec2(0.0, 0.0);
        this.velocity = vec2(0.0, 0.0);
        this.position = p;
        this.screenEdge = 1.0 - circleScale;
        this.circleScale = circleScale
        this.volume = this.getVolume();
        this.restDensity = 1;
        // this.mass = this.getMass(this.volume);
        this.mass = 0.001;
    }

    // dt: float
    // neighbors: Particle[]
    // h: float
    // k: float
    // return: mat4
    update(dt, neighbors, h) {
        // Physics calculation
        let F = PhysicsEngine.calcForces(this, neighbors, h);
        console.log("F: " + F);
        this.acceleration = vec2(F[0] / this.mass, F[1] / this.mass);
        this.velocity = add(this.velocity, mult(this.acceleration, vec2(dt, dt)));
        this.position = add(this.position, mult(this.velocity, vec2(dt, dt)));

        // Bounds checking
        if (this.position[0] > this.screenEdge) {
            this.position[0] = this.screenEdge;
            this.velocity[0] = -this.velocity[0] * 0.2;
        }
        if (this.position[0] < -this.screenEdge) {
            this.position[0] = -this.screenEdge;
            this.velocity[0] = -this.velocity[0] * 0.2;
        }
        if (this.position[1] > this.screenEdge) {
            this.position[1] = this.screenEdge;
            this.velocity[1] = -this.velocity[1] * 0.2;
        }
        if (this.position[1] < -this.screenEdge) {
            this.position[1] = -this.screenEdge;
            this.velocity[1] = -this.velocity[1] * 0.2;
        }

        // Get transformation matrix
        return mult(translate(this.position[0], this.position[1], 0.0), scalem(this.circleScale, this.circleScale, 1));
    }

    getMass(volume) {
        return this.restDensity * volume;
    }

    getVolume() {
        return Math.PI * this.circleScale * this.circleScale;
    }

    toString() {
        return `Particle:
        Position: (${this.position[0]}, ${this.position[1]})
        Velocity: (${this.velocity[0]}, ${this.velocity[1]})
        Acceleration: (${this.acceleration[0]}, ${this.acceleration[1]})
        Rest Density: ${this.restDensity}
        Density: ${this.density}
        Pressure: ${this.pressure}
        Previous Density: ${this.prevDensity}
        Previous Pressure: ${this.prevPressure}
        Mass: ${this.mass.toFixed(3)}
        Volume: ${this.volume.toFixed(3)}
        Circle Scale: ${this.circleScale}
        Screen Edge: ${this.screenEdge}`;
    }
}
