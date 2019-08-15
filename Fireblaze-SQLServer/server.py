import mysql.connector
import socket
import threading

CONFIG_FILE_PATH = "data/database.cfg"
PORT = 3300
HOST = "localhost"

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

def client_handler(clientSocket, address, config):
    connection = get_sql_connection(config)
    cursor = connection.cursor()
    while True:
        try:
            data = clientSocket.recv(1024)
            if len(data) == 0:
                break
            print("Received data from " + str(address))
            query = data.decode("utf-8")
            print(query)
            try:                
                cursor.execute(query)
                result = ""
                for row in cursor.fetchall():
                    print(row)
                print(result)
            except mysql.connector.Error as e:
                print("Error with SQL query")
                print(str(e))
        except socket.error as e:
            print("Error handling " + str(address) + ": " + str(e))
            break
    cursor.close()
    connection.close()
    print("Closed connection from " + str(address))

def main():
    config = read_config_file(CONFIG_FILE_PATH)

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen(5)
    print("Server starting on (" + HOST + ", " + str(PORT) + ")")
    while True:
        (clientSocket, address) = server.accept()
        print("New connection from " + str(address))
        threading.Thread(target=client_handler, args=(clientSocket, address, config)).start()

    connection.close()

if __name__ == "__main__":
    main()