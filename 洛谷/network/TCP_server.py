# TCP_Server_Simple.py
import socket

# 创建一个TCP/IP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 绑定服务器地址和端口
server_address = ('localhost', 8888)
server_socket.bind(server_address)

# 开始监听连接
server_socket.listen(1)
print("服务器已启动，正在监听端口 %s..." % server_address[1])

while True:
    # 等待一个客户端连接
    print("等待连接...")
    connection, client_address = server_socket.accept()
    
    try:
        print("客户端已连接：", client_address)
        
        # 接收客户端发来的数据
        data = connection.recv(1024)
        print("接收到数据：%s" % data.decode('utf-8'))
        
        if data:
            # data="888"
            # 回显数据给客户端
            print("正在回显数据...")
            connection.sendall(b'888')
        else:
            # 没有数据表示客户端想关闭连接
            print("客户端断开连接。")
            break
            
    finally:
        # 清理连接
        connection.close()

#  python TCP_server.py