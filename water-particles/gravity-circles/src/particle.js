let fg = vec2(0.0, -0.1);

class Particle {
    acceleration;
    velocity;
    position;
    circleScale;

    constructor(v) {
        this.acceleration = vec2(0.0, 0.0);
        this.velocity = v;
        this.position = vec2(0.0, 0.0);
        this.circleScale = 0.02;
    }

    update(dt) {
        this.acceleration = add(this.acceleration, fg);
        this.velocity = add(this.velocity, mult(this.acceleration, vec2(dt, dt)));
        this.position = add(this.position, mult(this.velocity, vec2(dt, dt)));

        let screenEdge = 1.0 - this.circleScale;

        if (this.position[0] > screenEdge) {
            this.position[0] = screenEdge;
        }
        if (this.position[0] < -screenEdge) {
            this.position[0] = -screenEdge;
        }
        if (this.position[1] > screenEdge) {
            this.position[1] = screenEdge;
        }
        if (this.position[1] < -screenEdge) {
            this.position[1] = -screenEdge;
        }

        return mult(translate(this.position[0], this.position[1], 0.0), scalem(this.circleScale, this.circleScale, 1));
    }
}

function genParticles(number) {
    let particles = [];
    let max = 0.8;
    let min = 0.1;

    for (i = 0; i < number; i++) {
        let vX = Math.random() * (max - min) + min;
        let vY = Math.random() * (max - min) + min;

        particles.push(new Particle(vec2(vX, vY)));
    }

    return particles;
}