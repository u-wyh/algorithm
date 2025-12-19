# TCP_Server_File.py
import socket
import os
import time

# 简单的用户数据库
users = {
    'admin': '123456',
    'user1': 'password1', 
    'test': 'test123'
}

# 创建文件保存目录
if not os.path.exists('received_files'):
    os.makedirs('received_files')

def authenticate(username, password):
    """验证用户名和密码"""
    return users.get(username) == password

def save_file(filename, file_data):
    """保存接收到的文件"""
    filepath = os.path.join('received_files', filename)
    with open(filepath, 'wb') as f:
        f.write(file_data)
    return filepath

# 创建TCP服务器
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 8888)
server_socket.bind(server_address)
server_socket.listen(5)
print("文件传输服务器已启动，正在监听端口 %s..." % server_address[1])
print("接收的文件将保存在 'received_files' 目录中")

while True:
    print("\n等待客户端连接...")
    connection, client_address = server_socket.accept()
    print("客户端已连接：", client_address)
    
    try:
        # 接收认证信息
        auth_data = connection.recv(1024).decode('utf-8').strip()
        print(f"收到认证数据: {auth_data}")
        
        # 解析用户名和密码
        if ':' in auth_data:
            username, password = auth_data.split(':', 1)
            
            if authenticate(username, password):
                # 认证成功
                success_msg = "AUTH_SUCCESS:登录成功！可以发送文本或文件。"
                connection.sendall(success_msg.encode('utf-8'))
                print(f"用户 {username} 认证成功")
                
                # 会话循环
                while True:
                    # 接收数据
                    data = connection.recv(1024)
                    
                    if not data:
                        print(f"用户 {username} 断开连接")
                        break
                    
                    # 尝试解码为文本，判断是否为文件传输命令
                    try:
                        text_data = data.decode('utf-8').strip()
                        
                        if text_data.lower() == 'quit':
                            print(f"用户 {username} 结束会话")
                            break
                        elif text_data.startswith('FILE:'):
                            # 文件传输模式
                            filename = text_data[5:].strip()  # 提取文件名
                            print(f"用户 {username} 请求发送文件: {filename}")
                            
                            # 通知客户端准备接收文件
                            connection.sendall(b"READY_FOR_FILE")
                            
                            # 接收文件大小信息
                            file_size_data = connection.recv(1024).decode('utf-8')
                            file_size = int(file_size_data)
                            print(f"文件大小: {file_size} 字节")
                            
                            # 确认准备接收
                            connection.sendall(b"READY_FOR_DATA")
                            
                            # 接收文件数据
                            received_data = b""
                            while len(received_data) < file_size:
                                chunk = connection.recv(min(4096, file_size - len(received_data)))
                                if not chunk:
                                    break
                                received_data += chunk
                            
                            # 保存文件
                            saved_path = save_file(filename, received_data)
                            print(f"文件保存成功: {saved_path}")
                            
                            # 发送成功确认
                            response = f"FILE_RECEIVED:文件 '{filename}' 接收成功，大小 {len(received_data)} 字节，谢谢！"
                            connection.sendall(response.encode('utf-8'))
                            
                        else:
                            # 普通文本消息
                            print(f"收到来自 {username} 的文本: {text_data}")
                            response = f"{text_data}，谢谢！"
                            connection.sendall(response.encode('utf-8'))
                            
                    except UnicodeDecodeError:
                        # 如果是二进制数据但未使用文件协议，当作普通文本处理
                        print(f"收到来自 {username} 的二进制数据，大小: {len(data)} 字节")
                        response = f"收到 {len(data)} 字节的二进制数据，谢谢！"
                        connection.sendall(response.encode('utf-8'))
                        
            else:
                # 认证失败
                error_msg = "AUTH_FAILED:用户名或密码错误！"
                connection.sendall(error_msg.encode('utf-8'))
                print(f"认证失败: {auth_data}")
        else:
            # 数据格式错误
            error_msg = "AUTH_FAILED:数据格式错误！"
            connection.sendall(error_msg.encode('utf-8'))
            
    except Exception as e:
        print(f"处理客户端时出错: {e}")
    finally:
        connection.close()
        print("连接关闭")

# python  TCP_Server_File.py