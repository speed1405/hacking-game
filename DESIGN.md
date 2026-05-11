# Project "Legacy Leak": A Hacking Simulator Design Document

## 1. Game Overview
"Legacy Leak" is a single-player, CLI-based hacking simulator that follows the career of a freelance hacker from the early 1990s through the modern era. The game focuses on technical accuracy, logic-based challenges, and the evolution of technology. Players progress by completing missions, upgrading their hardware, and learning to exploit various versions of networked services.

## 2. Core Narrative: The "Ghost in the Machine" Journey
The player takes on the role of a nameless freelancer operating from the shadows. The tone is **Gritty Noir**: cold, paranoid, and focused on the cost of digital secrets. The narrative spans three decades of evolving technology and shifting ethics across nine distinct acts.

### Act I: The Copper Age (1990-1993) - "The Dial-Up Shadows"
*   **Atmosphere:** CRT flicker, acoustic couplers, and the smell of ozone.
*   **Key Milestone:** Bypassing phone company toll systems (blue-boxing) to reach remote BBSs without a trace.
*   **Plot:** You meet your mentor, *Vapor*, who teaches you that "information wants to be free, but access has a price."

### Act II: The Superhighway (1994-1996) - "The Mosaic Breach"
*   **Atmosphere:** The excitement and chaos of the first web browsers.
*   **Key Milestone:** Exploit the transition from private BBSs to the public "World Wide Web" via early Gopher and HTTP vulnerabilities.
*   **Plot:** *Vapor* warns you about a group called *Aegis* that is quietly buying up the infrastructure of the new web.

### Act III: The Gold Rush (1997-2000) - "The Y2K Panic"
*   **Atmosphere:** Glowing server racks and the ticking clock of the millennium.
*   **Key Milestone:** Exploiting legacy code in banking systems as they scramble to patch for Y2K.
*   **Plot:** You discover that *Aegis* has intentionally left "logic bombs" in key infrastructure. *Vapor* disappears during a federal raid on the "LOD" (Legion of Doom).

### Act IV: The Broadband Shift (2001-2004) - "The Always-On Threat"
*   **Atmosphere:** The hum of DSL modems and the sudden silence of unencrypted Telnet being replaced by SSH.
*   **Key Milestone:** The first major WiFi (WEP) cracks and the rise of persistent connections allowing for longer, more complex breaches.
*   **Plot:** You receive an encrypted package from the missing *Vapor*. It contains a key to an *Aegis* vault that you cannot yet reach.

### Act V: The Social Web (2005-2008) - "The Human Exploit"
*   **Atmosphere:** The "glossy" look of Web 2.0 and the rise of social engineering.
*   **Key Milestone:** Using early social media (MySpace/early Facebook) to gather "clues" for password cracking and credential stuffing.
*   **Plot:** You find *Vapor's* signature inside an *Aegis* subsidiary. You realize they haven't just bought the web; they are building a profile on every user.

### Act VI: The Hacktivist Rise (2009-2013) - "The Lulz Era"
*   **Atmosphere:** Glitch art, IRC chat rooms, and the chaotic energy of decentralized groups.
*   **Key Milestone:** Coordinating "multi-vector" attacks (DDoS as a distraction for a data breach) against high-profile political targets.
*   **Plot:** You are recruited by a hacktivist group to expose *Aegis*. You have to decide if you're a mercenary or a revolutionary.

### Act VII: The Cloud Migration (2014-2017) - "The Invisible Fortress"
*   **Atmosphere:** Clinical white-space, AWS dashboards, and the "Snowden" paranoia.
*   **Key Milestone:** Infiltrating virtualized containers and exploiting misconfigured "S3 Buckets" to exfiltrate massive datasets.
*   **Plot:** You find evidence that *Aegis* is the primary contractor for a global, silent surveillance program. *Vapor* is rumored to be their lead architect—either a prisoner or a traitor.

### Act VIII: The Ransomware Pandemic (2018-2021) - "The Extortion Cycle"
*   **Atmosphere:** Red warning screens, crypto-wallet addresses, and the dark web economy.
*   **Key Milestone:** Deploying and managing complex ransomware chains to force *Aegis* to reveal their "Master Key."
*   **Plot:** You finally breach an *Aegis* deep-storage site. You find *Vapor*, or what’s left of them: a digital consciousness uploaded to the network.

### Act IX: The Zero-Trust Era (2022-Present) - "The AI Panopticon"
*   **Atmosphere:** Minimalist terminals, AI-driven security alerts, and quantum-ready encryption.
*   **Key Milestone:** Bypassing AI-security "sentinels" that learn from your command history in real-time.
*   **Plot:** The final confrontation. You must use everything you've learned over 30 years to either dismantle *Aegis* from the root or take control of the panopticon yourself.

## 3. Gameplay Mechanics

### 3.1. The Terminal Interface
The game is played entirely through a simulated terminal.
- **Commands:** Must be POSIX-compliant (e.g., `ls`, `cd`, `cat`, `rm`, `mkdir`, `grep`, `ssh`, `ftp`, `telnet`).
- **Simulated OS:** A hierarchical file system for the player's own machine and any remote machines they access.
- **Output:** Text-based, with ASCII art used for headers, BBS interfaces, and system logs.

### 3.2. Networking & Connection
- **Dial-up (90s):** Requires "dialing" a phone number via a `dial` command. Characterized by slow text rendering and distinct modem sounds.
- **IP/SSH (Modern):** Transition to using `ssh [user]@[ip]` for connections.
- **Network Mapping:** Use of tools like `nmap` or `finger` to discover services and their versions.

