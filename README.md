# dmzport
Lightweight TCP Port Forwarder<br>

dmzport — это простая и компактная утилита на языке C, которая позволяет пробрасывать TCP-порт из DMZ-сервера к хосту в локальной сети, к которому нет прямого доступа снаружи.

Используется, например, когда:

У вас есть доступ к серверу в DMZ (между интернетом и внутренней сетью клиента),

И вы хотите добраться до внутреннего ресурса (например, 172.22.0.3:80),

Через проброс: 172.22.0.4:8000 → 172.22.0.3:80.

🛠 Возможности
· 🔁 Многоразовый TCP-прокси (обслуживает множество соединений)
· 🧠 Без root-доступа
· 🧼 Без зависимостей (только POSIX)
· 📁 Поддерживает статическую сборку

🚀 Установка:
```gcc -o dmzport dmzport.c -pthread```
⚙️ Или статически (если на целевой машине старая glibc):
```gcc -static -o dmzport dmzport.c -pthread```

📌 Использование
```./dmzport DMZ_IP:PORT TARGET_IP:PORT```
Пример:
```./dmzport 0.0.0.0:8000 192.168.122.50:80```
Теперь, с вашего компьютера:
```curl http://<DMZ_SERVER_IP>:8000```
Вы получите ответ от сервера 192.168.122.50:80, находящегося в локальной сети клиента.

dmzport is a small and efficient C-based TCP port forwarder that allows you to forward a port from a DMZ host to a target inside a local network, often unreachable from the internet.

Use case:

You have access to a DMZ server

You want to reach an internal service (e.g., 172.22.0.3:80),

You forward: 172.22.0.4:8000 → 172.22.0.3:80.

🛠 Features
· 🔁 Multi-connection TCP proxy
· 🚫 No root required
· 💡 Zero dependencies (pure POSIX C)
· 🧱 Static build support

🚀 Installation:
```gcc -o dmzport dmzport.c -pthread```
Or static (for old glibc environments):
```gcc -static -o dmzport dmzport.c -pthread```

📌 Usage
```./dmzport DMZ_IP:PORT TARGET_IP:PORT```
Example:
```./dmzport 0.0.0.0:8000 192.168.122.50:80```
Then on your internet machine:
```curl http://<DMZ_SERVER_IP>:8000```
You will receive the response from 192.168.122.50:80 via DMZ relay.

✅ License
MIT License. Free to use, modify, and distribute.
