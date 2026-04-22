import socket
import struct
import time
import sys

# --- CONSTANTES DEL PROTOCOLO NEXUS ---
PORT = 27042

CMD_READ_MEM       = 0x01
CMD_WRITE_MEM      = 0x02
CMD_SCAN_SNAPSHOT  = 0x03
CMD_SCAN_DIFF      = 0x04
CMD_ENUM_MODULES   = 0x05
CMD_HOOK_SYMBOL    = 0x06
CMD_NOP_REGION     = 0x07
CMD_SET_MODE       = 0x08
CMD_BAN_SIM        = 0x09
CMD_PONG           = 0xFF

class NexusClient:
    def __init__(self, ip, port):
        self.ip = ip
        self.port = port
        self.sock = None

    def connect(self):
        print(f"[*] Conectando a {self.ip}:{self.port}...")
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.ip, self.port))
        print("[+] Conectado exitosamente al servidor NEXUS.")

    def disconnect(self):
        if self.sock:
            self.sock.close()
            print("[*] Desconectado.")

    def _send_cmd(self, cmd, payload=b''):
        # Header: [CMD: 4 bytes] [LEN: 4 bytes]
        header = struct.pack('<II', cmd, len(payload))
        self.sock.sendall(header + payload)

    def _recv_resp(self):
        # Recibir Header de respuesta
        header_data = self.sock.recv(8)
        if not header_data or len(header_data) < 8:
            return None, None
        
        cmd, length = struct.unpack('<II', header_data)
        
        # Recibir Payload
        payload = b''
        while len(payload) < length:
            chunk = self.sock.recv(length - len(payload))
            if not chunk:
                break
            payload += chunk
            
        return cmd, payload

    def ping(self):
        print("[*] Enviando PING...")
        self._send_cmd(CMD_PONG)
        cmd, payload = self._recv_resp()
        if cmd == CMD_PONG:
            print("[+] PONG recibido. Conexión estable.")
        else:
            print("[-] PING falló.")

    def scan_snapshot(self):
        print("[*] Solicitando Snapshot de memoria (Fase 1)...")
        self._send_cmd(CMD_SCAN_SNAPSHOT)
        cmd, payload = self._recv_resp()
        if cmd == CMD_SCAN_SNAPSHOT and len(payload) == 4:
            count = struct.unpack('<I', payload)[0]
            print(f"[+] Snapshot tomado exitosamente: {count} candidatos encontrados.")
        else:
            print("[-] Error tomando snapshot.")

    def set_mode(self, exploit_mode=False):
        mode_val = 1 if exploit_mode else 0
        mode_str = "EXPLOIT" if exploit_mode else "RESEARCH"
        print(f"[*] Cambiando modo a {mode_str}...")
        
        payload = struct.pack('<B', mode_val)
        self._send_cmd(CMD_SET_MODE, payload)
        
        cmd, resp_payload = self._recv_resp()
        if cmd == CMD_SET_MODE:
            print(f"[+] Modo {mode_str} activado en el dispositivo.")
        else:
            print("[-] Error cambiando el modo.")

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Uso: python pc_client.py <IP_DEL_IPHONE>")
        sys.exit(1)
        
    target_ip = sys.argv[1]
    client = NexusClient(target_ip, PORT)
    try:
        client.connect()
        client.ping()
        
        # Ejemplo de flujo de trabajo:
        # 1. Cambiar a modo Research (solo logear, no modificar nada peligroso aún)
        client.set_mode(exploit_mode=False)
        
        # 2. Tomar un snapshot inicial del heap del juego
        client.scan_snapshot()
        
    except Exception as e:
        print(f"[-] Error de conexión: {e}")
        print("[!] Asegúrate de que el juego está abierto y el dispositivo está en la misma red WiFi.")
    finally:
        client.disconnect()
