# THAEM

[![itch.io](https://img.shields.io/badge/itch.io-play%20it%20now-informational)](https://marcinkonowalczyk.itch.io/thaem)

THAEM uses waypoints to create a path for the player, which it also used to interact with enemies (bullets). The behaviour of all of the components of the game (player and the bullets) is related to the behaviour of many other components. Hence, they can be considered all to be linked together.

Made using C++ and [piksel](https://bernhardfritz.github.io/piksel/).

[Emscripten](http://kripken.github.io/emscripten-site/index.html) installed with `brew install emscripten`.

[Build instructions](https://bernhardfritz.github.io/piksel/#/gettingstarted/buildproject?id=build-for-the-web-).

Works best on Chrome / Firefox. Can also work on Safari if [WebGL 2.0](https://caniuse.com/webgl2) is enabled with `Develop > Experimental Features > WebGL 2.0`.

# ToDos

- [x] Find better fonts hack
- [x] Link in itch.io
- [x] Second level to hard? Endless needs lower points ceiling. Maybe just lower points requirements in general?
- [x] bullets spawning on screen
- [x] black bullets have no path drawn on death screen
- [ ] ? more zen thoughts and/or death messages
- [x] ? Color in AE in the title
- [x] package itch.io better
- [ ] On-death animation
- [x] <strike>fix itch.io banner</strike> replaced with a shield
- [ ] better screenshots here and on itch.io