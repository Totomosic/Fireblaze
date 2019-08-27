import mysql.connector
import socket
import threading

CONFIG_DIRECTORY_PATH = "../CommonData/"
DATABASE_CONFIG_FILE_PATH = CONFIG_DIRECTORY_PATH + "FireblazeDB.cfg"
SERVER_CONFIG_FILE_PATH = CONFIG_DIRECTORY_PATH + "SQLServer.cfg"

console_lock = threading.Lock()

def read_config_file(file):
    f = open(file, "r")
    result = {}
    data = f.read()
    lines = data.split('\n')
    for line in lines:
        if '=' not in line:
            continue
        line = line.replace(" ", "")
        line = line.replace("\n", "")
        line = line.replace("\r", "")
        parts = line.split('=')
        result[parts[0]] = parts[1]
    return result

def get_sql_connection(config):
    return mysql.connector.connect(host=config["db_host"], user=config["db_user"], password=config["db_pass"], port=int(config["db_port"]), database=config["db_name"])

def handle_sql_query(query, clientSocket, address, config, connection, cursor):
    try:                
        cursor.execute(query)
        result = "Response: ["
        isFirst = True
        for row in cursor:
            if not isFirst:
                result += ","
            result += "["
            firstItem = True
            for item in row:
                if not firstItem:
                    result += ","
                result += str(item)
                firstItem = False
            result += "]"
            isFirst = False
        result += "]\0"
        sendData = result.encode("utf-8")
        clientSocket.sendall(sendData)
    except mysql.connector.Error as e:
        console_lock.acquire()
        print("Error with SQL query")
        print(str(e))
        console_lock.release()
        result = "Error: " + str(e) + "\0"
        sendData = result.encode("utf-8")
        clientSocket.sendall(sendData)

def handle_sql_commit(clientSocket, address, config, connection, cursor):
    try:
        connection.commit()
        response = "Success\0"
        sendData = response.encode("utf-8")
        clientSocket.sendall(sendData)
    except mysql.connector.Error as e:
        response = "Error\0"
        sendData = response.encode("utf-8")
        clientSocket.sendall(sendData)

def handle_sql_rollback(clientSocket, address, config, connection, cursor):
    try:
        connection.rollback()
        response = "Success\0"
        sendData = response.encode("utf-8")
        clientSocket.sendall(sendData)
    except mysql.connector.Error as e:
        response = "Error\0"
        sendData = response.encode("utf-8")
        clientSocket.sendall(sendData)

def client_handler(clientSocket, address, config):
    connection = get_sql_connection(config)
    cursor = connection.cursor()
    while True:
        try:
            data = clientSocket.recv(2048)
            if len(data) == 0:
                break
            console_lock.acquire()
            print("Received data from " + str(address))
            message = data.decode("utf-8")
            print(message)
            console_lock.release()
            if message.startswith("Query: "):
                query = message[len("Query: "):]
                handle_sql_query(query, clientSocket, address, config, connection, cursor)
            elif message.startswith("Commit"):
                handle_sql_commit(clientSocket, address, config, connection, cursor)
            elif message.startswith("Rollback"):
                handle_sql_rollback(clientSocket, address, config, connection, cursor)
            else:
                console_lock.acquire()
                print("Invalid query")
                console_lock.release()
                clientSocket.sendall("Error: Invalid query".encode("utf-8"))
        except socket.error as e:
            console_lock.acquire()
            print("Error handling " + str(address) + ": " + str(e))
            console_lock.release()
            break
    cursor.close()
    connection.close()
    console_lock.acquire()
    print("Closed connection from " + str(address))
    console_lock.release()

def listen_thread(server, config):
    while True:
        (clientSocket, address) = server.accept()
        console_lock.acquire()
        print("New connection from " + str(address))
        console_lock.release()
        threading.Thread(target=client_handler, args=(clientSocket, address, config)).start()

def main():
    config = read_config_file(DATABASE_CONFIG_FILE_PATH)
    server_config = read_config_file(SERVER_CONFIG_FILE_PATH)

    HOST = server_config["server_host"]
    PORT = int(server_config["server_port"])

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen(5)
    print("Server starting on (" + HOST + ", " + str(PORT) + ")")
    
    threading.Thread(target=listen_thread, args=(server, config)).start()

    terminalClient = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    terminalClient.connect((HOST, PORT))
    
    while True:
        request = input(">")
        request = "Query: " + request
        request += '\0'
        terminalClient.sendall(request.encode("utf-8"))
        data = terminalClient.recv(4096)
        console_lock.acquire()
        print(data.decode("utf-8"))
        console_lock.release()

    connection.close()

if __name__ == "__main__":
    main()
