# Pong-Clone

A classic Pong recreation developed using **C++** and the **SFML** (Simple and Fast Multimedia Library) framework. This project features a smooth arcade experience with a player-controlled paddle, an automated AI opponent, and dynamic ball physics.


## 🎮 Features

* **Classic Gameplay:** Real-time paddle movement and ball physics.
* **AI Opponent:** An automated opponent paddle that tracks the ball's position.
* **Dynamic Difficulty:** The ball accelerates upon hitting paddles and features variable return angles based on the hit position.
* **Scoring System:** Visual score tracking displayed at the top of the window.
* **Custom Aesthetics:** Styled with a slate-blue background, yellow paddles, and a cyan ball, utilizing the Iosevka Charon Mono font.


## 🛠️ Requirements

* **C++17** or higher
* **CMake** (version 3.28+) 


* **Ninja** (recommended for build) 


* **SFML 3.0.2** (automatically fetched via CMake)


## 🚀 Getting Started
---

### Building the Project

The project uses `CMake` and a `Makefile` for easy compilation. To build the executable:

```bash
make build

```
---
### Running the Game

Once built, you can launch the game using:

```bash
make run

```
---
### Cleaning Build Files

To remove the `build/` directory and start fresh:

```bash
make clean

```
---

## 🕹️ Controls

| Action | Key(s) |
| --- | --- |
| **Move Up** | `W` or `Up Arrow` |
| **Move Down** | `S` or `Down Arrow` |
| **Close Game** | Window Close Button |



## 📂 Project Structure

* `src/main.cpp`: Entry point and the primary game loop.
* `src/helper.hpp`: Contains game logic, movement controls, and rendering helpers.
* `src/IosevkaCharonMono-Regular.hpp`: Embedded font data for the UI.
* `CMakeLists.txt`: Build configuration and dependency management.


## ⚖️ License

* **Software:** This project is licensed under the **MIT License** - see the `LICENSE` file for details. 


* **Font:** The Iosevka font included is licensed under the **SIL Open Font License 1.1**. 



## How to Contribute

Contributions are welcome and appreciated! Whether you're fixing a bug, improving the AI, or adding new features, here is how you can help: 

---
### 🛠️ Development Workflow

1. **Fork the Repository**: Create your own copy of the project to work on. 


2. **Create a Branch**: Use a descriptive name for your branch (e.g., `feat/add-sound-effects` or `fix/collision-glitch`).
3. **Code & Format**:
* Ensure your code follows the existing style. 


* Run `make format` before committing to ensure consistent styling via `clang-format`. 




4. **Build & Test**:
* Use `make build` to compile the project using the Ninja generator. 


* Verify your changes by running the game with `make run`. 




5. **Submit a Pull Request**: Provide a clear description of your changes and why they are beneficial. 

---


### 📝 Contribution Guidelines

* **Code Standards**: The project targets **C++17**; please avoid using features from newer standards to maintain compatibility with the current `CMakeLists.txt` configuration. 


* **Dependencies**: This project uses `FetchContent` to manage **SFML 3.0.2**. Avoid adding manual library files to the repository; instead, update the `CMakeLists.txt` if new dependencies are required. 


* **Licensing**: By contributing, you agree that your code will be licensed under the **MIT License**. 


* **Attribution**: If you use assets or fonts, ensure they are compatible with the **SIL Open Font License** or similar open-source terms. 


---

### 🐛 Reporting Issues

If you find a bug or have a suggestion, please open an **Issue** on the repository. Provide as much detail as possible, including:

* Your Operating System.
* Steps to reproduce the issue.
* Expected vs. actual behavior.
---
