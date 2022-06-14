import socket
import sys

if len(sys.argv) == 3:
    # Get "IP address of Server" and also the "port number" from argument 1 and argument 2
    ip = sys.argv[1]
    port = int(sys.argv[2])
else:
    print("Run like : python3 server.py <arg1:server ip:this system IP 192.168.0.200> <arg2:server port:20777>")
    exit(1)

# Create a UDP socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the port
server_address = (ip, port)
s.bind(server_address)
print("remember: Ctrl+C to exit")

tick=0
datastream = []
while True:
    tick = tick+1
    if tick > 999:
        break
    print(tick)
    print("####### server is listening #######")
    data, address = s.recvfrom(4096)
    datastream.append(data)
    print("\n\n [RECEIVE] Server received: ", data, "\n\n")

for i in range(0, len(datastream)):
  with open("data/data"+str(i)+".raw", "wb") as file:
      file.write(datastream[i])

def unique(l: list = []) -> int:
    res = []
    uq_list = (list(set(l)))
    for x in uq_list:
        res.append(x)
    return res

unique_packet_lengths = unique(map(len, datastream))

# breakpoint
import pdb; pdb.set_trace()
# enter a local python session w/ all pdb variables
import code; code.interact(local=vars())

data_lens = map(len, datastream)

print(list(data_lens))