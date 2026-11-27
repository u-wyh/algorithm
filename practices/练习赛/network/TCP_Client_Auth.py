# TCP_Client_Auth.py
import socket

def main():
    # 创建TCP客户端
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('localhost', 8888)
    
    print("正在连接认证服务器 %s 端口 %s..." % server_address)
    
    try:
        client_socket.connect(server_address)
        
        # 获取用户认证信息
        username = input("请输入用户名: ")
        password = input("请输入密码: ")
        
        # 发送认证信息（格式：username:password）
        auth_message = f"{username}:{password}"
        client_socket.sendall(auth_message.encode('utf-8'))
        
        # 接收认证结果
        auth_response = client_socket.recv(1024).decode('utf-8')
        print(f"服务器响应: {auth_response}")
        
        # 检查认证结果
        if auth_response.startswith("AUTH_SUCCESS"):
            print("认证成功！开始会话...")
            print("输入 'quit' 退出会话")
            
            # 会话循环
            while True:
                message = input("发送消息: ")
                client_socket.sendall(message.encode('utf-8'))
                
                if message.lower() == 'quit':
                    print("结束会话")
                    break
                
                # 接收服务器响应
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

# python TCP_Client_Auth.py