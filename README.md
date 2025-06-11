# dmzport
Lightweight TCP Port Forwarder<br>

dmzport — это простая и компактная утилита на языке C, которая позволяет пробрасывать TCP-порт из DMZ-сервера к хосту в локальной сети, к которому нет прямого доступа снаружи.<br>
<br>
Используется, например, когда:<br>
<br>
У вас есть доступ к серверу в DMZ (между интернетом и внутренней сетью клиента),<br>
<br>
И вы хотите добраться до внутреннего ресурса (например, 172.22.0.3:80),<br>
<br>
Через проброс: 172.22.0.4:8000 → 172.22.0.3:80.<br>
<br>
🛠 Возможности<br>
· 🔁 Многоразовый TCP-прокси (обслуживает множество соединений)<br>
· 🧠 Без root-доступа<br>
· 🧼 Без зависимостей (только POSIX)<br>
· 📁 Поддерживает статическую сборку<br>
<br>
🚀 Установка:<br>
```gcc -o dmzport dmzport.c -pthread```<br><br>
⚙️ Или статически (если на целевой машине старая glibc):<br>
```gcc -static -o dmzport dmzport.c -pthread```<br><br>
<br>
📌 Использование<br>
```./dmzport DMZ_IP:PORT TARGET_IP:PORT```<br><br>
Пример:<br>
```./dmzport 0.0.0.0:8000 192.168.122.50:80```<br><br>
Теперь, с вашего компьютера:<br>
```curl http://<DMZ_SERVER_IP>:8000```<br>
Вы получите ответ от сервера 192.168.122.50:80, находящегося в локальной сети клиента.<br>
<br>
dmzport is a small and efficient C-based TCP port forwarder that allows you to forward a port from a DMZ host to a target inside a local network, often unreachable from the internet.<br>
<br>
Use case:<br>
<br>
You have access to a DMZ server<br>
<br>
You want to reach an internal service (e.g., 172.22.0.3:80),<br>
<br>
You forward: 172.22.0.4:8000 → 172.22.0.3:80.<br>
<br>
🛠 Features<br>
· 🔁 Multi-connection TCP proxy<br>
· 🚫 No root required<br>
· 💡 Zero dependencies (pure POSIX C)<br>
· 🧱 Static build support<br>
<br>
🚀 Installation:<br>
```gcc -o dmzport dmzport.c -pthread```<br><br>
Or static (for old glibc environments):<br>
```gcc -static -o dmzport dmzport.c -pthread```<br><br>
<br>
📌 Usage<br>
```./dmzport DMZ_IP:PORT TARGET_IP:PORT```<br><br>
Example:<br>
```./dmzport 0.0.0.0:8000 192.168.122.50:80```<br><br>
Then on your internet machine:<br>
```curl http://<DMZ_SERVER_IP>:8000```<br>
You will receive the response from 192.168.122.50:80 via DMZ relay.<br>
<br><br>
✅ License<br>
MIT License. Free to use, modify, and distribute.
