class PhysicsEngine {
    // particle: Particle
    // neighbors: Particle[]
    // h: float
    // k: float
    // restDensity: float
    // return: F: vec2
    static calcForces(ball) {
        let gravity = this.calcGravity(ball.mass);

        return gravity;
    }

    // mass: float
    // return: Fg: vec2
    static calcGravity(mass) {
        return vec2(0, -mass * 9.81);
    }

    static calcTension(mass) {
        return vec2(0, -mass * 9.81);
    }
}