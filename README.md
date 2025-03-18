
## 🐍 Snake Game using Data Structures & Algorithms  

### 📌 Introduction  
This project is a **terminal-based Snake Game** implemented in **C using ncurses**, focusing on **Data Structures & Algorithms (DSA)**. The game efficiently handles:  
- **Dynamic memory management** using a **linked list** to represent the snake.  
- **Queue operations** for movement and growth handling.  
- **Optimized collision detection** for walls, food, and self-collision.  

### 🎯 Objectives  
- Implement a **dynamic** and **efficient** Snake Game.  
- Utilize **linked lists** for flexible snake movement and growth.  
- Ensure **real-time responsiveness** with non-blocking user input.  
- Optimize memory usage and **minimize computational overhead**.  

### 🛠️ Technologies Used  
- **C Language**  
- **Ncurses Library** (for terminal rendering)  
- **Dynamic Memory Management**  
- **Linked List & Queue** for game logic  

---

## 📌 Data Structures & Algorithm Design  

### 🔹 **Snake Representation - Linked List**  
Each segment of the snake is stored as a **node** in a **singly linked list** containing:  
✔️ `(x, y)` coordinates for position tracking  
✔️ Pointer to the next segment (`next`)  

### 🔹 **Queue-Like Movement**  
✔️ **New head is added** at the front (O(1) complexity)  
✔️ **Tail is removed** unless food is consumed  

### 🔹 **Collision Detection**  
✔️ **Boundary Detection** – Restricts movement within predefined grid  
✔️ **Self-Collision Check** – Ensures game over on contact with itself  
✔️ **Food Collision** – Food is placed on unoccupied grid spaces  

---

## 📌 Algorithm Breakdown  

### 🔹 **Game Loop**  
1️⃣ **Read user input** (Arrow keys for movement, 'q' to quit)  
2️⃣ **Update snake position** based on direction  
3️⃣ **Check collisions** with walls or itself  
4️⃣ **Handle food consumption** (grow snake, update score)  
5️⃣ **Update display** using **ncurses**  
6️⃣ **Control frame rate** to maintain smooth gameplay  

### 🔹 **Food Placement Strategy**  
- Generates random coordinates **within bounds**  
- Ensures **food does not overlap** with the snake  
- Keeps trying **until a valid location is found**  

### 🔹 **Performance Optimizations**  
✔️ **Dynamic memory allocation** prevents excessive RAM usage  
✔️ **O(1) insertion & deletion** using linked list  
✔️ **Frame rate control** using `usleep()` for smooth execution  

---

## 📌 Installation & Running the Game  

### ✅ **Prerequisites**  
Ensure you have **ncurses** installed on your Linux system:  
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

### 🚀 **Compile & Run**  
```bash
gcc snake_game.c -o snake -lncurses
./snake
```

---

## 📌 Controls  
🎮 **Arrow Keys** → Move Up/Down/Left/Right  
❌ **Q** → Quit the game  

---

## 📌 Future Enhancements  
🔹 AI-controlled snake 🤖  
🔹 Multiplayer mode 🆚  
🔹 Graphical rendering with OpenGL or SDL 🎨  

---

## 📌 Conclusion  
This project successfully applies **data structures and algorithms** to create an efficient **terminal-based Snake Game**. The **linked list** ensures **dynamic growth**, and the **optimized grid-based approach** maintains smooth gameplay.  

---

### 📜 License  
This project is **open-source**. Feel free to modify and improve! 🚀  


