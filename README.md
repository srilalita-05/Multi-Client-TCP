# Multi-Client Chat Server (Windows - Thread-Based)

## 📌 Overview

This project implements a **TCP-based multi-client chat system** using C on Windows.
The server handles multiple clients simultaneously using threads and supports:

* Broadcast messaging (to all clients)
* Private messaging (user-to-user)
* Client join/leave notifications
* Thread-safe client management

---

## 🧠 Architecture

### Server

* Accepts multiple client connections
* Creates a new thread for each client
* Maintains a list of connected clients (with usernames)
* Routes messages:

  * Broadcast → to all clients
  * Private → to specific client

### Client

* Connects to the server
* Sends messages
* Receives messages asynchronously using a separate thread

---

## ⚙️ Features

* ✅ Multi-client support (thread-based)
* ✅ Username system
* ✅ Broadcast messaging
* ✅ Private messaging using `/pm`
* ✅ Join/leave notifications
* ✅ Thread synchronization using `CRITICAL_SECTION`
* ✅ Error handling for unknown users

---

## 🛠️ Technologies Used

* C Programming
* Winsock2 (Windows Sockets API)
* Windows Threads (`CreateThread`)
* Synchronization (`CRITICAL_SECTION`)

---

## 📁 File Structure

```
server.c   → Chat server implementation
client.c   → Chat client implementation
README.md  → Project documentation
```

---

## 🚀 Compilation

Use MinGW / MSYS2:

```bash
gcc server.c -o server -lws2_32
gcc client.c -o client -lws2_32
```

---

## ▶️ How to Run

### Step 1: Start Server

```bash
./server
```

---

### Step 2: Start Clients (in separate terminals)

```bash
./client
```

---

### Step 3: Enter Username

Each client must enter a username after connecting.

---

## 💬 Usage

### 🔹 Broadcast Message

Just type:

```
Hello everyone
```

All clients will receive:

```
Alice: Hello everyone
```

---

### 🔹 Private Message

Format:

```
/pm <username> <message>
```

Example:

```
/pm Bob Hi bro
```

Output (only for Bob):

```
[PM] Alice: Hi bro
```

---

## ⚠️ Important Notes

* Usernames are **case-sensitive**
* Each client must have a **unique username** (recommended)
* Server must be started **before clients**
* Private messaging fails if username does not match exactly

---

## 🧪 Testing

Run:

* 1 server
* 2 or more clients

Test:

* Broadcast messages
* Private messages
* Client disconnects

---

## 🔒 Synchronization

The server uses `CRITICAL_SECTION` to:

* Protect shared client list
* Avoid race conditions between threads

---

## 🧩 Limitations

* No username uniqueness enforcement
* No message persistence
* Limited number of clients (`MAX_CLIENTS`)
* No GUI (console-based)

---

## 🚀 Future Improvements

* Add `/list` command to view active users
* Enforce unique usernames
* Add timestamps to messages
* GUI-based client (using Qt or similar)
* File sharing support
* Scalable model using `select()` or IOCP

---

## 🎯 Conclusion

This project demonstrates:

* Socket programming
* Multithreading
* Synchronization
* Client-server architecture

It serves as a strong foundation for building real-time communication systems.

---
