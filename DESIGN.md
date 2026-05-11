# Project "Legacy Leak": A Hacking Simulator Design Document

## 1. Game Overview
"Legacy Leak" is a single-player, CLI-based hacking simulator that follows the career of a freelance hacker from the early 1990s through the modern era. The game focuses on technical accuracy, logic-based challenges, and the evolution of technology. Players progress by completing missions, upgrading their hardware, and learning to exploit various versions of networked services.

## 2. Core Narrative: The "Ghost in the Machine" Journey
The player takes on the role of a nameless freelancer operating from the shadows. The tone is **Gritty Noir**: cold, paranoid, and focused on the cost of digital secrets. The narrative spans three decades of evolving technology and shifting ethics.

### Act I: The Copper Age (1990-1999)
*Atmosphere: Dark rooms, the glow of CRT monitors, the screech of 2400-baud modems.*
* **Setting:** Early internet "wild west." Most connections are via phone lines.
* **Key Milestone: "The Great Phreak":** The player must navigate the phone system to bypass long-distance charges and reach a high-security BBS.
* **The "Job":** You are hired to retrieve evidence of corporate embezzlement from a local bank's private BBS.
* **Historical Event:** The transition from simple password guessing to "buffer overflow" exploits.
* **Ending:** A mentor-figure (alias: *Vapor*) goes silent after a federal raid, leaving you with an encrypted file you can't yet open.

### Act II: The Silicon Boom (2000-2009)
*Atmosphere: Noisy server rooms, the rise of "The Matrix" aesthetic, the transition from dial-up to DSL.*
* **Setting:** The internet is everywhere, but it's fragile. The shift from unencrypted Telnet to SSH begins.
* **Key Milestone: "The Dotcom Crash":** Navigating a bankrupt tech giant's defunct servers to recover "lost" intellectual property.
* **The "Job":** Infiltration of a major ISP to plant a backdoor for a mysterious client. You begin to see *Vapor's* signature in the ISP's core code.
* **Historical Event:** The rise of SQL injection and early worm outbreaks.
* **Ending:** You realize the file from Act I is part of a larger global surveillance backbone being built by a conglomerate called *Aegis*.

### Act III: The Cloud Era (2010-Present)
*Atmosphere: Sleek interfaces, clinical white-space, the silent efficiency of data centers.*
* **Setting:** Everything is interconnected. Encryption is standard. Containers and cloud instances make targets feel ethereal.
* **Key Milestone: "The Dark Web Transition":** Moving operations from IRC to TOR-based onion boards.
* **The "Job":** Breaching a "Zero-Trust" cloud environment to delete the data *Aegis* has been collecting on you for 20 years.
* **Historical Event:** The discovery of massive processor-level vulnerabilities (like Meltdown/Spectre) and the rise of state-sponsored cyberwarfare.
* **Ending:** A final choice—release the truth about *Aegis* (and end your career) or become the new silent architect of their digital panopticon.

## 3. Gameplay Mechanics

### 3.1. The Terminal Interface
The game is played entirely through a simulated terminal.
- **Commands:** Must be POSIX-compliant (e.g., `ls`, `cd`, `cat`, `rm`, `mkdir`, `grep`, `ssh`, `ftp`, `telnet`).
- **Simulated OS:** A hierarchical file system for the player's own machine and any remote machines they access.
- **Output:** Text-based, with ASCII art used for headers, BBS interfaces, and system logs.

### 3.2. Networking & Connection
- **Dial-up (90s):** Requires "dialing" a phone number via a `dial` command. Characterized by slow text rendering and distinct modem sounds (simulated via text/visuals).
- **IP/SSH (Modern):** Transition to using `ssh [user]@[ip]` for connections.
- **Network Mapping:** Use of tools like `nmap` or `finger` to discover services and their versions.

### 3.3. Service Versioning & Bypassing
The core challenge lies in identifying and exploiting services.
- **Discovery:** Running a scan on a target reveals services (e.g., `FTP 2.1.3`, `OpenSSH 4.2p1`).
- **Vulnerability Database:** The player maintains or finds a list of known vulnerabilities for specific versions.
- **Exploitation:** The player must use the correct tool or command sequence that matches the target's service version. Newer versions may require different approaches or the discovery of specific configuration flaws.

### 3.4. Hardware Progression
Players earn money from missions to upgrade their rig:
- **Modems:** 2400 baud -> 14.4k -> 56k -> DSL -> Fiber (affects command output speed and file transfer time).
- **Storage:** Upgrading HDD to store more tools and stolen data.
- **CPU:** Faster decryption or password cracking.

## 4. Mission Structure
Missions are delivered via a central hub that evolves over time.
1. **Early 90s:** A mysterious BBS called "The Node."
2. **2000s:** Encrypted IRC channels or early web forums.
3. **Modern:** Dark web onion sites or encrypted messaging apps.

**Mission Types:**
- **Exfiltration:** Find and download a specific file (e.g., `blueprints.pdf`, `passwords.txt`).
- **Sabotage:** Delete specific system files or shut down a service.
- **Infiltration:** Plant a "backdoor" for a later mission.

## 5. Technical Design Goals
- **Accuracy:** Commands should behave as they do in a real Linux environment (e.g., `ls -la` shows hidden files).
- **No Scripting (Phase 1):** Gameplay is focused on manual command entry and tactical decision-making.
- **Persistence:** The state of the player's filesystem and known hosts is saved.
- **Challenge over Trace:** There is no "trace" or "timer" mechanic. The difficulty comes from the complexity of the systems, the need for technical accuracy, and discovering the correct exploits for specific service versions.

## 6. Economy & Reputation
As a freelancer, the player earns **Credits** and **Reputation**.
- **Credits:** Used to purchase hardware upgrades (Modems, CPUs, Storage) and "zero-day" exploits from the black market.
- **Reputation:** Higher reputation unlocks higher-paying and more complex missions from more exclusive underground boards.

## 7. Example Mission (1994)
1. **Objective:** Exfiltrate "SALARY_LIST.TXT" from a local accounting firm's BBS.
2. **Step 1:** Dial the firm's number: `dial 555-0123`.
3. **Step 2:** Explore the file system: `ls`, `cd /private`.
4. **Step 3:** Encounter a permission error.
5. **Step 4:** Check the version of the BBS software: `version`. (Output: `SkyNet BBS v1.0.2`)
6. **Step 5:** Use a known exploit tool for `v1.0.2` to gain admin access.
7. **Step 6:** Download the file: `get SALARY_LIST.TXT`.
8. **Step 7:** Disconnect and upload to the mission board.
