# Project "Legacy Leak": A Hacking Simulator Design Document

## 1. Game Overview
"Legacy Leak" is a single-player, CLI-based hacking simulator that follows the career of a freelance hacker from the early 1990s through the modern era. The game focuses on technical accuracy, logic-based challenges, and the evolution of technology. Players progress by completing missions, upgrading their hardware, and learning to exploit various versions of networked services.

## 2. Core Narrative
The player starts as a hobbyist in the early 90s, armed with a basic computer and a dial-up modem.
- **Act I: The BBS Era (1990-1999):** Phone phreaking, Bulletin Board Systems (BBS), telnet, and early exploits. Focus on manual discovery and social engineering clues.
- **Act II: The Dotcom & Cyberwar Era (2000-2010):** The rise of the web, SSH replacing Telnet, early WiFi hacking, and the professionalization of freelance hacking.
- **Act III: The Modern Era (2011-Present):** Advanced encryption, cloud infrastructure, and sophisticated vulnerability management.

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
