# TCP_Server_Auth.py
import socket

# 简单的用户数据库
users = {
    'admin': '123456',
    'user1': 'password1', 
    'test': 'test123'
}

def authenticate(username, password):
    """验证用户名和密码"""
    return users.get(username) == password

# 创建TCP服务器
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 8888)
server_socket.bind(server_address)
server_socket.listen(5)
print("认证服务器已启动，正在监听端口 %s..." % server_address[1])

while True:
    print("等待客户端连接...")
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
                success_msg = "AUTH_SUCCESS:登录成功！开始会话..."
                connection.sendall(success_msg.encode('utf-8'))
                print(f"用户 {username} 认证成功")
                
                # 进入会话循环
                while True:
                    # 接收客户端数据
                    data = connection.recv(1024).decode('utf-8').strip()
                    
                    if not data or data.lower() == 'quit':
                        print(f"用户 {username} 结束会话")
                        break
                    
                    print(f"收到来自 {username} 的消息: {data}")
                    
                    # 回显处理 - 在用户消息后添加"谢谢"
                    if data == "888":
                        response = "你发送了特殊数字888，谢谢！"
                    else:
                        response = f"{data}，谢谢！"  # 主要修改在这里
                    
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
        print("连接关闭\n")

# python TCP_Server_Auth.py