# 💬 Multi-Client Chat Server (Thread-Based)

A TCP-based multi-client chat application built using **C**, demonstrating **socket programming**, **multithreading**, and **synchronization using mutex**.

---

## 🚀 Features

* 🔗 Multiple clients can connect simultaneously
* 🧵 Thread-per-client architecture using POSIX threads
* 📢 Broadcast messaging (to all clients)
* 💌 Private messaging using `@username`
* 🔒 Thread-safe client handling using mutex
* ❌ Graceful client disconnection handling

---

## 🏗️ Architecture

* **Server**

  * Accepts incoming TCP connections
  * Spawns a new thread for each client
  * Maintains a shared client list (mutex protected)

* **Client**

  * Connects to server
  * Sends and receives messages concurrently

---

## 🧠 Key Concepts Used

* TCP Socket Programming (`socket`, `bind`, `listen`, `accept`)
* Multithreading (`pthread`)
* Synchronization (`pthread_mutex`)
* Inter-process communication
* String parsing for private messaging

---

## 📂 Project Structure

```
.
├── server.c   # Server-side implementation
├── client.c   # Client-side implementation
└── README.md  # Project documentation
```

---

## ⚙️ Compilation & Execution

### 🔧 Compile

```bash
gcc -o server server.c -lpthread
gcc -o client client.c -lpthread
```

### ▶️ Run Server

```bash
./server 8080
```

### 💻 Run Client

```bash
./client 127.0.0.1 8080
```

---

## 🎥 Usage

1. Start the server
2. Open multiple terminals and run clients
3. Enter unique usernames

### 📢 Broadcast Message

```
Hello everyone
```

### 💌 Private Message

```
@username Hello!
```

---

## 🧵 Thread Handling

* Each client is handled by a separate thread
* Threads run concurrently to allow real-time communication
* Mutex is used to protect shared client data

---

## 🔒 Synchronization

* Shared resource: `client_list`
* Protected using `pthread_mutex`
* Prevents race conditions during:

  * Adding clients
  * Removing clients
  * Broadcasting messages

---

## 📊 Performance Analysis

### ✅ Strengths

* Supports multiple clients simultaneously
* Low latency for small-scale usage
* Efficient message handling

### ⚠️ Limitations

* Thread-per-client model is not scalable for large systems
* Fixed maximum number of clients
* Blocking I/O operations

### 🚀 Future Improvements

* Use `select()` or `epoll()` for scalability
* Add encryption (TLS)
* Implement user authentication
* Build GUI client

---

## 👥 Team Contributions

| Member       | Responsibility              |
| ------------ | --------------------------- |
| Sreeja(Mem1) | Server setup & networking   |
| Naveen(Mem2) | Threading & synchronization |
| Lalita(Mem3) | Messaging logic             |
| Raghu (Mem4) | Client, demo & performance  |

---

## 🎯 Conclusion

This project demonstrates how **networking, concurrency, and synchronization** work together to build a real-time communication system similar to modern chat applications.

---

## 💡 Key Takeaway

> Understanding low-level networking using C provides deeper insight into how real-world communication systems operate.

---
