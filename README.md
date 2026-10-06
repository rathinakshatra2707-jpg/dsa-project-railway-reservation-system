# dsa-project-railway-reservation-system
# 🚆 Railway Reservation and Waiting List Management System

A **Data Structures and Algorithms (DSA) project in C** that simulates a railway reservation system with train management, ticket booking, cancellation, PNR tracking, confirmed reservations, and a FIFO-based waiting list.

## 📌 Project Overview

The **Railway Reservation and Waiting List Management System** is a menu-driven C program designed to demonstrate the practical application of fundamental DSA concepts.

The system allows users to:

- Add and manage trains
- Display train details
- Search trains
- Book tickets
- Generate PNR numbers
- Maintain confirmed reservations
- Maintain a waiting list
- Cancel confirmed tickets
- Automatically promote waiting passengers
- Check PNR status
- Display confirmed and waiting passengers
- Sort trains by train number

The main focus of the project is the practical use of **Arrays, Linked Lists, Queues, Searching, and Sorting**.

---

## 🎯 Objectives

- Implement a real-world application using C and DSA.
- Manage train information efficiently.
- Implement railway ticket booking.
- Generate unique PNR numbers.
- Store confirmed reservations dynamically.
- Maintain a FIFO-based waiting list.
- Handle ticket cancellations.
- Automatically promote waiting passengers when a seat becomes available.
- Implement train and PNR searching.
- Implement train sorting using Bubble Sort.

---

## 🧠 Data Structures and Algorithms Used

| Concept | Application |
|---|---|
| **Structure** | Stores train and passenger information |
| **Array** | Stores train records |
| **Singly Linked List** | Stores confirmed reservations |
| **Linear Queue** | Manages the waiting list |
| **Linear Search** | Searches trains and PNRs |
| **Bubble Sort** | Sorts trains by train number |
| **Pointers** | Connects linked-list and queue nodes |
| **Dynamic Memory Allocation** | Uses `malloc()` and `free()` |

---

## 🚉 System Workflow

```text
                    RAILWAY RESERVATION SYSTEM
                              |
             ┌────────────────┼────────────────┐
             ↓                ↓                ↓
        Train Management   Ticket Booking   Cancellation
             |                |                |
          Array         Check Seat           Find PNR
                              |
                    ┌─────────┴─────────┐
                    ↓                   ↓
              Seat Available       No Seat Available
                    ↓                   ↓
                CONFIRMED            WAITING
                    ↓                   ↓
              Linked List             Queue
                    |                   |
                    └────────┬──────────┘
                             ↓
                       Seat Available
                             ↓
                  First Waiting Passenger
                             ↓
                         CONFIRMED
