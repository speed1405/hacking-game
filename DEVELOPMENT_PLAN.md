# "Legacy Leak" Development Plan

This plan outlines the implementation phases for the "Legacy Leak" hacking simulator, focusing on modularity, technical accuracy, and the transition from the 90s to modern computing.

## Phase 1: Core Engine & Terminal UI
**Goal:** Build a robust terminal emulator that feels "real."
- **Terminal Framework:** Utilize `prompt_toolkit` for Python to implement:
    - Custom prompt (e.g., `user@localhost:~$`).
    - Command history (arrow keys).
    - Tab-completion for files and commands.
    - Syntax highlighting for commands.
    - **Theme System:** A modular styling system to swap color palettes (Green, Amber, etc.) globally.
- **Virtual File System (VFS):**
    - Implement a class-based VFS that supports `ls`, `cd`, `cat`, `mkdir`, `rm`, and `pwd`.
    - Support for file permissions (read/write/execute).
    - Persistent "Home" directory for the player.

## Phase 2: Networking & Remote Access
**Goal:** Implement the "Dial-up" and "Broadband" networking layers.
- **Host System:** A manager for remote servers, each with their own IP/Phone Number, VFS, and active services.
- **Dialer Logic:** A `dial` command for Act I that simulates modem connection speeds and sounds (visual cues).
- **Service Layer:**
    - Each host runs specific services (e.g., `Telnet`, `FTP`, `SMTP`) with specific versions (e.g., `OpenFTP 1.2.0`).
    - A `scan` tool to identify running services and versions.

## Phase 3: Exploitation & Tools
**Goal:** Create the "version-matching" gameplay loop.
- **Tool Manager:** A system for managing the player's `/bin` directory.
- **Exploit Tools:** Individual executables for specific versions (e.g., `sploit_sky102`, `ftp_overflow_v2`).
- **Execution Logic:** Tools must be run while connected to a target; they check if the target's service version matches their payload.

## Phase 4: Mission & Progression System
**Goal:** Implement the "Freelancer" lifecycle and leveling.
- **BBS/Hub:** A central hub for mission briefings and payouts.
- **Economy:** Tracking `Credits` and `Reputation`.
- **Leveling Logic:** Implement the Reputation-to-Level formula and the unlock system for tools/hardware.
- **Procedural Generator:**
    - Create a system to generate random IPs/Phone numbers.
    - Assign random service versions and "data treasures" to generated hosts based on the current Act.
- **Hardware Shop:** A menu/command to purchase faster modems and more storage.
- **Save System:** JSON-based persistence of the player's VFS, stats, and completed missions.

## Phase 5: Prologue & Act I-III - The Early Era (1989-2000)
**Goal:** Establish the foundation of phone phreaking and early web hacking.
- **Prologue (Tutorial):** Controlled tutorial environment introducing `ls`, `cd`, `cat`, and `dial`.
- **Act I:** "Dial-up" atmosphere, BBS interfaces, and `dial` command. *Boss: Telecomm Core.*
- **Act II:** Transition to HTTP/Gopher services and early browser-based exploits. *Boss: Early ISP.*
- **Act III:** Y2K mission set and legacy bank systems. *Boss: The Y2K Vault.*

## Phase 6: Act IV-VI - The Expansion Era (2001-2013)
**Goal:** Transition to high-speed networking and social-technical hacking.
- **Act IV:** Implement Broadband logic and WiFi/SSH mechanics. *Boss: Corporate Backbone.*
- **Act V:** Social engineering "clue" system. *Boss: Social Profile Engine.*
- **Act VI:** Hacktivism missions, multi-vector attack logic, and IRC-based hub. *Boss: Aegis Command Center.*

## Phase 7: Act VII-IX - The Modern & Future Era (2014-Present)
**Goal:** Advanced infrastructure and AI-driven defense.
- **Act VII:** Cloud-specific mechanics (S3/Containers). *Boss: S3 Monolith.*
- **Act VIII:** Ransomware mechanics and Dark Web mission boards. *Boss: Encryption Hive.*
- **Act IX:** AI "Sentinel" implementation. *Boss: Aegis Prime (AI Core).*

## Phase 8: Polish & Content Expansion
**Goal:** Finalize the narrative arc and user experience.
- Implement the "Vapor" digital consciousness interaction.
- Final choice branching logic and multiple endings.
- Comprehensive sound design (modem screeches, server hums) via visual/textual feedback.

## Technical Stack
- **Language:** Python 3.10+
- **Primary Library:** `prompt_toolkit` (for terminal UI)
- **Data Format:** `json` (for save files and world state)
- **Architecture:** Object-Oriented (Host, File, User, Service, Command classes)

## Initial Development Steps (First 48 Hours)
1. Initialize the project structure and git repository.
2. Build the `BaseTerminal` class using `prompt_toolkit`.
3. Implement the `VirtualFileSystem` and core commands (`ls`, `cd`).
4. Create a "Hello World" remote host that can be "dialed" into.
