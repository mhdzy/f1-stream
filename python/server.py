import genericpath
import os
import socket
import sys

if len(sys.argv) == 3:
    # Get "IP address of Server" and also the "port number" from argument 1 and argument 2
    ip = sys.argv[1]
    port = int(sys.argv[2])
else:
    print("Usage: python3 server.py <arg1:ip:192.168.0.200> <arg2:port:20777>")
    ip = "192.168.0.13"
    port = 20777

if False:
    cmd = 'ifconfig | pcre2grep -o "(?<=(inet ))([\d\.]*)(?=( netmask))"'
    ip = os.popen(cmd).read().split("\n")[1]
    port = 20777


def create_udp_socket(ip, port):
    # create a socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # enable IP re-use
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind((ip, port))
    # do not block indefinitely
    sock.settimeout(0.5)
    return sock


def close_udp_socket(sock):
    sock.close()


def receive_udp_data(sock, n_packets=20000):
    counter = 0
    datastream = []
    print("now waiting for data...")
    while True:
        if counter > n_packets:
            break
        data, _ = sock.recvfrom(4096)
        datastream.append(data)
        counter = counter + 1
        if counter % 1000:
            print(f"({counter})" + "recv (" + str(counter) + ") " + str(len(data)))
    return data


def export_udp_data(data, track):
    export_folder = "data/" + track + "/raw"
    if not genericpath.exists(export_folder):
        os.mkdir(export_folder)
    for i in range(0, len(data)):
        with open(export_folder + "/packet" + str(i) + ".raw", "wb") as file:
            _ = file.write(data[i])


maxpackets = 100000
track = "miami"

sock = create_udp_socket(ip, port)
data = receive_udp_data(sock, maxpackets)
close_udp_socket(sock)
export_udp_data(data, track)
