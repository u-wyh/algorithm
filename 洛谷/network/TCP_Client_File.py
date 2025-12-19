# TCP_Client_File.py
import socket
import os

def send_file(client_socket, file_path):
    """发送文件到服务器"""
    try:
        # 获取文件名和文件大小
        filename = os.path.basename(file_path)
        file_size = os.path.getsize(file_path)
        
        # 发送文件传输命令
        file_command = f"FILE:{filename}"
        client_socket.sendall(file_command.encode('utf-8'))
        
        # 等待服务器准备
        response = client_socket.recv(1024).decode('utf-8')
        if response != "READY_FOR_FILE":
            print(f"服务器未准备好接收文件: {response}")
            return False
        
        # 发送文件大小
        client_socket.sendall(str(file_size).encode('utf-8'))
        
        # 等待服务器确认
        response = client_socket.recv(1024).decode('utf-8')
        if response != "READY_FOR_DATA":
            print(f"服务器数据接收未就绪: {response}")
            return False
        
        # 发送文件数据
        print(f"正在发送文件: {filename} ({file_size} 字节)")
        with open(file_path, 'rb') as f:
            bytes_sent = 0
            while bytes_sent < file_size:
                chunk = f.read(4096)
                if not chunk:
                    break
                client_socket.sendall(chunk)
                bytes_sent += len(chunk)
                print(f"进度: {bytes_sent}/{file_size} 字节 ({bytes_sent/file_size*100:.1f}%)", end='\r')
        
        print(f"\n文件发送完成: {bytes_sent} 字节")
        
        # 接收服务器确认
        response = client_socket.recv(1024).decode('utf-8')
        print(f"服务器响应: {response}")
        return True
        
    except Exception as e:
        print(f"文件发送失败: {e}")
        return False

def main():
    # 创建TCP客户端
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('localhost', 8888)
    
    print("正在连接文件传输服务器 %s 端口 %s..." % server_address)
    
    try:
        client_socket.connect(server_address)
        
        # 获取用户认证信息
        username = input("请输入用户名: ")
        password = input("请输入密码: ")
        
        # 发送认证信息
        auth_message = f"{username}:{password}"
        client_socket.sendall(auth_message.encode('utf-8'))
        
        # 接收认证结果
        auth_response = client_socket.recv(1024).decode('utf-8')
        print(f"服务器响应: {auth_response}")
        
        # 检查认证结果
        if auth_response.startswith("AUTH_SUCCESS"):
            print("认证成功！可以发送文本消息或文件。")
            print("命令说明:")
            print("  - 输入文本: 发送普通消息")
            print("  - 输入 'sendfile 文件路径': 发送文件")
            print("  - 输入 'quit': 退出程序")
            
            # 会话循环
            while True:
                user_input = input("\n请输入消息或命令: ")
                
                if user_input.lower() == 'quit':
                    client_socket.sendall(b'quit')
                    print("结束会话")
                    break
                    
                elif user_input.lower().startswith('sendfile '):
                    # 文件传输模式
                    file_path = user_input[9:].strip()  # 提取文件路径
                    
                    if os.path.exists(file_path):
                        send_file(client_socket, file_path)
                    else:
                        print(f"文件不存在: {file_path}")
                        
                else:
                    # 普通文本消息
                    client_socket.sendall(user_input.encode('utf-8'))
                    response = client_socket.recv(1024).decode('utf-8')
                    print(f"服务器回复: {response}")
                    
        else:
            print("认证失败，连接关闭")
            
    except ConnectionRefusedError:
        print("无法连接到服务器，请确保服务器已启动")
    except Exception as e:
        print(f"发生错误: {e}")
    finally:
        client_socket.close()
        print("客户端关闭")

if __name__ == "__main__":
    main()

# python TCP_Client_File.py
# sendfile C:\\Users\\wyh15\\Documents\\code\\network\\text.txt
