# "Legacy Leak" Development Plan (C++ Edition)

This plan outlines the implementation phases for the "Legacy Leak" hacking simulator, focusing on performance, modularity, and technical accuracy using C++.

## Phase 1: Core Engine & TUI
**Goal:** Build a robust terminal emulator using modern C++.
- **Terminal Framework:** Utilize **FTXUI** for:
    - Interactive Terminal UI with a "real" feel.
    - **Shell Parser:** Implement advanced parsing for piping (`|`), redirection (`>`, `>>`), and environment variables.
    - Custom prompt, command history, and tab-completion.
- **Virtual File System (VFS):**
    - Implement a hierarchical VFS with full POSIX permission logic (rwx).
    - Support for `ls`, `cd`, `cat`, `mkdir`, `rm`, `chown`, `chmod`.
    - **Logging System:** Automatic generation of system logs in `/var/log` for every host.
- **Process Manager:**
    - A centralized manager to track "running" services and player-spawned background tasks.
    - Support for `ps`, `kill`, and a simplified `top`.

## Phase 2: Networking & Remote Access
**Goal:** Implement the "Dial-up" and "Broadband" networking layers.
- **Host Manager:** A registry of remote server objects, each with unique IPs/Phone numbers and VFS instances.
- **Connection Logic:** A `dial` command that simulates latency and "baud rate" output speeds.
- **Service Layer:**
    - Service objects (Telnet, FTP, SSH) with specific versioning strings.
    - A `scan` utility to probe remote ports.

## Phase 3: Exploitation & Tools
**Goal:** Create the "version-matching" gameplay loop.
- **Tool Manager:** Manages the player's `/bin` directory.
- **Exploit Tools:** Individual executable-like objects for specific versions (e.g., `sploit_sky102`).
- **Logic:** Exploits perform a version check against the target service and grant access if matched.

## Phase 4: Mission & Progression System
**Goal:** Implement the "Freelancer" lifecycle and leveling.
- **BBS/Hub:** Central hub for briefings, payouts, and the Hardware Shop.
- **Procedural Generator:** A system to generate random targets and missions based on the current Act.
- **Economy & Leveling:**
    - Tracking Credits, Reputation, and Level-up triggers.
    - **Act Gating:** Implement logic to lock/unlock story acts based on Level and narrative flags.
- **Save System:** JSON-based persistence using **nlohmann/json**.

## Phase 5: Prologue & Acts I-III (1989-2000)
**Goal:** Establish the foundation of the early era.
- **Prologue:** Tutorial mission introducing core movement and `dial`.
- **Act I-III:** Dial-up sounds (visual/textual), Y2K missions, and the transition to early web.

## Technical Stack
- **Language:** C++20
- **Build System:** CMake 3.20+
- **TUI Library:** [FTXUI](https://github.com/ArthurSonzogni/FTXUI)
- **JSON Library:** [nlohmann/json](https://github.com/nlohmann/json)
- **Architecture:** Object-Oriented with a focus on RAII and modern memory management.

## Initial Development Steps (First 48 Hours)
1. Set up the CMake project structure and integrate dependencies.
2. Build the basic `MainLoop` and `TerminalView` using FTXUI.
3. Implement the `VFSNode` and `FileSystem` classes.
4. Create a simple `CommandRegistry` for `ls` and `cd`.
