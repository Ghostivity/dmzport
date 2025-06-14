![dmzport](https://github.com/user-attachments/assets/15f0060b-781a-48f7-8e38-80399ac7c0e5)


# 🛰️ dmzport — Ultra-Lightweight TCP Port Forwarder

> ⛓️ **Securely pivot into local networks via DMZ**  
> 🧠 Built with simplicity, precision, and tactical clarity in pure C

---

### 📌 Overview

**dmzport** — это сверхлёгкая, автономная утилита на C, которая пробрасывает TCP-порт с сервера в зоне **DMZ** (между интернетом и внутренней сетью) на скрытый **локальный хост**, к которому нельзя подключиться напрямую.  
Работает даже на системах с устаревшей `glibc`. Не требует root-доступа. Не имеет зависимостей. Просто запускаешь — и всё.

📦 **Пример боевого применения**:
```
[Ваш компьютер] → [DMZ-сервер:8000] ⇆ [Внутренний сервер 192.168.122.50:80]
```

⛏️ Сценарии:
- Получение веб-страниц из внутренней сети через curl или ffuf
- Анализ открытых портов в локальной сети

---

### 🛠️ Features

- 🔁 Поддержка **множества TCP-соединений**
- 🧱 Работает **без root-прав**
- ✨ **Без зависимостей** — только POSIX C
- 🧼 Статическая сборка для совместимости со старыми Linux

---

### 🚀 Installation

#### 💻 Стандартная сборка:
```
gcc -o dmzport dmzport.c -pthread
```

#### 🧱 Полностью статическая сборка (для старых серверов DMZ):
```
gcc -static -o dmzport dmzport.c -pthread
```

---

### 📎 Usage

#### 📥 Синтаксис:
```
./dmzport <BIND_IP:BIND_PORT> <TARGET_IP:TARGET_PORT>
```

#### 🔁 Пример:
```
./dmzport 0.0.0.0:8000 192.168.122.50:80
```

Теперь вы можете с интернет хоста выполнить:
```
curl http://<DMZ_SERVER_IP>:8000
```
...и получите ответ с **192.168.122.50:80**, находящегося в локальной сети клиента.

---

### 🌍 English Summary

**dmzport** is a zero-dependency, non-root, multi-connection TCP port forwarder written in portable C.  
It allows you to pivot from a DMZ server into isolated local network targets.

📌 **Use Case**:
You land a DMZ server (e.g. 172.22.0.4)  
You need to access a LAN service (e.g. 192.168.122.50:80)  
Run:
```
./dmzport 0.0.0.0:8000 192.168.122.50:80
```

Then:
```
curl http://172.22.0.4:8000
```

You now see the content of the internal service — relayed over TCP via the DMZ host.

---

### ✅ License

This project is licensed under the MIT License.

```
© Ghostivity. Free for commercial and private use. Modify, distribute, embed.
No warranty. Use responsibly.
```

---

### 🤝 Author

Developed by **Ghostivity**

📬 https://github.com/Ghostivity
