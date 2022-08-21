
import genericpath
import os
import socket
import sys

if len(sys.argv) == 3:
    # Get "IP address of Server" and also the "port number" from argument 1 and argument 2
    ip = sys.argv[1]
    port = int(sys.argv[2])
else:
    print("Run like : python3 server.py <arg1:server ip:this system IP 192.168.0.200> <arg2:server port:20777>")
    ip = "192.168.0.24"
    port = 20777
    # exit(1)

if False:
    import os
    cmd = 'ifconfig | pcre2grep -o "(?<=(inet ))([\d\.]*)(?=( netmask))"'
    ip = os.popen(cmd).read().split('\n')[1]
    port = 20777

# Create a UDP socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the port
server_address = (ip, port)
s.bind(server_address)

tick=0
maxpackets = 2**17 - 1
datastream = []

while True:
    if tick > maxpackets:
        print("reached limit of" + str(maxpackets))
        break
    data, address = s.recvfrom(4096)
    print("recv (" + str(tick) +")" + str(len(data)))
    datastream.append(data)
    tick = tick + 1

track = "monaco"
subfolder = "data/" + track + "/raw"
if not genericpath.exists(subfolder):
    os.mkdir(subfolder)

for i in range(0, len(datastream)):
  with open(subfolder + "/packet"+str(i)+".raw", "wb") as file:
      if i % 10 == len(datastream) - 1:
        print(str(round(i/len(datastream), 2) * 100) + "%\n")
      tmp = file.write(datastream[i])

def unique(l: list = []) -> int:
    res = []
    uq_list = (list(set(l)))
    for x in uq_list:
        res.append(x)
    return res

# breakpoint
# import pdb; pdb.set_trace()

# enter a local python session w/ all pdb variables
# import code; code.interact(local=vars())
