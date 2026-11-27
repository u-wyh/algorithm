# TCP_Client_Simple.py
import socket

# 创建一个TCP/IP socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 连接服务器
server_address = ('localhost', 8888)
print("正在连接 %s 端口 %s..." % server_address)
client_socket.connect(server_address)

try:
    # 发送数据
    message = "你好，服务器！"
    print("发送：%s" % message)
    client_socket.sendall(message.encode('utf-8'))
    
    # 接收服务器回显的数据
    data = client_socket.recv(1024)
    print("接收：%s" % data.decode('utf-8'))
    
finally:
    print("关闭连接。")
    client_socket.close()

#  python TCP_client.py