### 3.3. Service Versioning & Bypassing
The core challenge lies in identifying and exploiting services.
- **Discovery:** Running a scan on a target reveals services (e.g., `FTP 2.1.3`, `OpenSSH 4.2p1`).
- **Vulnerability Database:** The player maintains or finds a list of known vulnerabilities for specific versions.
- **Exploitation:** The player must use the correct tool or command sequence that matches the target's service version.

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

## 5. Technical Design Goals
- **Accuracy:** Commands should behave as they do in a real Linux environment.
- **No Scripting (Phase 1):** Gameplay is focused on manual command entry.
- **Persistence:** The state of the player's filesystem and known hosts is saved.
- **Challenge over Trace:** Difficulty comes from technical complexity and discovering the correct exploits.

## 6. Economy, Reputation & Leveling
The player's progression is tracked via three core metrics:
- **Credits:** Currency earned from all missions and boss targets. Used for hardware (Modems, CPUs, Storage) and Software (Exploits, Scanners).
- **Reputation:** Earned by successfully completing missions and exfiltrating "Bonus" data. Reputation serves as the XP for the leveling system.
- **Level (Rank):** As Reputation reaches certain thresholds, the player "Levels Up."
    - **Unlocks:** Each level grants access to more prestigious mission boards, advanced exploit vendors, and act-specific hardware.
    - **Titles:** Leveling grants Noir-inspired ranks (e.g., *Novice*, *Script-Diver*, *Ghost-Protocol*, *Digital-Shade*).

## 7. Mission Systems

### 7.1. Story Missions
These are the fixed, 9-act narrative missions that drive the plot involving *Vapor* and *Aegis*. They offer high rewards and major story beats.

### 7.2. Procedural Missions (The Grind)
To earn extra credits and reputation, players can take on procedural "Contracts."
- **Generation:** These missions are randomly generated based on the player's current Act and Level.
- **Target Variety:** Difficulty varies. A "Low Stakes" mission might involve an old FTP server, while a "High Stakes" mission involves a hardened modern firewall.
- **Objectives:** Include data theft, file deletion, or "system mapping" for a client.
- **Replayability:** Players can grind these missions to afford high-end hardware before attempting the Act Boss.

## 8. Boss Targets
At the end of each act, the player must breach a "Boss Target." These are high-security systems that require the player to combine all the skills, tools, and hardware upgrades they have acquired during that act. Successful breaches reward significant **Credits**.

### Act I Boss: "The Central Office" (Telecomm Core)
*   **Skill Test:** Advanced phone phreaking and multiple `dial` hops.
*   **Challenge:** Navigate a complex "blue-box" voice menu system to find the hidden modem number.

### Act II Boss: "The Mosaic Arch" (Early ISP)
*   **Skill Test:** Service discovery and early HTTP version exploitation.
*   **Challenge:** The target uses a custom HTTP server version; you must find the vulnerability description in a hidden Gopher hole first.

### Act III Boss: "The Y2K Vault" (Major Bank)
*   **Skill Test:** Legacy code exploitation and timestamp manipulation.
*   **Challenge:** Bypass a "time-lock" system by manipulating the system clock during a Y2K simulation.

### Act IV Boss: "The Node 0" (Corporate Backbone)
*   **Skill Test:** SSH credential stuffing and WiFi packet analysis.
*   **Challenge:** Sniff a "handshake" from a remote terminal to gain the initial entry point.

### Act V Boss: "The Profile engine" (Social Media Giant)
*   **Skill Test:** Social engineering and complex SQL injections.
*   **Challenge:** Piece together the admin's password from their public social media posts across multiple "mock" profiles.

### Act VI Boss: "The Hive Mind" (Aegis Command Center)
*   **Skill Test:** Multi-vector attacks and DDoS management.
*   **Challenge:** Manage a "botnet" via commands to distract the automated firewall while you slip into the backend.

### Act VII Boss: "The S3 Monolith" (Cloud Infrastructure)
*   **Skill Test:** Cloud misconfiguration and container escaping.
*   **Challenge:** Chain together three different cloud-service vulnerabilities to reach the "Root" account.

### Act VIII Boss: "The Encryption Hive" (Ransomware Hub)
*   **Skill Test:** Decryption algorithm matching and dark web negotiation.
*   **Challenge:** Reverse-engineer a ransomware key in real-time before the "Boss" host locks you out.

### Act IX Boss: "The Aegis Prime" (AI Core)
*   **Skill Test:** AI sentinel bypassing and quantum-ready exploit execution.
*   **Challenge:** Defeat the "Sentinel" by varying your command patterns so the AI cannot predict your next move.

## 9. Example Mission (1994)
1. **Objective:** Exfiltrate "SALARY_LIST.TXT" from a local accounting firm's BBS.
2. **Step 1:** Dial the firm's number: `dial 555-0123`.
3. **Step 2:** Explore the file system: `ls`, `cd /private`.
4. **Step 3:** Encounter a permission error.
5. **Step 4:** Check the version of the BBS software: `version`. (Output: `SkyNet BBS v1.0.2`)
6. **Step 5:** Use a known exploit tool for `v1.0.2` to gain admin access.
7. **Step 6:** Download the file: `get SALARY_LIST.TXT`.
8. **Step 7:** Disconnect and upload to the mission board.
