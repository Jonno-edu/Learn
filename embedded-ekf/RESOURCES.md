# Embedded ESKF Resources

## Knowledge

- [Paper: "Quaternion kinematics for the error-state Kalman filter" - Joan Sola](https://arxiv.org/abs/1711.02508)
  Foundational source for quaternion perturbations, attitude errors, and ESKF rotation handling. Use for: quaternion error-state math and attitude injection.
- [Primer: Reference frames and how they are used in inertial navigation - VectorNav](https://www.vectornav.com/resources/inertial-navigation-primer/math-fundamentals/math-refframes)
  Practical inertial-navigation reference for frame vocabulary. Use for: NED, body frame, and navigation-frame terminology.
- [Book: Kalman and Bayesian Filters in Python - Roger Labbe](https://github.com/rlabbe/Kalman-and-Bayesian-Filters-in-Python)
  Open source intuition-first Kalman filtering text. Use for: Kalman gain, covariance, residuals, and sanity-check intuition.
- [Article: The Power of Ten - Rules for Developing Safety Critical Code - Gerard J. Holzmann](https://spinroot.com/gerard/pdf/P10.pdf)
  Compact safety-critical C guidance from NASA/JPL context. Use for: the course's conservative C style rules.
- [Standard: NASA-STD-8739.8 Software Assurance and Software Safety Standard](https://standards.nasa.gov/standard/NASA/NASA-STD-87398)
  NASA software assurance and software safety standard. Use for: context on assurance language and avoiding unsupported flight-readiness claims.
- [Framework: NASA F Prime](https://nasa.github.io/fprime/)
  Flight software and embedded systems framework from NASA/JPL. Use later for: comparing this standalone library with component-based flight software architecture.
- [Framework: NASA Core Flight System](https://github.com/nasa/cFS)
  NASA cFS repository and documentation entry point. Use later for: OBC integration context after the standalone ESKF core exists.

## Wisdom (Communities)

- [F Prime Discussions](https://github.com/nasa/fprime/discussions)
  Useful later for component architecture and flight-software design questions, not for the early standalone C lessons.
- [cFS Discussions](https://github.com/nasa/cFS/discussions)
  Useful later for NASA cFS integration patterns and operational flight-software architecture.

## Gaps

- Need a preferred primary source for discrete inertial navigation ESKF equations with IMU bias states and GPS position/velocity updates.
- Need a C-focused numerical linear algebra reference suitable for fixed-size embedded implementations.

