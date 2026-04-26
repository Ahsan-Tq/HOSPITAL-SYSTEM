# Hospital System

A C++ hospital management system built as an Object-Oriented Programming (OOP) project. Designed to simulate real hospital operations — patient registration, doctor assignment, and appointment management — using core OOP principles implemented from scratch.

---

## Why This Exists

Managing hospital data manually is error-prone and slow. This project models a simplified hospital workflow in code, applying OOP concepts to a real-world domain where structure, hierarchy, and encapsulation actually matter.

---

## What It Does

- Register and manage patients
- Add and manage doctors with their specializations
- Assign patients to doctors
- Schedule and track appointments
- View records through a CLI menu

---

## OOP Concepts Applied

- **Classes and Objects** — Patient, Doctor, Appointment each modeled as separate classes
- **Encapsulation** — Data hidden behind class methods, accessed through interfaces
- **Inheritance** — Shared attributes between Person base class and Patient/Doctor subclasses
- **Polymorphism** — Overridden methods for displaying different record types
- **Composition** — Appointment class composed of Patient and Doctor objects

---

## How It Works

1. User launches the program and sees a menu
2. Can register a new patient or add a doctor
3. Can book an appointment linking a patient to a doctor
4. Records are stored and displayed in session
5. All interaction is through the CLI

---

## Tech Stack

| Layer | Technology |
|---|---|
| Language | C++ |
| Paradigm | Object-Oriented Programming |
| Interface | CLI (menu-driven) |

---

## How to Run

1. Clone the repository
   ```bash
   git clone https://github.com/Ahsan-Tq/HOSPITAL-SYSTEM
   ```

2. Navigate to the project folder
   ```bash
   cd HOSPITAL-SYSTEM
   ```

3. Compile the file
   ```bash
   g++ main.cpp -o hospital
   ```

4. Run the program
   ```bash
   ./hospital
   ```

---

## Academic Context

OOP semester project — BS Artificial Intelligence.
Demonstrates real-world application of object-oriented design principles in a system with multiple interacting entities.

---

## Built By

Ahsan Taqweem Imran — [github.com/Ahsan-Tq](https://github.com/Ahsan-Tq)
